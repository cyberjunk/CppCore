from cppcore import lib

class Hash:
    def __init__(self):    
        self._h = self._init()
    def __del__(self):
        self._destroy(self._h)
    def reset(self):
        self._reset(self._h)
    def blockstep(self, data:bytes):
        self._blockstep(self._h, data, len(data))
    def step(self, data:bytes):
        self._step(self._h, data, len(data))
    def finish(self) -> bytes:
        r = bytes(self._nbytes)
        self._finish(self._h, r)
        return r

class MD5(Hash):
    def __init__(self):
        self._nbytes    = 16
        self._init      = lib.cppcore_md5_init
        self._destroy   = lib.cppcore_md5_destroy
        self._reset     = lib.cppcore_md5_reset
        self._blockstep = lib.cppcore_md5_blockstep
        self._step      = lib.cppcore_md5_step
        self._finish    = lib.cppcore_md5_finish
        super().__init__()

class SHA256(Hash):
    def __init__(self):
        self._nbytes    = 32
        self._init      = lib.cppcore_sha256_init
        self._destroy   = lib.cppcore_sha256_destroy
        self._reset     = lib.cppcore_sha256_reset
        self._blockstep = lib.cppcore_sha256_blockstep
        self._step      = lib.cppcore_sha256_step
        self._finish    = lib.cppcore_sha256_finish
        super().__init__()

class SHA512(Hash):
    def __init__(self):
        self._nbytes    = 64
        self._init      = lib.cppcore_sha512_init
        self._destroy   = lib.cppcore_sha512_destroy
        self._reset     = lib.cppcore_sha512_reset
        self._blockstep = lib.cppcore_sha512_blockstep
        self._step      = lib.cppcore_sha512_step
        self._finish    = lib.cppcore_sha512_finish
        super().__init__()

class CRC32(Hash):
    def __init__(self):
        self._nbytes    = 4
        self._init      = lib.cppcore_crc32_init
        self._destroy   = lib.cppcore_crc32_destroy
        self._reset     = lib.cppcore_crc32_reset
        self._blockstep = lib.cppcore_crc32_blockstep
        self._step      = lib.cppcore_crc32_step
        self._finish    = lib.cppcore_crc32_finish
        super().__init__()

class CRC32C(Hash):
    def __init__(self):
        self._nbytes    = 4
        self._init      = lib.cppcore_crc32c_init
        self._destroy   = lib.cppcore_crc32c_destroy
        self._reset     = lib.cppcore_crc32c_reset
        self._blockstep = lib.cppcore_crc32c_blockstep
        self._step      = lib.cppcore_crc32c_step
        self._finish    = lib.cppcore_crc32c_finish
        super().__init__()
