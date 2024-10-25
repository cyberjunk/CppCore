
const imports = { 
  "wasi_snapshot_preview1": {
    sched_yield() {
      return 0; 
    },
    random_get(ptr, len) {
      const mem = EXPORTS.memory.buffer
      const arr = new Uint8Array(mem, ptr, len);
      self.crypto.getRandomValues(arr);
      return 0;
    }
  }
}

const handle = await WebAssembly
  .instantiateStreaming(fetch('libcppcore.wasm'), imports)
  .then(lib => {
    console.debug("libcppcore: Library loaded")
    //console.debug("libcppcore: Exports")
    //console.debug(lib.instance.exports);
    
    /*console.debug("Memory Buffer Size")
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

const EXPORTS = handle.instance.exports;

const registry = new FinalizationRegistry((ptr) => {
  EXPORTS.cppcore_free(ptr);
});

const encoder = new TextEncoder();
const decoder = new TextDecoder();

/////////////////////////////////////////////////////////////////////////////////////////////

function alloc(size) {
  const ptr = handle.instance.exports.cppcore_alloc(size);
  if (ptr == 0) throw new Error('libcppcore: Out of Memory');
  return ptr;
}

function hexStrFromInt(v) {
  return "0x" + v.toString(16).padStart(8, '0');
}

/////////////////////////////////////////////////////////////////////////////////////////////
// BUFFER
/////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Memory Allocation on the WASM linear memory
 * Note: This is not compatible with growing memory
 * because all existing instances will point to the old memory
 */
export class Buffer extends Uint8Array {
  constructor(parm1, parm2, parm3) {
    console.debug("libcppcore: Constructing Buffer (" + 
      typeof(parm1) + "," + 
      typeof(parm2) + "," + 
      typeof(parm3) + ")");
    if (parm1 instanceof Uint8Array) {
      //console.debug("libcppcore: Copy Buffer from Uint8Array");
      const ptr = alloc(parm1.byteLength);
      super(EXPORTS.memory.buffer, ptr, parm1.byteLength);
      this.set(parm1);
      registry.register(this, ptr, this);
    }
    else if (parm1 == EXPORTS.memory.buffer) {
      //console.debug("libcppcore: Creating view on existing Buffer");
      super(EXPORTS.memory.buffer, parm2, parm3);
    }
    else if (!isNaN(parm1)) {
      //console.debug("libcppcore: Creating Buffer from size=" + parm1);
      const ptr = alloc(parm1);
      super(EXPORTS.memory.buffer, ptr, parm1);
      registry.register(this, ptr, this);
    }
    else if (parm1 instanceof Array) {
      //console.debug("libcppcore: Copy Buffer from Array");
      const ptr = alloc(parm1.length);
      super(EXPORTS.memory.buffer, ptr, parm1.length);
      this.set(parm1);
      registry.register(this, ptr, this);
    }
    else {
      throw new Error("libcppcore: Invalid constructor arguments for Buffer");
    }
  }
  free() {
    registry.unregister(this);
    EXPORTS.cppcore_free(this._ptr);
  }
  get bitLength() {
    return this.byteLength << 3;
  }
  get _ptr() {
    return this.byteOffset;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// CSTRING
/////////////////////////////////////////////////////////////////////////////////////////////

export class CString {
  constructor(v) {
    console.debug("libcppcore: Constructing CString (" + typeof(v) + ")");
    const type = typeof(v);
    if (type === 'string') {
      this._buffer = new Buffer(v.length+1);
      this.fromString(v);
    }
    else if (type === 'undefined') {
      this._buffer = new Buffer(16);
      this.byteLength = 0;
    }
    else if (Number.isInteger(v)) {
      this._buffer = new Buffer(v+1);
      this.byteLength = 0;
    }
    else if (v instanceof CString) {
      this._buffer = new Buffer(v._buffer);
      this.byteLength = v.byteLength;
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
  free() {
    this._buffer.free();
  }
  fromString(str) {
    const result = encoder.encodeInto(str, this._buffer);
    if (this.maxLength < result.written)
        throw new Error('String too big.');
    this._buffer[result.written] = 0x00;
    this.byteLength = result.written;
  }
  toString() {
    return decoder.decode(this._buffer.subarray(0, this.byteLength));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// BASEX
/////////////////////////////////////////////////////////////////////////////////////////////

export class BaseX {
    constructor(alphabet) {
        this._alphabet = new CString(alphabet);
        this._strbuf = new CString(BaseX.estimateSymbols(8192, this._alphabet.byteLength));
    }
    static estimateBits(symbols, base) {
        return EXPORTS.cppcore_basex_estimate_bits(
            symbols, base);
    }
    static estimateSymbols(bits, base) {
        return EXPORTS.cppcore_basex_estimate_symbols(
            bits, base);
    }
    encode(v) {
        let f = null;
        if      (v.byteLength == 4)    { f = EXPORTS.cppcore_basex_encode32; }
        else if (v.byteLength == 8)    { f = EXPORTS.cppcore_basex_encode64; }
        else if (v.byteLength == 16)   { f = EXPORTS.cppcore_basex_encode128; }
        else if (v.byteLength == 32)   { f = EXPORTS.cppcore_basex_encode256; }
        else if (v.byteLength == 64)   { f = EXPORTS.cppcore_basex_encode512; }
        else if (v.byteLength == 128)  { f = EXPORTS.cppcore_basex_encode1024; }
        else if (v.byteLength == 256)  { f = EXPORTS.cppcore_basex_encode2048; }
        else if (v.byteLength == 512)  { f = EXPORTS.cppcore_basex_encode4096; }
        else if (v.byteLength == 1024) { f = EXPORTS.cppcore_basex_encode8192; }
        else throw new Error('invalid byteLength');
        const MAXSYMBOLS = this._strbuf.maxLength;
        const r = f(
            v._ptr,                     // inbuf ptr
            this._strbuf._ptr,          // outbuf ptr
            MAXSYMBOLS,                 // outbuf max symbols
            this._alphabet.byteLength,  // base
            this._alphabet._ptr,        // alphabet ptr
            1                           // write term 0x00
        );
        if (r < 0) throw new Error('_strbuf too small');
        this._strbuf.byteLength = (MAXSYMBOLS-r);
        return this._strbuf.toString();
    }
    decode(str, bits) {
        this._strbuf.fromString(str);
        let f = null;
        let t = null;
        if (!bits) bits = BaseX.estimateBits(this._strbuf.byteLength, this._alphabet.byteLength);
        if      (bits <= 32)   { t = UInt32;   f = EXPORTS.cppcore_basex_decode32; }
        else if (bits <= 64)   { t = UInt64;   f = EXPORTS.cppcore_basex_decode64; }
        else if (bits <= 128)  { t = UInt128;  f = EXPORTS.cppcore_basex_decode128; }
        else if (bits <= 256)  { t = UInt256;  f = EXPORTS.cppcore_basex_decode256; }
        else if (bits <= 512)  { t = UInt512;  f = EXPORTS.cppcore_basex_decode512; }
        else if (bits <= 1024) { t = UInt1024; f = EXPORTS.cppcore_basex_decode1024; }
        else if (bits <= 2048) { t = UInt2048; f = EXPORTS.cppcore_basex_decode2048; }
        else if (bits <= 4096) { t = UInt4096; f = EXPORTS.cppcore_basex_decode4096; }
        else if (bits <= 8192) { t = UInt8192; f = EXPORTS.cppcore_basex_decode8192; }
        else throw new Error('invalid bitlength');
        const uint = new t();
        const r = f(this._strbuf._ptr, uint._ptr, this._alphabet._ptr);
        if (r == 0) throw new Error('Invalid symbol or overflow');
        return uint;
    }
    decodeInto(str, buf) {
        this._strbuf.fromString(str);
        const byteLength = buf.byteLength;
        let f = null;
        if      (byteLength == 4)    { f = EXPORTS.cppcore_basex_decode32; }
        else if (byteLength == 8)    { f = EXPORTS.cppcore_basex_decode64; }
        else if (byteLength == 16)   { f = EXPORTS.cppcore_basex_decode128; }
        else if (byteLength == 32)   { f = EXPORTS.cppcore_basex_decode256; }
        else if (byteLength == 64)   { f = EXPORTS.cppcore_basex_decode512; }
        else if (byteLength == 128)  { f = EXPORTS.cppcore_basex_decode1024; }
        else if (byteLength == 256)  { f = EXPORTS.cppcore_basex_decode2048; }
        else if (byteLength == 512)  { f = EXPORTS.cppcore_basex_decode4096; }
        else if (byteLength == 1024) { f = EXPORTS.cppcore_basex_decode8192; }
        else throw new Error('invalid bytelength');
        const r = f(this._strbuf._ptr, buf._ptr, this._alphabet._ptr);
        if (r == 0) throw new Error('Invalid symbol or overflow');
    }
}

export class Base02 extends BaseX {
  constructor() {
    super("01");
  }
  static estimateBits(symbols) {
    return super.estimateBits(symbols, 2);
  }
  static estimateSymbols(bits) {
    return super.estimateSymbols(bits, 2);
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

export const BASE02 = new Base02();
export const BASE10 = new Base10();
export const BASE16 = new Base16();

/////////////////////////////////////////////////////////////////////////////////////////////
// UINT
/////////////////////////////////////////////////////////////////////////////////////////////

class UInt {
    constructor(size, oth) {
      this._buffer = new Buffer(size);
      if (oth) {
        this.set(oth);
      }
    }
    static fromString(s) {
      if (s.startsWith("0x")) {
        return BASE16.decode(s.substring(2));
      } else if (s.startsWith("0b")) {
        return BASE02.decode(s.substring(2));
      } else {
        return BASE10.decode(s);
      }
    }
    free() {
      this._buffer.free();
    }
    set(v) {
        if (v instanceof UInt) {
            this.set(v._buffer);
        }
        else if (typeof v === "string") {
            if (v.startsWith("0x")) {
                BASE16.decodeInto(v.substring(2), this._buffer);
            } else if (v.startsWith("0b")) {
                BASE02.decodeInto(v.substring(2), this._buffer);
            } else {
                BASE10.decodeInto(v, this._buffer);
            }
        }
        else if (v instanceof Uint8Array) {
            if (v.byteLength <= this.byteLength) {
                this._buffer.set(v);
                this._buffer.fill(0, v.byteLength);
            }
            else {
                this._buffer.set(v.subarray(0, this.byteLength));
            }
        }
        else if (v instanceof Array) {
            this._buffer.set(v);
            this._buffer.fill(0, v.length);
        }
        else throw new Error("Can't set UInt from parameter.")
    }
    toString(b) {
        if   (!b || b == 10) return BASE10.encode(this);
        else if (b == 16)    return BASE16.encode(this);
        else if (b == 2)     return BASE02.encode(this);
        else throw new Error("Unsupported base for toString() on UInt");
    }

    get byteLength() { return this._buffer.byteLength; }
    get bitLength()  { return this._buffer.bitLength; }
    get _ptr() { return this._buffer.byteOffset; }
}

export class UInt32 extends UInt {
    constructor(v) { super(4, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint32_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint32_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint32_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint32_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint32_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint32_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint32_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint32_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint32_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt64 extends UInt {
    constructor(v) { super(8, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint64_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint64_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint64_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint64_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint64_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint64_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint64_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint64_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint64_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt128 extends UInt {
    constructor(v) { super(16, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint128_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint128_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint128_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint128_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint128_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint128_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint128_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint128_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint128_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt256 extends UInt {
    constructor(v) { super(32, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint256_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint256_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint256_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint256_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint256_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint256_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint256_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint256_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint256_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt512 extends UInt {
    constructor(v) { super(64, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint512_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint512_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint512_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint512_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint512_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint512_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint512_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint512_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint512_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt1024 extends UInt {
    constructor(v) { super(128, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint1024_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint1024_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint1024_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint1024_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint1024_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint1024_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint1024_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint1024_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint1024_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt2048 extends UInt {
    constructor(v) { super(256, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint2048_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint2048_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint2048_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint2048_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint2048_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint2048_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint2048_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint2048_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint2048_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt4096 extends UInt {
    constructor(v) { super(512, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint4096_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint4096_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint4096_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint4096_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint4096_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint4096_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint4096_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint4096_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint4096_gcd(a._ptr, b._ptr, r._ptr); }
}
export class UInt8192 extends UInt {
    constructor(v) { super(1024, v); }
    static shl(a, b, r) { EXPORTS.cppcore_uint8192_shl(a._ptr, b, r._ptr);}
    static shr(a, b, r) { EXPORTS.cppcore_uint8192_shr(a._ptr, b, r._ptr);}
    static add(a, b, r) { EXPORTS.cppcore_uint8192_add(a._ptr, b._ptr, r._ptr); }
    static sub(a, b, r) { EXPORTS.cppcore_uint8192_sub(a._ptr, b._ptr, r._ptr); }
    static mul(a, b, r) { EXPORTS.cppcore_uint8192_mul(a._ptr, b._ptr, r._ptr); }
    static divmod(a, b, q, r) { EXPORTS.cppcore_uint8192_divmod(a._ptr, b._ptr, q._ptr, r._ptr); }
    static mulmod(a, b, m, r) { EXPORTS.cppcore_uint8192_mulmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static powmod(a, b, m, r) { EXPORTS.cppcore_uint8192_powmod(a._ptr, b._ptr, m._ptr, r._ptr); }
    static gcd(a, b, r) { EXPORTS.cppcore_uint8192_gcd(a._ptr, b._ptr, r._ptr); }
}

UInt32.MAX   = new UInt32();   UInt32.MAX._buffer.fill(0xFF);
UInt64.MAX   = new UInt64();   UInt64.MAX._buffer.fill(0xFF);
UInt128.MAX  = new UInt128();  UInt128.MAX._buffer.fill(0xFF);
UInt256.MAX  = new UInt256();  UInt256.MAX._buffer.fill(0xFF);
UInt512.MAX  = new UInt512();  UInt512.MAX._buffer.fill(0xFF);
UInt1024.MAX = new UInt1024(); UInt1024.MAX._buffer.fill(0xFF);
UInt2048.MAX = new UInt2048(); UInt2048.MAX._buffer.fill(0xFF);
UInt4096.MAX = new UInt4096(); UInt4096.MAX._buffer.fill(0xFF);
UInt8192.MAX = new UInt8192(); UInt8192.MAX._buffer.fill(0xFF);

/////////////////////////////////////////////////////////////////////////////////////////////
// AES
/////////////////////////////////////////////////////////////////////////////////////////////

class AES {
  constructor(bits) {
    switch(bits) {
      case 128:
        this._bits = 128;
        this._ptr  = EXPORTS.cppcore_aes128_init();
        break;
      case 192:
        this._bits = 192;
        this._ptr  = EXPORTS.cppcore_aes192_init();
        break;
      case 256:
        this._bits = 256;
        this._ptr  = EXPORTS.cppcore_aes256_init();
        break;
      default:
        throw new Error("Invalid bits for AES. Must be 128, 192 or 256.");
    }
    registry.register(this, this._ptr);
  }
  setKey(key) {
    if (key instanceof CString ||
        key instanceof Buffer) {
      switch(this._bits) {
        case 128:
          if (key.byteLength != 16)
            throw new Error("Key must have exactly 16 bytes for AES128");
          EXPORTS.cppcore_aes128_reset(this._ptr, key._ptr);
          break;
        case 192:
          if (key.byteLength != 24)
            throw new Error("Key must have exactly 24 bytes for AES192");
          EXPORTS.cppcore_aes192_reset(this._ptr, key._ptr);
          break;
        case 256:
          if (key.byteLength != 32)
            throw new Error("Key must have exactly 32 bytes for AES256");
          EXPORTS.cppcore_aes256_reset(this._ptr, key._ptr);
          break;
      }
    }
    else if (typeof key === "string") {
      this.setKey(new CString(key));
    }
    else if (key instanceof Uint8Array) {
      this.setKey(new Buffer(key));
    }
    else {
      throw new Error("No valid key provided in setKey()");
    }
  }
}

class AESIV extends AES {
  constructor(bits) { 
    super(bits);
  }
  setIV(iv) {
    if (iv instanceof Uint8Array) {
      if (iv.byteLength != 16)
        throw new Error("Binary IV must have exactly 16 bytes");
      this._iv_enc = new Buffer(iv);
      this._iv_dec = new Buffer(iv);
    }
    else if (iv instanceof CString) {
      if (iv.byteLength != 16)
        throw new Error("String IV must have exactly 16 bytes.");
      this.setIV(iv._buffer.subarray(0, 16));
    }
    else if (typeof iv === "string") {
      this.setIV(new CString(iv));
    }
    else {
      throw new Error("No valid IV provided in setIV()");
    }
  }
}

export class AES128ECB extends AES {
  constructor() {
    super(128);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes128_encrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes128_decrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
}
export class AES192ECB extends AES {
  constructor() {
    super(192);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes192_encrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes192_decrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
}
export class AES256ECB extends AES {
  constructor() {
    super(256);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes256_encrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes256_decrypt_ecb(
      this._ptr, data_in._ptr, data_out._ptr, n);
  }
}

export class AES128CBC extends AESIV {
  constructor() {
    super(128);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes128_encrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes128_decrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, n);
  }
}
export class AES192CBC extends AESIV {
  constructor() {
    super(192);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes192_encrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes192_decrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, n);
  }
}
export class AES256CBC extends AESIV {
  constructor() {
    super(256);
  }
  encrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes256_encrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, n);
  }
  decrypt(data_in, data_out, n) {
    EXPORTS.cppcore_aes256_decrypt_cbc(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, n);
  }
}

export class AES128CTR extends AESIV {
  constructor() {
    super(128);
  }
  encrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes128_encrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, len);
  }
  decrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes128_decrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, len);
  }
}
export class AES192CTR extends AESIV {
  constructor() {
    super(192);
  }
  encrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes192_encrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, len);
  }
  decrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes192_decrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, len);
  }
}
export class AES256CTR extends AESIV {
  constructor() {
    super(256);
  }
  encrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes256_encrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_enc._ptr, len);
  }
  decrypt(data_in, data_out, len) {
    EXPORTS.cppcore_aes256_decrypt_ctr(
      this._ptr, data_in._ptr, data_out._ptr, this._iv_dec._ptr, len);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// HASH
/////////////////////////////////////////////////////////////////////////////////////////////

class Hash {
  constructor(f) {
    this._ptr = f();
    registry.register(this, this._ptr);
  }
  _reset(f) {
    f(this._ptr);
  }
  _step(data, f) {
    if (data instanceof Buffer || data instanceof UInt || data instanceof CString) {
      f(this._ptr, data._ptr, data.byteLength);
    }
    else if (typeof data === "string") {
      const d = new CString(data);
      this._step(d, f);
      d.free();
    }
    else if (data instanceof Uint8Array) {
      const d = new Buffer(data);
      this._step(d, f);
      d.free();
    }
    else {
      throw new Error("Unsupported type of data in Hash.step()");
    }
  }
  _finish(digest, f) {
    if (digest instanceof Buffer || digest instanceof UInt) {
      if (digest.byteLength != this.constructor.digestLength) {
        throw new Error("Unsupported size of digest in Hash.finish()");
      }
      f(this._ptr, digest._ptr);
    }
    else if (digest instanceof Uint8Array) {
      const d = new Buffer(digest.byteLength);
      this._finish(d, f);
      digest.set(d);
      d.free();
    }
    else {
      throw new Error("Unsupported type of digest in Hash.finish()");
    }
  }
}

export class MD5 extends Hash {
  static get digestLength() { return 16; }
  constructor() { super(EXPORTS.cppcore_md5_init); }
  reset() { super._reset(EXPORTS.cppcore_md5_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_md5_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_md5_finish); }
}
export class SHA256 extends Hash {
  static get digestLength() { return 32; }
  constructor() { super(EXPORTS.cppcore_sha256_init); }
  reset() { super._reset(EXPORTS.cppcore_sha256_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_sha256_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_sha256_finish); }
}
export class SHA512 extends Hash {
  static get digestLength() { return 64; }
  constructor() { super(EXPORTS.cppcore_sha512_init); }
  reset() { super._reset(EXPORTS.cppcore_sha512_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_sha512_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_sha512_finish); }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// HMAC
/////////////////////////////////////////////////////////////////////////////////////////////

class HMAC {
  constructor(f) {
    this._ptr = f();
    registry.register(this, this._ptr);
  }
  _reset(key, f) {
    if (key instanceof Buffer || key instanceof UInt || key instanceof CString) {
      f(this._ptr, key._ptr, key.byteLength);
    }
    else if (typeof key === "string") {
      const k = new CString(key);
      this._reset(k, f);
      k.free();
    }
    else if (key instanceof Uint8Array) {
      const k = new Buffer(key);
      this._reset(k, f);
      k.free();
    }
    else {
      throw new Error("Unsupported type of key in HMAC.reset()");
    }
  }
  _step(data, f) {
    if (data instanceof Buffer || data instanceof UInt || data instanceof CString) {
      f(this._ptr, data._ptr, data.byteLength);
    }
    else if (typeof data === "string") {
      const d = new CString(data);
      this._step(d, f);
      d.free();
    }
    else if (data instanceof Uint8Array) {
      const d = new Buffer(data);
      this._step(d, f);
      d.free();
    }
    else {
      throw new Error("Unsupported type of data in HMAC.step()");
    }
  }
  _finish(digest, f) {
    if (digest instanceof Buffer || digest instanceof UInt) {
      if (digest.byteLength != this.constructor.digestLength) {
        throw new Error("Unsupported size of digest in HMAC.finish()");
      }
      f(this._ptr, digest._ptr);
    }
    else if (digest instanceof Uint8Array) {
      const d = new Buffer(digest.byteLength);
      this._finish(d, f);
      digest.set(d);
      d.free();
    }
    else {
      throw new Error("Unsupported type of digest in HMAC.finish()");
    }
  }
}

export class HMACMD5 extends HMAC {
  static get digestLength() { return 16; }
  constructor() { super(EXPORTS.cppcore_hmac_md5_init); }
  reset(key) { super._reset(key, EXPORTS.cppcore_hmac_md5_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_hmac_md5_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_hmac_md5_finish); }
}
export class HMACSHA256 extends HMAC {
  static get digestLength() { return 32; }
  constructor() { super(EXPORTS.cppcore_hmac_sha256_init); }
  reset(key) { super._reset(key, EXPORTS.cppcore_hmac_sha256_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_hmac_sha256_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_hmac_sha256_finish); }
}
export class HMACSHA512 extends HMAC {
  static get digestLength() { return 64; }
  constructor() { super(EXPORTS.cppcore_hmac_sha512_init); }
  reset(key) { super._reset(key, EXPORTS.cppcore_hmac_sha512_reset); }
  step(data) { super._step(data, EXPORTS.cppcore_hmac_sha512_step); }
  finish(digest) { super._finish(digest, EXPORTS.cppcore_hmac_sha512_finish); }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// PBKDF2
/////////////////////////////////////////////////////////////////////////////////////////////

export class PBKDF2 {
  static _run(password, salt, digest, iterations, f) {
    if ((password instanceof Buffer || password instanceof UInt || password instanceof CString) &&
        (salt     instanceof Buffer || salt     instanceof UInt || salt     instanceof CString) &&
        (digest   instanceof Buffer || digest   instanceof UInt) &&
        (Number.isInteger(iterations))) {
      f(password._ptr, password.byteLength,
        salt._ptr,     salt.byteLength,
        digest._ptr,   digest.byteLength,
        iterations);
    }
    else if (typeof password === "string") {
      const p = new CString(password);
      PBKDF2._run(p, salt, digest, iterations, f);
      p.free();
    }
    else if (typeof salt === "string") {
      const s = new CString(salt);
      PBKDF2._run(password, s, digest, iterations, f);
      s.free();
    }
    else if (password instanceof Uint8Array && !(password instanceof Buffer)) {
      const p = new Buffer(password);
      PBKDF2._run(p, salt, digest, iterations, f);
      p.free();
    }
    else if (salt instanceof Uint8Array && !(salt instanceof Buffer)) {
      const s = new Buffer(salt);
      PBKDF2._run(password, s, digest, iterations, f);
      s.free();
    }
    else if (digest instanceof Uint8Array && !(digest instanceof Buffer)) {
      const d = new Buffer(digest.byteLength);
      PBKDF2._run(password, salt, d, iterations, f);
      digest.set(d);
      d.free();
    }
    else throw new Error("Unsupported parameters in PBKDF2");
  }
  static md5(password, salt, digest, iterations) {
    PBKDF2._run(password, salt, digest, iterations, 
      EXPORTS.cppcore_pbkdf2_md5_create);
  }
  static sha256(password, salt, digest, iterations) {
    PBKDF2._run(password, salt, digest, iterations, 
      EXPORTS.cppcore_pbkdf2_sha256_create);
  }
  static sha512(password, salt, digest, iterations) {
    PBKDF2._run(password, salt, digest, iterations, 
      EXPORTS.cppcore_pbkdf2_sha512_create);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// DH
/////////////////////////////////////////////////////////////////////////////////////////////
//TODO

/////////////////////////////////////////////////////////////////////////////////////////////
// PRIMES
/////////////////////////////////////////////////////////////////////////////////////////////

export class Prime {
  static Result = {
    NotPrime:    0,
    Prime:       1,
    LikelyPrime: 2
  };
  static test(p, sign, certainty) {
    if (typeof p === "string") {
      const n = UInt.fromString(p);
      const r = Prime.test(n, sign, certainty);
      n.free();
      return r;
    }
    if (!(p instanceof UInt) && !(p instanceof Buffer)) {
      throw new Error("libcppcore: Invalid type of p in Prime.test()");
    }
    switch(p.byteLength) {
      case 4:   return EXPORTS.cppcore_prime32_test(p._ptr, sign, certainty);
      case 8:   return EXPORTS.cppcore_prime64_test(p._ptr, sign, certainty);
      case 16:  return EXPORTS.cppcore_prime128_test(p._ptr, sign, certainty);
      case 32:  return EXPORTS.cppcore_prime256_test(p._ptr, sign, certainty);
      case 64:  return EXPORTS.cppcore_prime512_test(p._ptr, sign, certainty);
      case 128: return EXPORTS.cppcore_prime1024_test(p._ptr, sign, certainty);
      case 256: return EXPORTS.cppcore_prime2048_test(p._ptr, sign, certainty);
      case 512: return EXPORTS.cppcore_prime4096_test(p._ptr, sign, certainty);
      default:  throw new Error("libcppcore: Invalid byteLength of p in Prime.test()");
    }
  }
  static generate(p, sign, certainty) {
    if (!(p instanceof UInt) && !(p instanceof Buffer)) {
      throw new Error("libcppcore: Invalid type of p in Prime.generate()");
    }
    switch(p.byteLength) {
      case 4:   return EXPORTS.cppcore_prime32_generate(p._ptr, sign, certainty);
      case 8:   return EXPORTS.cppcore_prime64_generate(p._ptr, sign, certainty);
      case 16:  return EXPORTS.cppcore_prime128_generate(p._ptr, sign, certainty);
      case 32:  return EXPORTS.cppcore_prime256_generate(p._ptr, sign, certainty);
      case 64:  return EXPORTS.cppcore_prime512_generate(p._ptr, sign, certainty);
      case 128: return EXPORTS.cppcore_prime1024_generate(p._ptr, sign, certainty);
      case 256: return EXPORTS.cppcore_prime2048_generate(p._ptr, sign, certainty);
      case 512: return EXPORTS.cppcore_prime4096_generate(p._ptr, sign, certainty);
      default:  throw new Error("libcppcore: Invalid byteLength of p in Prime.generate()");
    }
  }
}
