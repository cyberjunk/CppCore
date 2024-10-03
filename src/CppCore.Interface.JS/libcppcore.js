
const imports = { 
    "wasi_snapshot_preview1": {
      sched_yield() {
        console.log("import: sched_yield");
        return 0; 
      }
    }
}

const handle = await WebAssembly
    .instantiateStreaming(fetch('libcppcore.wasm'), imports)
    .then(lib => {
        console.debug("libcppcore: Library loaded")
        console.debug("libcppcore: Exports")
        console.debug(lib.instance.exports);
        
        /*console.debug("Memory Buffer Size")
        console.debug(lib.instance.exports.memory.buffer.byteLength.toString(16));
        console.debug(lib.instance.exports.memory.buffer.maxByteLength.toString(16));*/
        
        /*lib.instance.exports.memory.grow(1);
        console.debug(lib.instance.exports.memory.buffer.byteLength.toString(16));
        console.debug(lib.instance.exports.memory.buffer.maxByteLength.toString(16));*/
        
        /*var _tls_base = lib.instance.exports.__tls_base.value;
        var _data_end = lib.instance.exports.__data_end.value;
        var _heap_base = lib.instance.exports.__heap_base.value
        var _stack_pointer = lib.instance.exports.__stack_pointer.value

        console.debug("__tls_base: " + _tls_base.toString(16));
        console.debug("__data_end: " + _data_end.toString(16));
        console.debug("__heap_base: " + _heap_base.toString(16));
        console.debug("__stack_pointer: " + _stack_pointer.toString(16));*/

        return lib;
    });

const registry = new FinalizationRegistry((ptr) => {
    console.log("Finalizing: " + ptr)
    handle.instance.exports.cppcore_free(ptr);
});

const encoder = new TextEncoder();
const decoder = new TextDecoder();

/////////////////////////////////////////////////////////////////////////////////////////////

function alloc(size) {
    const ptr = handle.instance.exports.cppcore_alloc(size);     
    if (ptr == 0)
        throw new Error('Out of heap memory');
    return ptr;
}

function hexStrFromInt(v) {
    return "0x" + v.toString(16).padStart(8, '0');
}

/////////////////////////////////////////////////////////////////////////////////////////////

