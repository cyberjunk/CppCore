import basex
import base62
import time
import sys

b16:bytes = b'\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff'
b:bytes = b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16 + \
        b16 + b16 +b16 + b16

print(len(b))
max = int.from_bytes(b, byteorder=sys.byteorder, signed=False)
print(max)

var = basex.encode(max, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
print(var)

max2 = basex.decode(var, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
#max2 = basex_decode(var, "KLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")

print(max2)

t1 = time.time_ns()
for i in range(1000):
    #var1 = basex_encode(max, "0123456789")
    var1 = basex.encode(max, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")
span = time.time_ns() - t1
print(span)

t1 = time.time_ns()
for i in range(1000):
    #var2 = bin(max)
    var2 = base62.encode(max)
span = time.time_ns() - t1
print(span)

#print(var1)
