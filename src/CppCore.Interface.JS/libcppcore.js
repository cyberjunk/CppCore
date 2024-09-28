
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

        console.debug("Memory Buffer Size")
        console.debug(lib.instance.exports.memory.buffer.byteLength.toString(16));
        console.debug(lib.instance.exports.memory.buffer.maxByteLength.toString(16));
        lib.instance.exports.memory.grow(1);
        console.debug(lib.instance.exports.memory.buffer.byteLength.toString(16));
        console.debug(lib.instance.exports.memory.buffer.maxByteLength.toString(16));
        
        var _tls_base = lib.instance.exports.__tls_base.value;
        var _data_end = lib.instance.exports.__data_end.value;
        var _heap_base = lib.instance.exports.__heap_base.value
        var _stack_pointer = lib.instance.exports.__stack_pointer.value

        console.debug("__tls_base: " + _tls_base.toString(16));
        console.debug("__data_end: " + _data_end.toString(16));
        console.debug("__heap_base: " + _heap_base.toString(16));
        console.debug("__stack_pointer: " + _stack_pointer.toString(16));

        /*var ptr = lib.instance.exports.cppcore_alloc(16);
        var t1 = new Uint8Array(lib.instance.exports.memory.buffer, ptr, 16);
        console.log("testing...")
        console.log(t1[0]);
        t1[0] = 0xFF;
        console.log(t1[0]);
        var t2 = new Uint8Array(lib.instance.exports.memory.buffer, ptr, 16);
        console.log(t2[0]);
        var t3 = new DataView(lib.instance.exports.memory.buffer, ptr, 16);
        console.log(t3.getUint8(0));

        console.log(t1.byteLength);
        console.log(t2.byteLength);
        console.log(t3.byteLength);

        console.log(t1);
        console.log(t3);*/

        return lib;
    });

const registry = new FinalizationRegistry((ptr) => {
    console.debug("Finalizing: " + ptr)
    handle.instance.exports.cppcore_free(ptr);
});

const encoder = new TextEncoder();
const decoder = new TextDecoder();

/////////////////////////////////////////////////////////////////////////////////

export class Buffer extends Uint8Array {
    constructor(size) {
        console.debug("Constructing Buffer...");
        const ptr = handle.instance.exports.cppcore_alloc(size);
        if (ptr == 0)
            throw new Error('Out of heap memory');
        super(handle.instance.exports.memory.buffer, ptr, size);
        console.debug("Constructed Buffer at: " + ptr);
        registry.register(this, ptr);
        this._ptr=ptr;
    }
}

export class CString extends Buffer {
    constructor(v) {
        console.debug("CString Constructor: " + v);
        const type = typeof(v);
        if (type === 'string') {
            super(v.length+1);
            this.fromString(v);
        }
        else if (type === 'undefined') {
            super(16);
            this.usedLength = 0;
        }
        else if (Number.isInteger(v)) {
            super(v+1);
            this.usedLength = 0;
        }
        else {
            throw new Error('Invalid value for CString');
        }
    }
    fromString(str) {
        const enc = encoder.encode(str);
        if (this.byteLength-1 < enc.length)
            throw new Error('String too big');
        this.set(enc);
        this[enc.length] = 0x00;
        this.usedLength = enc.length;
    }
    toString() {
        //const buf = new ArrayBuffer(this.byteLength-1);
        const buf = new ArrayBuffer(this.usedLength);
        const dst = new Uint8Array(buf);
        const src = new Uint8Array(this);
        /*console.debug("this byteLength: " + this.byteLength);
        console.debug("src byteLength:" + src.byteLength);
        console.debug("dst byteLength: " + dst.byteLength);*/
        
        //dst.set(src.slice(0, this.byteLength-1));
        dst.set(src.slice(0, this.usedLength));

        return decoder.decode(dst);
    }
}

export class BaseX {
    constructor(alphabet) {
        this._alphabet = new CString(alphabet);
    }
    encode128(v) {
        let outbuf = new CString(15);
        let r = handle.instance.exports.cppcore_basex_encode128(
            v._ptr, outbuf._ptr, outbuf.byteLength-1, 
            this._alphabet.byteLength-1, 
            this._alphabet._ptr, 1);
        if (r < 0)
            throw new Error('Buffer too small');
        
        console.log("LEN:" + r);
        console.log("DIFF:" + (outbuf.byteLength-1-r));
        outbuf.usedLength = (outbuf.byteLength-1-r);
        return outbuf.toString();
    }
    decode128(str) {
        const ibuf = new CString(str);
        const obuf = new Buffer(16);
        const r = handle.instance.exports.cppcore_basex_decode128(
            ibuf._ptr, obuf._ptr, this._alphabet._ptr);
        if (r == 0)
            throw new Error('Invalid symbol or overflow');
        return obuf;
    }
}

export class uint2048 {
    constructor() {
        this._ptr = handle.instance.exports.cppcore_alloc(256);
        registry.register(this, this._ptr);
    }
    static add(a, b) {
        var r = new uint2048();
        handle.instance.exports.cppcore_uint2048_add(a._ptr, b._ptr, r._ptr);
        return r;
    }
}

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

export function cppcore_alloc(size) {
    return handle.instance.exports.cppcore_alloc(size);
}


export function cppcore_prime1024_generate()
{
  /*var p = new Uint8Array(handle.instance.exports.memory.buffer, 0, 128);
  console.log(p.byteOffset);
  console.log(p);
  handle.instance.exports.cppcore_prime1024_generate(p.byteOffset, 0, 0);
  console.log(p);*/
}
