const IMPORTS = { 
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

const HANDLE = await WebAssembly
  .instantiateStreaming(fetch('libcppcore.wasm'), IMPORTS)
  .then(lib => {
    console.debug("Library loaded")
    return lib;
});

const EXPORTS = HANDLE.instance.exports;

const REGISTRY = new FinalizationRegistry((ptr) => {
  EXPORTS.cppcore_free(ptr);
});

const ENCODER = new TextEncoder();
const DECODER = new TextDecoder();

function alloc(size) {
  const ptr = EXPORTS.cppcore_alloc(size);
  if (ptr == 0) throw new Error('Out of Memory');
  return ptr;
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
    console.debug("Constructing Buffer (" + 
      typeof(parm1) + "," + 
      typeof(parm2) + "," + 
      typeof(parm3) + ")");
    if (parm1 instanceof Uint8Array) {
      const ptr = alloc(parm1.byteLength);
      super(EXPORTS.memory.buffer, ptr, parm1.byteLength);
      this.set(parm1);
      REGISTRY.register(this, ptr, this);
    }
    else if (parm1 == EXPORTS.memory.buffer) {
      super(EXPORTS.memory.buffer, parm2, parm3);
    }
    else if (!isNaN(parm1)) {
      const ptr = alloc(parm1);
      super(EXPORTS.memory.buffer, ptr, parm1);
      REGISTRY.register(this, ptr, this);
    }
    else if (parm1 instanceof Array) {
      const ptr = alloc(parm1.length);
      super(EXPORTS.memory.buffer, ptr, parm1.length);
      this.set(parm1);
      REGISTRY.register(this, ptr, this);
    }
    else {
      throw new TypeError("Invalid constructor parameters in Buffer");
    }
  }
  free() {
    REGISTRY.unregister(this);
    EXPORTS.cppcore_free(this.ptr);
  }
  get bitLength() {
    return this.byteLength << 3;
  }
  get ptr() {
    return this.byteOffset;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// CSTRING
/////////////////////////////////////////////////////////////////////////////////////////////

export class CString {
  #buffer
  constructor(v) {
    console.debug("Constructing CString (" + typeof(v) + ")");
    const type = typeof(v);
    if (type === 'string') {
      this.#buffer = new Buffer(v.length+1);
      this.set(v);
    }
    else if (type === 'undefined') {
      this.#buffer = new Buffer(16);
      this.byteLength = 0;
    }
    else if (Number.isInteger(v)) {
      this.#buffer = new Buffer(v+1);
      this.byteLength = 0;
    }
    else if (v instanceof CString) {
      this.#buffer = new Buffer(v.buffer);
      this.byteLength = v.byteLength;
    }
    else {
      throw new TypeError('Invalid constructor parameter in CString');
    }
  }
  get buffer() {
    return this.#buffer;
  }
  get maxLength() {
    return this.#buffer.byteLength - 1;
  }
  get ptr() {
    return this.#buffer.ptr;
  }
  free() {
    this.#buffer.free();
  }
  resize(size) {
    if (!size) {
      size = this.byteLength;
    }
    if (size == this.maxLength) {
      return;
    }
    else if (size < this.byteLength) {
      throw new RangeError("Can't shrink CString below current use")
    }
    else {
      const buf = new Buffer(size+1);
      buf.set(this.#buffer.subarray(0, this.byteLength));
      buf[this.byteLength] = 0x00;
      this.#buffer.free();
      this.#buffer = buf;
    }
  }
  set(str) {
    if (typeof str === "string") {
      const result = ENCODER.encodeInto(str, this.#buffer);
      if (this.maxLength < result.written) {
        this.#buffer[this.maxLength] = 0x00;
        this.byteLength = this.maxLength;
        throw new RangeError('String too big in CString.set()');
      }
      this.#buffer[result.written] = 0x00;
      this.byteLength = result.written;
    }
    else if (str instanceof CString) {
      if (this.maxLength < str.byteLength) {
        this.#buffer.set(str.buffer.subarray(0, this.maxLength));
        this.#buffer[this.maxLength] = 0x00;
        this.byteLength = this.maxLength;
        throw new RangeError("CString too big in CString.set()")
      }
      this.#buffer.set(str.buffer);
      this.#buffer[str.byteLength] = 0x00;
      this.byteLength = str.byteLength;
    }
    else {
      throw new TypeError("Invalid parameter in CString.set()")
    }
  }
  toString() {
    return DECODER.decode(this.#buffer.subarray(0, this.byteLength));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// BASEX
/////////////////////////////////////////////////////////////////////////////////////////////

export class BaseX {
  #alphabet
  #strbuf
  constructor(alphabet) {
    this.#alphabet = new CString(alphabet);
    this.#strbuf = new CString(BaseX.estimateSymbols(8192, this.#alphabet.byteLength));
  }
  get alphabet() { return this.#alphabet; }
  get strbuf() { return this.#strbuf; }
  static estimateBits(symbols, base) {
    return EXPORTS.cppcore_basex_estimate_bits(symbols, base);
  }
  static estimateSymbols(bits, base) {
    return EXPORTS.cppcore_basex_estimate_symbols(bits, base);
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
    else throw new RangeError('Invalid byteLength in BaseX.encode()');
    const MAXSYMBOLS = this.#strbuf.maxLength;
    const r = f(
      v.ptr,                     // inbuf ptr
      this.#strbuf.ptr,          // outbuf ptr
      MAXSYMBOLS,                 // outbuf max symbols
      this.#alphabet.byteLength,  // base
      this.#alphabet.ptr,        // alphabet ptr
      1                           // write term 0x00
    );
    if (r < 0) throw new RangeError('String buffer too small in BaseX.encode()');
    this.#strbuf.byteLength = (MAXSYMBOLS-r);
    return this.#strbuf.toString();
  }
  decode(str, bits) {
    this.#strbuf.set(str);
    let f = null;
    let t = null;
    if (!bits) bits = BaseX.estimateBits(this.#strbuf.byteLength, this.#alphabet.byteLength);
    if      (bits <= 32)   { t = UInt32;   f = EXPORTS.cppcore_basex_decode32; }
    else if (bits <= 64)   { t = UInt64;   f = EXPORTS.cppcore_basex_decode64; }
    else if (bits <= 128)  { t = UInt128;  f = EXPORTS.cppcore_basex_decode128; }
    else if (bits <= 256)  { t = UInt256;  f = EXPORTS.cppcore_basex_decode256; }
    else if (bits <= 512)  { t = UInt512;  f = EXPORTS.cppcore_basex_decode512; }
    else if (bits <= 1024) { t = UInt1024; f = EXPORTS.cppcore_basex_decode1024; }
    else if (bits <= 2048) { t = UInt2048; f = EXPORTS.cppcore_basex_decode2048; }
    else if (bits <= 4096) { t = UInt4096; f = EXPORTS.cppcore_basex_decode4096; }
    else if (bits <= 8192) { t = UInt8192; f = EXPORTS.cppcore_basex_decode8192; }
    else throw new RangeError('Invalid bitLength in BaseX.decode()');
    const uint = new t();
    const r = f(this.#strbuf.ptr, uint.ptr, this.#alphabet.ptr);
    if (r == 0) throw new Error('Invalid symbol or overflow in BaseX.decode()');
    return uint;
  }
  decodeInto(str, buf) {
    this.#strbuf.set(str);
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
    else throw new RangeError('Invalid byteLength in BaseX.decodeInto()');
    const r = f(this.#strbuf.ptr, buf.ptr, this.#alphabet.ptr);
    if (r == 0) throw new Error('Invalid symbol or overflow in BaseX.decodeInto()');
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
    super("0123456789abcdef");
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
  #buffer
  constructor(size, oth) {
    this.#buffer = new Buffer(size);
    if (oth) {
      this.set(oth);
    }
  }
  static fromString(s) {
    if (s.startsWith("0x")) {
      return BASE16.decode(s.substring(2));
    }
    else if (s.startsWith("0b")) {
      return BASE02.decode(s.substring(2));
    } 
    else {
      return BASE10.decode(s);
    }
  }
  static fromInteger(v) {
    return UInt.fromString("0x" + v.toString(16));
  }
  free() {
    this.#buffer.free();
  }
  set(v) {
    if (v instanceof UInt) {
      this.set(v.buffer);
    }
    else if (typeof v === "string") {
      if (v.startsWith("0x")) {
        BASE16.decodeInto(v.substring(2), this.#buffer);
      } 
      else if (v.startsWith("0b")) {
        BASE02.decodeInto(v.substring(2), this.#buffer);
      } 
      else {
        BASE10.decodeInto(v, this.#buffer);
      }
    }
    else if (typeof v === "bigint" || Number.isInteger(v)) {
      this.set("0x" + v.toString(16));
    }
    else if (v instanceof Uint8Array) {
      if (v.byteLength <= this.byteLength) {
        this.#buffer.set(v);
        this.#buffer.fill(0, v.byteLength);
      }
      else {
        this.#buffer.set(v.subarray(0, this.byteLength));
      }
    }
    else if (v instanceof Array) {
      this.#buffer.set(v);
      this.#buffer.fill(0, v.length);
    }
    else throw new TypeError("Invalid parameter in UInt.set()")
  }
  toString(b) {
    if   (!b || b == 10) return BASE10.encode(this);
    else if (b == 16)    return BASE16.encode(this);
    else if (b == 2)     return BASE02.encode(this);
    else throw new Error("Invalid base in UInt.toString()");
  }
  toBigInt() {
    return BigInt("0x" + this.toString(16));
  }
  get buffer() { return this.#buffer; }
  get byteLength() { return this.#buffer.byteLength; }
  get bitLength()  { return this.#buffer.bitLength; }
  get ptr() { return this.#buffer.byteOffset; }
}

export class UInt32 extends UInt {
  constructor(v) { super(4, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint32_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint32_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint32_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint32_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint32_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint32_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint32_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint32_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint32_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt64 extends UInt {
  constructor(v) { super(8, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint64_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint64_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint64_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint64_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint64_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint64_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint64_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint64_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint64_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt128 extends UInt {
  constructor(v) { super(16, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint128_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint128_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint128_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint128_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint128_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint128_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint128_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint128_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint128_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt256 extends UInt {
  constructor(v) { super(32, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint256_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint256_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint256_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint256_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint256_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint256_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint256_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint256_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint256_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt512 extends UInt {
  constructor(v) { super(64, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint512_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint512_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint512_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint512_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint512_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint512_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint512_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint512_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint512_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt1024 extends UInt {
  constructor(v) { super(128, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint1024_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint1024_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint1024_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint1024_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint1024_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint1024_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint1024_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint1024_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint1024_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt2048 extends UInt {
  constructor(v) { super(256, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint2048_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint2048_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint2048_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint2048_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint2048_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint2048_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint2048_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint2048_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint2048_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt4096 extends UInt {
  constructor(v) { super(512, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint4096_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint4096_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint4096_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint4096_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint4096_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint4096_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint4096_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint4096_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint4096_gcd(a.ptr, b.ptr, r.ptr); }
}
export class UInt8192 extends UInt {
  constructor(v) { super(1024, v); }
  static shl(a, b, r) { EXPORTS.cppcore_uint8192_shl(a.ptr, b, r.ptr);}
  static shr(a, b, r) { EXPORTS.cppcore_uint8192_shr(a.ptr, b, r.ptr);}
  static add(a, b, r) { EXPORTS.cppcore_uint8192_add(a.ptr, b.ptr, r.ptr); }
  static sub(a, b, r) { EXPORTS.cppcore_uint8192_sub(a.ptr, b.ptr, r.ptr); }
  static mul(a, b, r) { EXPORTS.cppcore_uint8192_mul(a.ptr, b.ptr, r.ptr); }
  static divmod(a, b, q, r) { EXPORTS.cppcore_uint8192_divmod(a.ptr, b.ptr, q.ptr, r.ptr); }
  static mulmod(a, b, m, r) { EXPORTS.cppcore_uint8192_mulmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static powmod(a, b, m, r) { EXPORTS.cppcore_uint8192_powmod(a.ptr, b.ptr, m.ptr, r.ptr); }
  static gcd(a, b, r) { EXPORTS.cppcore_uint8192_gcd(a.ptr, b.ptr, r.ptr); }
}

UInt32.MAX   = new UInt32();   UInt32.MAX.buffer.fill(0xFF);
UInt64.MAX   = new UInt64();   UInt64.MAX.buffer.fill(0xFF);
UInt128.MAX  = new UInt128();  UInt128.MAX.buffer.fill(0xFF);
UInt256.MAX  = new UInt256();  UInt256.MAX.buffer.fill(0xFF);
UInt512.MAX  = new UInt512();  UInt512.MAX.buffer.fill(0xFF);
UInt1024.MAX = new UInt1024(); UInt1024.MAX.buffer.fill(0xFF);
UInt2048.MAX = new UInt2048(); UInt2048.MAX.buffer.fill(0xFF);
UInt4096.MAX = new UInt4096(); UInt4096.MAX.buffer.fill(0xFF);
UInt8192.MAX = new UInt8192(); UInt8192.MAX.buffer.fill(0xFF);

/////////////////////////////////////////////////////////////////////////////////////////////
// AES
/////////////////////////////////////////////////////////////////////////////////////////////

class AES {
  #bits
  #ptr
  get bits() { return this.#bits; }
  get ptr() { return this.#ptr; }
  constructor(bits) {
    switch(bits) {
      case 128:
        this.#bits = 128;
        this.#ptr  = EXPORTS.cppcore_aes128_init();
        break;
      case 192:
        this.#bits = 192;
        this.#ptr  = EXPORTS.cppcore_aes192_init();
        break;
      case 256:
        this.#bits = 256;
        this.#ptr  = EXPORTS.cppcore_aes256_init();
        break;
      default:
        throw new RangeError("Invalid bits for AES. Must be 128, 192 or 256.");
    }
    REGISTRY.register(this, this.#ptr, this);
  }
  setKey(key) {
    if (key instanceof CString ||
        key instanceof Buffer ||
        key instanceof UInt) {
      switch(this.#bits) {
        case 128:
          if (key.byteLength != 16)
            throw new RangeError("Key must have exactly 16 bytes for AES128");
          EXPORTS.cppcore_aes128_reset(this.ptr, key.ptr);
          break;
        case 192:
          if (key.byteLength != 24)
            throw new RangeError("Key must have exactly 24 bytes for AES192");
          EXPORTS.cppcore_aes192_reset(this.ptr, key.ptr);
          break;
        case 256:
          if (key.byteLength != 32)
            throw new RangeError("Key must have exactly 32 bytes for AES256");
          EXPORTS.cppcore_aes256_reset(this.ptr, key.ptr);
          break;
      }
    }
    else if (typeof key === "string") {
      const k = new CString(key);
      this.setKey(k);
      k.free();
    }
    else if (key instanceof Uint8Array) {
      const k = new Buffer(key);
      this.setKey(k);
      k.free();
    }
    else {
      throw new TypeError("libcppcorer: Invalid parameter in AES.setKey()");
    }
  }
  _encrypt(input, output, iv, f, blockmode) {
    if ((input  instanceof Buffer || input instanceof CString) && 
        (output instanceof Buffer)) {
      if (input.byteLength > output.byteLength) {
        throw new RangeError("Output too small");
      }
      let len = input.byteLength;
      if (blockmode) {
        if (len & 0x0F != 0) {
          throw new RangeError("Input must be a multiple of 16 bytes");
        }
        len = len >> 4;
      }
      if (iv) f(this.ptr, input.ptr, output.ptr, iv.ptr, len);
      else    f(this.ptr, input.ptr, output.ptr, len);
    }
    else if (input instanceof Uint8Array && !(input instanceof Buffer)) {
      const t = new Buffer(input);
      this._encrypt(t, output, iv, f, blockmode);
      t.free();
    }
    else if (output instanceof Uint8Array && !(output instanceof Buffer)) {
      const t = new Buffer(output.byteLength);
      this._encrypt(input, t, iv, f, blockmode);
      output.set(t);
      t.free();
    }
    else {
      throw new TypeError("Invalid type of input or output in AES.encrypt()");
    }
  }
  _decrypt(input, output, iv, f, blockmode) {
    if ((input  instanceof Buffer) && 
        (output instanceof Buffer || output instanceof CString)) {
      if (output instanceof CString) {
        if (input.byteLength > output.maxLength) {
          throw new RangeError("Output too small");
        }
        output.byteLength = input.byteLength;
        output[output.byteLength] = 0x00;
      }
      else {
        if (input.byteLength > output.byteLength) {
          throw new RangeError("Output too small");
        }
      }
      let len = input.byteLength;
      if (blockmode) {
        if (len & 0x0F != 0) {
          throw new RangeError("Input must be a multiple of 16 bytes");
        }
        len = len >> 4;
      }
      if (iv) f(this.ptr, input.ptr, output.ptr, iv.ptr, len);
      else    f(this.ptr, input.ptr, output.ptr, len);
    }
    else if (input instanceof Uint8Array && !(input instanceof Buffer)) {
      const t = new Buffer(input);
      this._decrypt(t, output, iv, f, blockmode);
      t.free();
    }
    else if (output instanceof Uint8Array && !(output instanceof Buffer)) {
      const t = new Buffer(output.byteLength);
      this._decrypt(input, t, iv, f, blockmode);
      output.set(t);
      t.free();
    }
    else {
      throw new TypeError("Invalid type of input or output in AES.decrypt()");
    }
  }
}

class AESIV extends AES {
  #ivEnc
  #ivDec
  get ivEnc() { return this.#ivEnc; }
  get ivDec() { return this.#ivDec; }
  constructor(bits) { 
    super(bits);
  }
  setIV(iv) {
    if (iv instanceof Uint8Array) {
      if (iv.byteLength != 16)
        throw new RangeError("Binary IV must have exactly 16 bytes");
      this.#ivEnc = new Buffer(iv);
      this.#ivDec = new Buffer(iv);
    }
    else if (iv instanceof CString) {
      if (iv.byteLength != 16)
        throw new RangeError("String IV must have exactly 16 bytes");
      this.setIV(iv.buffer.subarray(0, 16));
    }
    else if (typeof iv === "string") {
      const k = new CString(iv);
      this.setIV(k);
      k.free();
    }
    else {
      throw new TypeError("No valid type of iv in AES.setIV()");
    }
  }
}

export class AES128ECB extends AES {
  constructor() {
    super(128);
  }
  encrypt(input, output) {
    super._encrypt(input, output, null, EXPORTS.cppcore_aes128_encrypt_ecb, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, null, EXPORTS.cppcore_aes128_decrypt_ecb, true);
  }
}
export class AES192ECB extends AES {
  constructor() {
    super(192);
  }
  encrypt(input, output) {
    super._encrypt(input, output, null, EXPORTS.cppcore_aes192_encrypt_ecb, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, null, EXPORTS.cppcore_aes192_decrypt_ecb, true);
  }
}
export class AES256ECB extends AES {
  constructor() {
    super(256);
  }
  encrypt(input, output) {
    super._encrypt(input, output, null, EXPORTS.cppcore_aes256_encrypt_ecb, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, null, EXPORTS.cppcore_aes256_decrypt_ecb, true);
  }
}

export class AES128CBC extends AESIV {
  constructor() {
    super(128);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes128_encrypt_cbc, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes128_decrypt_cbc, true);
  }
}
export class AES192CBC extends AESIV {
  constructor() {
    super(192);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes192_encrypt_cbc, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes192_decrypt_cbc, true);
  }
}
export class AES256CBC extends AESIV {
  constructor() {
    super(256);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes256_encrypt_cbc, true);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes256_decrypt_cbc, true);
  }
}

export class AES128CTR extends AESIV {
  constructor() {
    super(128);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes128_encrypt_ctr, false);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes128_decrypt_ctr, false);
  }
}
export class AES192CTR extends AESIV {
  constructor() {
    super(192);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes192_encrypt_ctr, false);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes192_decrypt_ctr, false);
  }
}
export class AES256CTR extends AESIV {
  constructor() {
    super(256);
  }
  encrypt(input, output) {
    super._encrypt(input, output, this.ivEnc, EXPORTS.cppcore_aes256_encrypt_ctr, false);
  }
  decrypt(input, output) {
    super._decrypt(input, output, this.ivDec, EXPORTS.cppcore_aes256_decrypt_ctr, false);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// HASH
/////////////////////////////////////////////////////////////////////////////////////////////

class Hash {
  #ptr
  get ptr() { return this.#ptr; }
  constructor(f) {
    this.#ptr = f();
    REGISTRY.register(this, this.#ptr, this);
  }
  _reset(f) {
    f(this.#ptr);
  }
  _step(data, f) {
    if (data instanceof Buffer || data instanceof UInt || data instanceof CString) {
      f(this.#ptr, data.ptr, data.byteLength);
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
      throw new TypeError("Invalid type of data in Hash.step()");
    }
  }
  _finish(digest, f) {
    if (digest instanceof Buffer || digest instanceof UInt) {
      if (digest.byteLength != this.constructor.digestLength) {
        throw new RangeError("Invalid size of digest in Hash.finish()");
      }
      f(this.#ptr, digest.ptr);
    }
    else if (digest instanceof Uint8Array) {
      const d = new Buffer(digest.byteLength);
      this._finish(d, f);
      digest.set(d);
      d.free();
    }
    else {
      throw new TypeError("Invalid type of digest in Hash.finish()");
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
  #ptr
  get ptr() { return this.#ptr; }
  constructor(f) {
    this.#ptr = f();
    REGISTRY.register(this, this.#ptr, this);
  }
  _reset(key, f) {
    if (key instanceof Buffer || key instanceof UInt || key instanceof CString) {
      f(this.#ptr, key.ptr, key.byteLength);
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
      throw new TypeError("Invalid type of key in HMAC.reset()");
    }
  }
  _step(data, f) {
    if (data instanceof Buffer || data instanceof UInt || data instanceof CString) {
      f(this.#ptr, data.ptr, data.byteLength);
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
      throw new TypeError("Invalid type of data in HMAC.step()");
    }
  }
  _finish(digest, f) {
    if (digest instanceof Buffer || digest instanceof UInt) {
      if (digest.byteLength != this.constructor.digestLength) {
        throw new RangeError("Invalid size of digest in HMAC.finish()");
      }
      f(this.#ptr, digest.ptr);
    }
    else if (digest instanceof Uint8Array) {
      const d = new Buffer(digest.byteLength);
      this._finish(d, f);
      digest.set(d);
      d.free();
    }
    else {
      throw new TypeError("Invalid type of digest in HMAC.finish()");
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
  static #run(password, salt, digest, iterations, f) {
    if ((password instanceof Buffer || password instanceof UInt || password instanceof CString) &&
        (salt     instanceof Buffer || salt     instanceof UInt || salt     instanceof CString) &&
        (digest   instanceof Buffer || digest   instanceof UInt) &&
        (Number.isInteger(iterations))) {
      f(password.ptr, password.byteLength,
        salt.ptr,     salt.byteLength,
        digest.ptr,   digest.byteLength,
        iterations);
    }
    else if (typeof password === "string") {
      const p = new CString(password);
      PBKDF2.#run(p, salt, digest, iterations, f);
      p.free();
    }
    else if (typeof salt === "string") {
      const s = new CString(salt);
      PBKDF2.#run(password, s, digest, iterations, f);
      s.free();
    }
    else if (password instanceof Uint8Array && !(password instanceof Buffer)) {
      const p = new Buffer(password);
      PBKDF2.#run(p, salt, digest, iterations, f);
      p.free();
    }
    else if (salt instanceof Uint8Array && !(salt instanceof Buffer)) {
      const s = new Buffer(salt);
      PBKDF2.#run(password, s, digest, iterations, f);
      s.free();
    }
    else if (digest instanceof Uint8Array && !(digest instanceof Buffer)) {
      const d = new Buffer(digest.byteLength);
      PBKDF2.#run(password, salt, d, iterations, f);
      digest.set(d);
      d.free();
    }
    else throw new TypeError("Invalid parameters in PBKDF2");
  }
  static md5(password, salt, digest, iterations) {
    PBKDF2.#run(password, salt, digest, iterations, 
      EXPORTS.cppcore_pbkdf2_md5_create);
  }
  static sha256(password, salt, digest, iterations) {
    PBKDF2.#run(password, salt, digest, iterations, 
      EXPORTS.cppcore_pbkdf2_sha256_create);
  }
  static sha512(password, salt, digest, iterations) {
    PBKDF2.#run(password, salt, digest, iterations, 
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
    if (typeof p === "bigint" || Number.isInteger(p)) {
      const n = UInt.fromInteger(p);
      const r = Prime.test(n, sign, certainty);
      n.free();
      return r;
    }
    if (!(p instanceof UInt) && !(p instanceof Buffer)) {
      throw new TypeError("Invalid type of p in Prime.test()");
    }
    switch(p.byteLength) {
      case 4:   return EXPORTS.cppcore_prime32_test(p.ptr, sign, certainty);
      case 8:   return EXPORTS.cppcore_prime64_test(p.ptr, sign, certainty);
      case 16:  return EXPORTS.cppcore_prime128_test(p.ptr, sign, certainty);
      case 32:  return EXPORTS.cppcore_prime256_test(p.ptr, sign, certainty);
      case 64:  return EXPORTS.cppcore_prime512_test(p.ptr, sign, certainty);
      case 128: return EXPORTS.cppcore_prime1024_test(p.ptr, sign, certainty);
      case 256: return EXPORTS.cppcore_prime2048_test(p.ptr, sign, certainty);
      case 512: return EXPORTS.cppcore_prime4096_test(p.ptr, sign, certainty);
      default:  throw new RangeError("Invalid byteLength of p in Prime.test()");
    }
  }
  static generate(p, sign, certainty) {
    if (!(p instanceof UInt) && !(p instanceof Buffer)) {
      throw new TypeError("Invalid type of p in Prime.generate()");
    }
    switch(p.byteLength) {
      case 4:   return EXPORTS.cppcore_prime32_generate(p.ptr, sign, certainty);
      case 8:   return EXPORTS.cppcore_prime64_generate(p.ptr, sign, certainty);
      case 16:  return EXPORTS.cppcore_prime128_generate(p.ptr, sign, certainty);
      case 32:  return EXPORTS.cppcore_prime256_generate(p.ptr, sign, certainty);
      case 64:  return EXPORTS.cppcore_prime512_generate(p.ptr, sign, certainty);
      case 128: return EXPORTS.cppcore_prime1024_generate(p.ptr, sign, certainty);
      case 256: return EXPORTS.cppcore_prime2048_generate(p.ptr, sign, certainty);
      case 512: return EXPORTS.cppcore_prime4096_generate(p.ptr, sign, certainty);
      default:  throw new RangeError("Invalid byteLength of p in Prime.generate()");
    }
  }
}
