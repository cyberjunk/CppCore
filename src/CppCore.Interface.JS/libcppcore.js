
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
        this._strbuf = new CString(8192);
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
        let l = null;
        if (!bits) bits = BaseX.estimateBits(str.length, this._alphabet.usedLength);
        if (bits < 32) bits = 32;
        if      (bits <= 32)   { l = 4;    f = handle.instance.exports.cppcore_basex_decode32; }
        else if (bits <= 64)   { l = 8;    f = handle.instance.exports.cppcore_basex_decode64; }
        else if (bits <= 128)  { l = 16;   f = handle.instance.exports.cppcore_basex_decode128; }
        else if (bits <= 256)  { l = 32;   f = handle.instance.exports.cppcore_basex_decode256; }
        else if (bits <= 512)  { l = 64;   f = handle.instance.exports.cppcore_basex_decode512; }
        else if (bits <= 1024) { l = 128;  f = handle.instance.exports.cppcore_basex_decode1024; }
        else if (bits <= 2048) { l = 256;  f = handle.instance.exports.cppcore_basex_decode2048; }
        else if (bits <= 4096) { l = 512;  f = handle.instance.exports.cppcore_basex_decode4096; }
        else if (bits <= 8192) { l = 1024; f = handle.instance.exports.cppcore_basex_decode8192; }
        else throw new Error('invalid bitlength');
        const obuf = new Buffer(l);
        const r = f(this._strbuf._ptr, obuf._ptr, this._alphabet._ptr);
        if (r == 0) throw new Error('Invalid symbol or overflow');
        return obuf;
    }
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
