import sys

MAX32B  :bytes = b'\xff\xff\xff\xff'
MAX64B  :bytes = MAX32B + MAX32B
MAX128B :bytes = MAX64B + MAX64B
MAX256B :bytes = MAX128B + MAX128B
MAX512B :bytes = MAX256B + MAX256B
MAX1024B:bytes = MAX512B + MAX512B
MAX2048B:bytes = MAX1024B + MAX1024B
MAX4096B:bytes = MAX2048B + MAX2048B
MAX8192B:bytes = MAX4096B + MAX4096B

MAX32I  :int = int.from_bytes(bytes=MAX32B,   byteorder=sys.byteorder, signed=False)
MAX64I  :int = int.from_bytes(bytes=MAX64B,   byteorder=sys.byteorder, signed=False)
MAX128I :int = int.from_bytes(bytes=MAX128B,  byteorder=sys.byteorder, signed=False)
MAX256I :int = int.from_bytes(bytes=MAX256B,  byteorder=sys.byteorder, signed=False)
MAX512I :int = int.from_bytes(bytes=MAX512B,  byteorder=sys.byteorder, signed=False)
MAX1024I:int = int.from_bytes(bytes=MAX1024B, byteorder=sys.byteorder, signed=False)
MAX2048I:int = int.from_bytes(bytes=MAX2048B, byteorder=sys.byteorder, signed=False)
MAX4096I:int = int.from_bytes(bytes=MAX4096B, byteorder=sys.byteorder, signed=False)
MAX8192I:int = int.from_bytes(bytes=MAX8192B, byteorder=sys.byteorder, signed=False)
