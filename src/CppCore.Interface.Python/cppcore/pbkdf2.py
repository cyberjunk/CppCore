from cppcore import lib

def pbkdf2_md5(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_md5_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r

def pbkdf2_sha256(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_sha256_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r

def pbkdf2_sha512(pw:bytes, salt:bytes, length:int, iterations:int) -> bytes:
    r = bytes(length)
    lib.cppcore_pbkdf2_sha512_create(pw, len(pw), salt, len(salt), r, length, iterations)
    return r
