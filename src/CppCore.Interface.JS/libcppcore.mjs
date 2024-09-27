
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

        var ptr = lib.instance.exports.cppcore_alloc(16);
        var t1 = new Uint8Array(lib.instance.exports.memory.buffer, ptr, 16);
        console.log("testing...")
        console.log(t1[0]);
        t1[0] = 0xFF;
        console.log(t1[0]);
        //console.log(lib.instance.exports.memory.buffer.getUint8(ptr));
        var t2 = new Uint8Array(lib.instance.exports.memory.buffer, ptr, 16);
        console.log(t2[0]);
        var t3 = new DataView(lib.instance.exports.memory.buffer, ptr, 16);
        console.log(t3.getUint8(0));

        console.log(t1.byteLength);
        console.log(t2.byteLength);
        console.log(t3.byteLength);

        console.log(t1);
        console.log(t3);

        return lib;
    });

const registry = new FinalizationRegistry((ptr) => {
    console.debug("Finalizing: " + ptr)
    handle.instance.exports.cppcore_free(ptr);
});

/////////////////////////////////////////////////////////////////////////////////

export class Buffer extends DataView {
    constructor(size) {
        console.log("Constructing Buffer...");
        const ptr = handle.instance.exports.cppcore_alloc(size);
        super(handle.instance.exports.memory.buffer, ptr, size);
        console.log("Constructed Buffer at: " + ptr);
        registry.register(this, ptr);
        this._ptr=ptr;
    }
}

export class BaseX {
    constructor() {
        this._encoder = new TextEncoder();
        this._decoder = new TextDecoder();
    }
    decode2048() {
        let encoder = new TextEncoder();
        let alphabet = encoder.encode("0123456789");
        let buf = new Buffer(alphabet.length);
        let output = new Buffer(64);
        handle.instance.exports.cppcore_basex_decode2048(input, output, buf._ptr)
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