export class Buffer extends Uint8Array {
    constructor(parm1, parm2, parm3) {
        console.debug("libcppcore: Constructing Buffer (" + 
            typeof(parm1) + "," + 
            typeof(parm2) + "," + 
            typeof(parm3) + ")");
        if (parm1 instanceof Uint8Array) {
            console.debug("libcppcore: Copy Buffer from Uint8Array");
            const ptr = alloc(parm1.byteLength);
            super(handle.instance.exports.memory.buffer, ptr, parm1.byteLength);
            this.set(parm1);
            registry.register(this, ptr);
        }
        else if (parm1 == handle.instance.exports.memory.buffer) {
            console.debug("libcppcore: Creating view on existing Buffer");
            super(handle.instance.exports.memory.buffer, parm2, parm3);
        }
        else if (!isNaN(parm1)) {
            console.debug("libcppcore: Creating Buffer from size=" + parm1);              
            const ptr = alloc(parm1);
            super(handle.instance.exports.memory.buffer, ptr, parm1);
            //console.debug("libcppcore: Allocated Buffer at: " + hexStrFromInt(ptr));
            registry.register(this, ptr);
        }
        else {
            throw new Error("Not supported");
        }
    }
    get bitLength() {
        return this.byteLength << 3;
    }
    get _ptr() {
        return this.byteOffset;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

export class CString {
    constructor(v) {
        console.debug("libcppcore: CString from " + v);
        const type = typeof(v);
        if (type === 'string') {
            this._buffer = new Buffer(v.length+1);
            this.fromString(v);
        }
        else if (type === 'undefined') {
            this._buffer = new Buffer(16);
            this.usedLength = 0;
        }
        else if (Number.isInteger(v)) {
            this._buffer = new Buffer(v+1);
            this.usedLength = 0;
        }
        else if (v instanceof CString) {
            console.log("FROM OTHER CSTRING");
            this._buffer = new Buffer(v._buffer);
            this.usedLength = v.usedLength;
        }
        else {
            console.log(type);
            throw new Error('Invalid value for CString');
        }
    }
    get maxLength() {
      return this._buffer.byteLength - 1;
    }
    get _ptr() {
      return this._buffer._ptr;
    }
    fromString(str) {
        const enc = encoder.encode(str);
        if (this.maxLength < enc.length)
            throw new Error('String too big');
        this._buffer.set(enc);
        this._buffer[enc.length] = 0x00;
        this.usedLength = enc.length;
    }
    toString() {
        const dst = new Uint8Array(this.usedLength);
        dst.set(this._buffer.subarray(0, this.usedLength));
        return decoder.decode(dst);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

export class BaseX {
    constructor(alphabet) {
        this._alphabet = new CString(alphabet);
        this._strbuf = new CString(BaseX.estimateSymbols(8192, this._alphabet.usedLength));
    }
    static estimateBits(symbols, base) {
        return handle.instance.exports.cppcore_basex_estimate_bits(
            symbols, base);
    }
    static estimateSymbols(bits, base) {
        return handle.instance.exports.cppcore_basex_estimate_symbols(
            bits, base);
    }
    encode(v) {
        let f = null;
        if      (v.byteLength == 4)    { f = handle.instance.exports.cppcore_basex_encode32; }
        else if (v.byteLength == 8)    { f = handle.instance.exports.cppcore_basex_encode64; }
        else if (v.byteLength == 16)   { f = handle.instance.exports.cppcore_basex_encode128; }
        else if (v.byteLength == 32)   { f = handle.instance.exports.cppcore_basex_encode256; }
        else if (v.byteLength == 64)   { f = handle.instance.exports.cppcore_basex_encode512; }
        else if (v.byteLength == 128)  { f = handle.instance.exports.cppcore_basex_encode1024; }
        else if (v.byteLength == 256)  { f = handle.instance.exports.cppcore_basex_encode2048; }
        else if (v.byteLength == 512)  { f = handle.instance.exports.cppcore_basex_encode4096; }
        else if (v.byteLength == 1024) { f = handle.instance.exports.cppcore_basex_encode8192; }
        else throw new Error('invalid byteLength');
        const MAXSYMBOLS = this._strbuf.maxLength;
        const r = f(
            v._ptr,                     // inbuf ptr
            this._strbuf._ptr,          // outbuf ptr
            MAXSYMBOLS,                 // outbuf max symbols
            this._alphabet.usedLength,  // base
            this._alphabet._ptr,        // alphabet ptr
            1                           // write term 0x00
        );
        if (r < 0) throw new Error('_strbuf too small');
        this._strbuf.usedLength = (MAXSYMBOLS-r);
        return this._strbuf.toString();
    }
    decode(str, bits) {
        this._strbuf.fromString(str);
        let f = null;
        let t = null;
        if (!bits) bits = BaseX.estimateBits(str.length, this._alphabet.usedLength);
        if      (bits <= 32)   { t = UInt32;   f = handle.instance.exports.cppcore_basex_decode32; }
        else if (bits <= 64)   { t = UInt64;   f = handle.instance.exports.cppcore_basex_decode64; }
        else if (bits <= 128)  { t = UInt128;  f = handle.instance.exports.cppcore_basex_decode128; }
        else if (bits <= 256)  { t = UInt256;  f = handle.instance.exports.cppcore_basex_decode256; }
        else if (bits <= 512)  { t = UInt512;  f = handle.instance.exports.cppcore_basex_decode512; }
        else if (bits <= 1024) { t = UInt1024; f = handle.instance.exports.cppcore_basex_decode1024; }
        else if (bits <= 2048) { t = UInt2048; f = handle.instance.exports.cppcore_basex_decode2048; }
        else if (bits <= 4096) { t = UInt4096; f = handle.instance.exports.cppcore_basex_decode4096; }
        else if (bits <= 8192) { t = UInt8192; f = handle.instance.exports.cppcore_basex_decode8192; }
        else throw new Error('invalid bitlength');
        const uint = new t();
        const r = f(this._strbuf._ptr, uint._ptr, this._alphabet._ptr);
        if (r == 0) throw new Error('Invalid symbol or overflow');
        return uint;
    }
}

export class Base10 extends BaseX {
    constructor() {
        super("0123456789");
    }
    static estimateBits(symbols) {
        return super.estimateBits(symbols, 10);
    }
    static estimateSymbols(bits) {
        return super.estimateSymbols(bits, 10);
    }
}

export class Base16 extends BaseX {
    constructor() {
        super("0123456789ABCDEF");
    }
    static estimateBits(symbols) {
        return super.estimateBits(symbols, 16);
    }
    static estimateSymbols(bits) {
        return super.estimateSymbols(bits, 16);
    }
}

export const BASE10 = new Base10();
export const BASE16 = new Base16();

/////////////////////////////////////////////////////////////////////////////////////////////

class UInt {
    constructor(size, oth) {
        this._buffer = new Buffer(size);
        if (oth) {
            this.set(oth);
        }
    }
    set(v) {
        if (v instanceof UInt) {
            if (v.byteLength <= this.byteLength) {
                this._buffer.set(v._buffer);
                this._buffer.fill(0, v.byteLength);
            }
            else {
                this._buffer.set(v._buffer.subarray(0, this.byteLength));
            }
        }
        else if (typeof v === "string") {
            if (v.startsWith("0x")) {
                // TODO: AVOID COPY
                this.set(BASE16.decode(v.substring(2), this.bitLength));
            }
            else {
                // TODO: AVOID COPY
                this.set(BASE10.decode(v, this.bitLength));
            }
        }
        else throw new Error("Can't set UInt from parameter.")
    }
    toString(b) {
        if   (!b || b == 10) return BASE10.encode(this);
        else if (b == 16)    return BASE16.encode(this);
        else throw new Error("Unsupported base for toString() on UInt");
    }

    shl(v) { this.constructor.shl(this, v, this); return this; }
    shr(v) { this.constructor.shr(this, v, this); return this; }
    add(v) { this.constructor.add(this, v, this); return this; }
    sub(v) { this.constructor.sub(this, v, this); return this; }
    mul(v) { this.constructor.mul(this, v, this); return this; }
    div(b, r) { this.constructor.divmod(this, b, this, r); return this; }
    mod(b, q) { this.constructor.divmod(this, b, q, this); return this; }
    //mulmod(b,m) { this.constructor.mulmod(this, b, m, this); return this; }
    //powmod(b,m) { this.constructor.powmod(this, b, m, this); return this; }
    
    gcd(v) { this.constructor.gcd(this, v, this); return this; }

    get byteLength() { return this._buffer.byteLength; }
    get bitLength()  { return this._buffer.bitLength; }
    get _ptr() { return this._buffer.byteOffset; }
}

export class UInt32 extends UInt {
    constructor(v) { super(4, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint32_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint32_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint32_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint32_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint32_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt32(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt32(b);
        handle.instance.exports.cppcore_uint32_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint32_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint32_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint32_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt64 extends UInt {
    constructor(v) { super(8, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint64_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint64_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint64_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint64_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint64_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt64(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt64(b);
        handle.instance.exports.cppcore_uint64_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint64_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint64_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint64_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt128 extends UInt {
    constructor(v) { super(16, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint128_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint128_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint128_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint128_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint128_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt128(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt128(b);
        handle.instance.exports.cppcore_uint128_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint128_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint128_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint128_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt256 extends UInt {
    constructor(v) { super(32, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint256_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint256_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint256_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint256_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint256_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt256(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt256(b);
        handle.instance.exports.cppcore_uint256_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint256_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint256_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint256_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt512 extends UInt {
    constructor(v) { super(64, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint512_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint512_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint512_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint512_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint512_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt512(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt512(b);
        handle.instance.exports.cppcore_uint512_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint512_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint512_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint512_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt1024 extends UInt {
    constructor(v) { super(128, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint1024_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint1024_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint1024_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint1024_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint1024_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt1024(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt1024(b);
        handle.instance.exports.cppcore_uint1024_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint1024_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint1024_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint1024_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt2048 extends UInt {
    constructor(v) { super(256, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint2048_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint2048_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint2048_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint2048_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint2048_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt2048(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt2048(b);
        handle.instance.exports.cppcore_uint2048_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint2048_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint2048_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint2048_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt4096 extends UInt {
    constructor(v) { super(512, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint4096_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint4096_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint4096_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint4096_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint4096_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt4096(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt4096(b);
        handle.instance.exports.cppcore_uint4096_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint4096_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint4096_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint4096_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt8192 extends UInt {
    constructor(v) { super(1024, v); }
    static shl(a, b, r) { handle.instance.exports.cppcore_uint8192_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { handle.instance.exports.cppcore_uint8192_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { handle.instance.exports.cppcore_uint8192_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { handle.instance.exports.cppcore_uint8192_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { handle.instance.exports.cppcore_uint8192_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { 
        if (a._ptr == q._ptr || a._ptr == r._ptr) a = new UInt8192(a);
        if (b._ptr == q._ptr || b._ptr == r._ptr) b = new UInt8192(b);
        handle.instance.exports.cppcore_uint8192_divmod(a._ptr, b._ptr, q._ptr, r._ptr);
    }
    static mulmod(a, b, m, r) { handle.instance.exports.cppcore_uint8192_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { handle.instance.exports.cppcore_uint8192_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { handle.instance.exports.cppcore_uint8192_gcd(a._ptr, b._ptr, r._ptr); }
}

/////////////////////////////////////////////////////////////////////////////////////////////

export class AES {
    constructor() {
        console.log("Constructing...");
        this._ptr = handle.instance.exports.cppcore_aes128_init();
        console.log("Constructed at: " + this._ptr);
        registry.register(this, this._ptr);
    }
    reset(key) {
        if (key.byteLength != 16) {
            throw new Error('Key must be 16 bytes');
        }
        handle.instance.exports.cppcore_aes128_reset(this._ptr, key._ptr);
    }
    encrypt(data_in, data_out, n) {
        handle.instance.exports.cppcore_aes128_encrypt_ecb(
            this._ptr, data_in._ptr, data_out._ptr, n);
    }
    decrypt(data_in, data_out, n) {
        handle.instance.exports.cppcore_aes128_decrypt_ecb(
            this._ptr, data_in._ptr, data_out._ptr, n);
    }
}

AES.Key = class Key extends Buffer {
    constructor() {
        super(16);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////
