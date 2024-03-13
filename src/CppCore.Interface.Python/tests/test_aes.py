import cppcore.aes

dat1:bytes = b'\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff'
dat2:bytes = b'\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee\xee'

key:bytes = b'\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff'
iv:bytes = bytes(16)

print(dat1)
print(dat2)
print("--------")

#test = AES128()
#test.reset(key)

#dat = test.encryptECB(dat)
#print(dat)
#dat = test.decryptECB(dat)
#print(dat)

#print(test.ivenc)
#dat1 = test.encryptCBC(dat1)
#print(test.ivenc)
#dat2 = test.encryptCBC(dat2)
#print(test.ivenc)
#print("--------")
#print(test.ivdec)
#dat1 = test.decryptCBC(dat1)
#print(test.ivdec)
#dat2 = test.decryptCBC(dat2)
#print(test.ivdec)
#print("--------")
#print(dat1)
#print(dat2)

test = cppcore.aes.AES128CTR()
test.reset(key, iv)

print(test.ivenc)
dat1 = test.encrypt(dat1)
print(test.ivenc)
dat2 = test.encrypt(dat2)
print(test.ivenc)
print("--------")
print(test.ivdec)
dat1 = test.decrypt(dat1)
print(test.ivdec)
dat2 = test.decrypt(dat2)
print(test.ivdec)
print("--------")
print(dat1)
print(dat2)


del test

