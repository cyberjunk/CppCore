
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

function hexStrFromInt(v) {
    return "0x" + v.toString(16).padStart(8, '0');
}

/////////////////////////////////////////////////////////////////////////////////////////////

export class Buffer extends Uint8Array {
    constructor(size) {
        if (!size) {
            size = 64;
        }
        console.debug("libcppcore: Constructing Buffer with size " + size);
        const ptr = handle.instance.exports.cppcore_alloc(size);
        if (ptr == 0)
            throw new Error('Out of heap memory');
        super(handle.instance.exports.memory.buffer, ptr, size);
        console.debug("libcppcore: Constructed Buffer at: " + hexStrFromInt(ptr));
        registry.register(this, ptr);
        this._ptr=ptr;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

export class BaseX {
    constructor(alphabet) {
        this._alphabet = new CString(alphabet);
        this._strbuf = new CString(8192);
    }
    encode128(v) {
        const MAXSYMBOLS = this._strbuf.byteLength-1;
        const r = handle.instance.exports.cppcore_basex_encode128(
            v._ptr,                        // inbuf ptr
            this._strbuf._ptr,             // outbuf ptr
            MAXSYMBOLS,                    // outbuf max symbols
            this._alphabet.byteLength-1,   // base
            this._alphabet._ptr,           // alphabet ptr
            1                              // write term 0x00
        );
        if (r < 0) throw new Error('_strbuf too small');
        this._strbuf.usedLength = (MAXSYMBOLS-r);
        return this._strbuf.toString();
    }
    decode128(str) {
        this._strbuf.fromString(str);
        const obuf = new Buffer(16);
        const r = handle.instance.exports.cppcore_basex_decode128(
            this._strbuf._ptr, obuf._ptr, this._alphabet._ptr);
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
