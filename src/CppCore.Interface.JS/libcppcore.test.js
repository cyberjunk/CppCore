import { 
  Buffer, CString, BaseX,
  UInt32, UInt64, UInt128, UInt256, UInt512, UInt1024, UInt2048, UInt4096, UInt8192,
  AES128ECB, AES192ECB, AES256ECB,
  AES128CBC, AES192CBC, AES256CBC,
  AES128CTR, AES192CTR, AES256CTR,
  MD5, SHA256, SHA512,
  HMACMD5, HMACSHA256, HMACSHA512,
  PBKDF2,
  Prime
} from '../libcppcore.js';

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}
function getRandomHexStr(max) {
  const symbols = "0123456789abcdef";
  const len = getRandomInt(max-1) + 1;
  var str = "0x";
  for (var i=0; i < len; i++) {
    str += symbols[getRandomInt(16)];
  }
  if (BigInt(str) == 0) 
    str = "0x1";
  return str;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// BUFFER
///////////////////////////////////////////////////////////////////////////////////////////////////

describe('Buffer', function () {
  describe('constructor()', function () {
    it('constructor(uint8array)', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a);      
      chai.expect(b.byteLength).to.equal(8);
      chai.expect(indexedDB.cmp(a, b)).to.equal(0);
    });
    it('constructor(array)', function () {
      const a = [0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08];
      const b = new Buffer(a);
      chai.expect(b.byteLength).to.equal(8);
      for (var i = 0; i<8;i++)
        chai.expect(a[i]).to.equal(b[i]);
    });
    it('constructor(wasm_memory_buffer, number, number)', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a); 
      const c = new Buffer(b.buffer, b.byteOffset, b.byteLength)    
      chai.expect(c.byteLength).to.equal(8);
      chai.expect(indexedDB.cmp(a, c)).to.equal(0);
      chai.expect(b.buffer).to.equal(c.buffer);
    });
    it('constructor(number)', function () {
      const a = new Buffer(16);      
      chai.expect(a.byteLength).to.equal(16);
    });
  });
  describe('slice()', function () {
    it('slice(number, number)', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a);
      const c = b.slice(0, 8);      
      chai.expect(indexedDB.cmp(a, c)).to.equal(0);
      chai.expect(b.byteLength).to.equal(c.byteLength);
      chai.expect(b.buffer).to.equal(c.buffer);
      chai.expect(b.byteOffset).to.not.equal(c.byteOffset);
    });
  });
  describe('subarray()', function () {
    it('subarray(number, number)', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a);
      const c = b.subarray(0, 8);      
      chai.expect(indexedDB.cmp(a, c)).to.equal(0);
      chai.expect(b.byteLength).to.equal(c.byteLength);
      chai.expect(b.buffer).to.equal(c.buffer);
      chai.expect(b.byteOffset).to.equal(c.byteOffset);
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// CSTRING
///////////////////////////////////////////////////////////////////////////////////////////////////

describe('CString', function () {
  describe('constructor()', function () {
    it('constructor(null)', function () {
      const s = new CString();
      chai.expect(s.byteLength).to.equal(0);
      chai.expect(s.maxLength).to.equal(15);
      chai.expect(s.buffer.byteLength).to.equal(16);
    });
    it('constructor(number)', function () {
      const s = new CString(15);
      chai.expect(s.byteLength).to.equal(0);
      chai.expect(s.maxLength).to.equal(15);
      chai.expect(s.buffer.byteLength).to.equal(16);
    });
    it('constructor(string)', function () {
      const s = new CString("Hello World!");
      chai.expect(s.byteLength).to.equal(12);
      chai.expect(s.maxLength).to.equal(12);
      chai.expect(s.buffer.byteLength).to.equal(13);
    });
    it('constructor(cstring)', function () {
      const t = new CString("Hello World!");
      const s = new CString(t);
      chai.expect(s.byteLength).to.equal(12);
      chai.expect(s.maxLength).to.equal(12);
      chai.expect(s.buffer.byteLength).to.equal(13);
    });
  });
  describe('resize()', function () {
    it('resize(number) [grow]', function () {
      const s = new CString(3);
      s.set("123");
      s.resize(4);
      chai.expect(s.byteLength).to.equal(3);
      chai.expect(s.maxLength).to.equal(4);
      chai.expect(s.buffer.byteLength).to.equal(5);
      chai.expect(s.buffer[0]).to.equal(49);
      chai.expect(s.buffer[1]).to.equal(50);
      chai.expect(s.buffer[2]).to.equal(51);
      chai.expect(s.buffer[3]).to.equal(0);     
    });
    it('resize(number) [shrink]', function () {
      const s = new CString(15);
      s.set("123");
      s.resize(3);
      chai.expect(s.byteLength).to.equal(3);
      chai.expect(s.maxLength).to.equal(3);
      chai.expect(s.buffer.byteLength).to.equal(4);
      chai.expect(s.buffer[0]).to.equal(49);
      chai.expect(s.buffer[1]).to.equal(50);
      chai.expect(s.buffer[2]).to.equal(51);
      chai.expect(s.buffer[3]).to.equal(0);     
    });
  });
  describe('set()', function () {
    it('set(string)', function () {
      const s = new CString(31);
      s.set("0123456789");
      chai.expect(s.byteLength).to.equal(10);
      chai.expect(s.maxLength).to.equal(31);
      chai.expect(s.buffer.byteLength).to.equal(32);
    });
    it('set(cstring)', function () {
      const s = new CString(31);
      s.set(new CString("0123456789"));
      chai.expect(s.byteLength).to.equal(10);
      chai.expect(s.maxLength).to.equal(31);
      chai.expect(s.buffer.byteLength).to.equal(32);
    });
  });
  describe('toString()', function () {
    it('toString()', function () {
      const t = new CString("0123456789");
      const s = t.toString();
      chai.expect(s).to.equal("0123456789");
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// BASEX
///////////////////////////////////////////////////////////////////////////////////////////////////

describe('BaseX', function () {
  describe('constructor()', function () {
    it('constructor(string)', function () {
      const b = new BaseX("0123456789");      
      chai.expect(b.alphabet.byteLength).to.equal(10);
    });
  });
  describe('estimateBits()', function () {
    it('estimateBits(number, number)', function () {
      chai.expect(BaseX.estimateBits(1,    2)).to.equal(1);
      chai.expect(BaseX.estimateBits(8192, 2)).to.equal(8192);
      chai.expect(BaseX.estimateBits(2,   16)).to.equal(8);
      chai.expect(BaseX.estimateBits(8,   16)).to.equal(32);
      chai.expect(BaseX.estimateBits(16,  16)).to.equal(64);
      chai.expect(BaseX.estimateBits(32,  16)).to.equal(128);
      chai.expect(BaseX.estimateBits(11,  10)).to.equal(BaseX.estimateBits(11, 16));
      chai.expect(BaseX.estimateBits(23,  10)).to.equal(BaseX.estimateBits(23, 16));
    });
  });
  describe('estimateSymbols()', function () {
    it('estimateSymbols(number, number)', function () {
      chai.expect(BaseX.estimateSymbols(1,    2)).to.equal(1);
      chai.expect(BaseX.estimateSymbols(8192, 2)).to.equal(8192);
      chai.expect(BaseX.estimateSymbols(8,   16)).to.equal(2);
      chai.expect(BaseX.estimateSymbols(32,  16)).to.equal(8);
      chai.expect(BaseX.estimateSymbols(64,  16)).to.equal(16);
      chai.expect(BaseX.estimateSymbols(128, 16)).to.equal(32);
      chai.expect(BaseX.estimateSymbols(32,  10)).to.equal(BaseX.estimateSymbols(32, 8));
      chai.expect(BaseX.estimateSymbols(64,  10)).to.equal(BaseX.estimateSymbols(64, 8));
    });
  });
  describe('[B10] decode()', function () {
    it('decode("123", 32)', function () {
      const b = new BaseX("0123456789");
      const t1 = b.decode("123", 32);
      const t2 = new Uint8Array([0x7B, 0x00, 0x00, 0x00]);
      chai.expect(indexedDB.cmp(t1.buffer,t2)).to.equal(0);
    });
    it('decode("18446744073709551615", 64)', function () {
      const b = new BaseX("0123456789");
      const t1 = b.decode("18446744073709551615", 64);
      const t2 = new Uint8Array([0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]);
      chai.expect(indexedDB.cmp(t1.buffer,t2)).to.equal(0);
    });
  });
  describe('[B16] decode()', function () {
    it('decode("A", 32)', function () {
      const b = new BaseX("0123456789ABCDEF");
      const t1 = b.decode("A", 32);
      const t2 = new Uint8Array([0x0A, 0x00, 0x00, 0x00]);
      chai.expect(indexedDB.cmp(t1.buffer,t2)).to.equal(0);
    });
    it('decode("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 128)', function () {
      const b = new BaseX("0123456789ABCDEF");
      const t1 = b.decode("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 128);
      const t2 = new Uint8Array([
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
      ]);
      chai.expect(indexedDB.cmp(t1.buffer,t2)).to.equal(0);
    });
  });
  describe('[B10] encode()', function () {
    it('encode(7B000000])', function () {
      const b = new BaseX("0123456789");
      const t1 = b.encode(new Buffer(new Uint8Array([0x7B, 0x00, 0x00, 0x00])));
      chai.expect(t1).to.equal("123");
    });
  });
  describe('[B16] encode()', function () {
    it('encode(FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)', function () {
      const b = new BaseX("0123456789ABCDEF");
      const t1 = b.encode(new Buffer(new Uint8Array([
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
      ])));
      chai.expect(t1).to.equal("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// UINT
///////////////////////////////////////////////////////////////////////////////////////////////////

function opAddBigInt(t, a, b, r)    { r = a + b; return r; }
function opAddUInt  (t, a, b, r, q) { t.add(a,b,r); return r; }
function opSubBigInt(t, a, b, r)    { r = a - b; return r; }
function opSubUInt  (t, a, b, r, q) { t.sub(a,b,r); return r; }
function opMulBigInt(t, a, b, r)    { r = a * b; return r; }
function opMulUInt  (t, a, b, r, q) { t.mul(a,b,r); return r; }
function opDivBigInt(t, a, b, r)    { r = a / b; return r; }
function opDivUInt  (t, a, b, r, q) { t.divmod(a,b,r,q); return r; }

function testOp(type, bits, maxhexsymbols, iterations, opbig, opuint) {
    var a2 = new type();        
    var b2 = new type();
    var r2 = new type();
    var t2 = new type();
    for(var n=0;n<iterations;n++) {
      var stra = getRandomHexStr(maxhexsymbols);
      var strb = getRandomHexStr(maxhexsymbols);
      var a1 = BigInt(stra);
      var b1 = BigInt(strb);
      var r1 = BigInt(0);
      a2.set(stra);
      b2.set(strb);
      r1 = opbig(type, a1, b1, r1);
      r1 = BigInt.asUintN(bits, r1);
      r2 = opuint(type, a2, b2, r2, t2);
      chai.expect(r1.toString()).to.equal(r2.toString());
    }
}

describe('UInt', function () {
  describe('UInt32', function () {
    it('add()', function () { testOp(UInt32, 32, 8, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt32, 32, 8, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt32, 32, 8, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt32, 32, 8, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt64', function () {
    it('add()', function () { testOp(UInt64, 64, 16, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt64, 64, 16, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt64, 64, 16, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt64, 64, 16, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt128', function () {
    it('add()', function () { testOp(UInt128, 128, 32, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt128, 128, 32, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt128, 128, 32, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt128, 128, 32, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt256', function () {
    it('add()', function () { testOp(UInt256, 256, 64, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt256, 256, 64, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt256, 256, 64, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt256, 256, 64, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt512', function () {
    it('add()', function () { testOp(UInt512, 512, 128, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt512, 512, 128, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt512, 512, 128, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt512, 512, 128, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt1024', function () {
    it('add()', function () { testOp(UInt1024, 1024, 256, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt1024, 1024, 256, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt1024, 1024, 256, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt1024, 1024, 256, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt2048', function () {
    it('add()', function () { testOp(UInt2048, 2048, 512, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt2048, 2048, 512, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt2048, 2048, 512, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt2048, 2048, 512, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt4096', function () {
    it('add()', function () { testOp(UInt4096, 4096, 1024, 10, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt4096, 4096, 1024, 10, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt4096, 4096, 1024, 10, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt4096, 4096, 1024, 10, opDivBigInt, opDivUInt); });
  });
  describe('UInt8192', function () {
    it('add()', function () { testOp(UInt8192, 8192, 2048, 10, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt8192, 8192, 2048, 10, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt8192, 8192, 2048, 10, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt8192, 8192, 2048, 10, opDivBigInt, opDivUInt); });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// AES
///////////////////////////////////////////////////////////////////////////////////////////////////

const KEY128 = new Buffer(new Uint8Array([
    0x04,0x01,0x08,0x0A,0xFF,0x1A,0x5C,0xE1,
    0x9A,0x6F,0x2B,0x6C,0x25,0x43,0x61,0x87
]));
const KEY192 = new Buffer(new Uint8Array([
    0x04,0x01,0x08,0x0A,0xFF,0x1A,0x5C,0xE1,
    0x9A,0x6F,0x2B,0x6C,0x25,0x43,0x61,0x87,
    0xDD,0xFE,0x1F,0xAB,0xEF,0x56,0x11,0x7A
]));
const KEY256 = new Buffer(new Uint8Array([
    0x04,0x01,0x08,0x0A,0xFF,0x1A,0x5C,0xE1,
    0x9A,0x6F,0x2B,0x6C,0x25,0x43,0x61,0x87,
    0xDD,0xFE,0x1F,0xAB,0xEF,0x56,0x11,0x7A,
    0xA6,0x19,0x2A,0x05,0xA0,0xEE,0xBB,0xAA
]));
const IV = new Buffer(new Uint8Array([
    0x02,0x06,0x0A,0xFF,0xEF,0x6A,0x3C,0xA1,
    0x2A,0x6D,0x1E,0x3A,0x1B,0x21,0x42,0x7B
]));
const DATA15 = new Buffer(new Uint8Array([
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E
]));
const DATA16 = new Buffer(new Uint8Array([
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
]));

function testAES(type, key, iv, data) {
  const data_enc = new Buffer(data.byteLength);
  const data_dec = new Buffer(data.byteLength);
  const aes = new type();
  aes.setKey(key);
  if (iv) aes.setIV(iv);
  aes.encrypt(data, data_enc);
  aes.decrypt(data_enc, data_dec);
  chai.expect(indexedDB.cmp(data, data_dec)).to.equal(0);
  chai.expect(indexedDB.cmp(data, data_enc)).to.not.equal(0);
  chai.expect(indexedDB.cmp(data_enc, data_dec)).to.not.equal(0);
  aes.encrypt(data, data_enc);
  aes.decrypt(data_enc, data_dec);
  chai.expect(indexedDB.cmp(data, data_dec)).to.equal(0);
  chai.expect(indexedDB.cmp(data, data_enc)).to.not.equal(0);
  chai.expect(indexedDB.cmp(data_enc, data_dec)).to.not.equal(0);
}

describe('AES', function () {
  describe('AES-ECB', function () {
    it('AES128-ECB', function () { testAES(AES128ECB, KEY128, null, DATA16); });
    it('AES192-ECB', function () { testAES(AES192ECB, KEY192, null, DATA16); });
    it('AES256-ECB', function () { testAES(AES256ECB, KEY256, null, DATA16); });
  });
  describe('AES-CBC', function () {
    it('AES128-CBC', function () { testAES(AES128CBC, KEY128, IV, DATA16); });
    it('AES192-CBC', function () { testAES(AES192CBC, KEY192, IV, DATA16); });
    it('AES256-CBC', function () { testAES(AES256CBC, KEY256, IV, DATA16); });
  });
  describe('AES-CTR', function () {
    it('AES128-CTR', function () { testAES(AES128CTR, KEY128, IV, DATA15); });
    it('AES192-CTR', function () { testAES(AES192CTR, KEY192, IV, DATA15); });
    it('AES256-CTR', function () { testAES(AES256CTR, KEY256, IV, DATA15); });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// HASH
///////////////////////////////////////////////////////////////////////////////////////////////////

async function testHash(type, digestlen, name) {
  const hash = new type();
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<100;n++) {
    const len = getRandomInt(1024-1)+1;
    const data = new Buffer(len);
    for (var i=0;i<len;i++) {
      data[i] = getRandomInt(256);
    }
    hash.reset();
    hash.step(data);
    hash.finish(digest1);
    const d = await window.crypto.subtle.digest(name, data);
    const digest2 = new Uint8Array(d);
    chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
    data.free();
  }
}

describe('Hash', function () {
  describe('SHA256', function () {
    it('test', async function () {
      await testHash(SHA256, 32, "SHA-256");
    });
  });
  describe('SHA512', function () {
    it('test', async function () {
      await testHash(SHA512, 64, "SHA-512");
    });
  });
  describe('MD5', function () {
    it('test', function () {
      var hash = new MD5();
      var digest = new Buffer(16);
      var data = new Buffer([
        49, 50, 51, 52, 53, 54
      ]);
      hash.reset();
      hash.step(data);
      hash.finish(digest);
      const exp = new Uint8Array([
        0xE1,0x0A,0xDC,0x39,0x49,0xBA,0x59,0xAB,
        0xBE,0x56,0xE0,0x57,0xF2,0x0F,0x88,0x3E]);
      chai.expect(indexedDB.cmp(digest, exp)).to.equal(0);
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// HMAC
///////////////////////////////////////////////////////////////////////////////////////////////////

async function testHMAC(type, digestlen, name) {
  const hmac = new type();
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<100;n++) {
    const datalen = getRandomInt(1024-1)+1;
    const data = new Buffer(datalen);
    for (var i=0;i<datalen;i++) {
      data[i] = getRandomInt(256);
    }
    const keylen = getRandomInt(64-1)+1;
    const key = new Buffer(keylen);
    for (var i=0;i<keylen;i++) {
      key[i] = getRandomInt(256);
    }
    hmac.reset(key);
    hmac.step(data);
    hmac.finish(digest1);
    const c = await window.crypto.subtle.importKey('raw', key, { name: 'HMAC', hash: name },true, ['sign']);
    const s = await window.crypto.subtle.sign('HMAC', c, data);
    const digest2 = new Uint8Array(s);
    chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
    data.free();
    key.free();
  }
}

describe('HMAC', function () {
  describe('SHA256', function () {
    it('test', async function () {
      await testHMAC(HMACSHA256, 32, "SHA-256");
    });
  });
  describe('SHA512', function () {
    it('test', async function () {
      await testHMAC(HMACSHA512, 64, "SHA-512");
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// PBKDF2
///////////////////////////////////////////////////////////////////////////////////////////////////

async function testPBKDF2(func, digestlen, name, iterations) {
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<5;n++) {
    const pwlen = getRandomInt(1024-1)+1;
    const pw = new Buffer(pwlen);
    for (var i=0;i<pwlen;i++) {
      pw[i] = getRandomInt(256);
    }
    const saltlen = getRandomInt(64-1)+1;
    const salt = new Buffer(saltlen);
    for (var i=0;i<saltlen;i++) {
      salt[i] = getRandomInt(256);
    }
    func(pw, salt, digest1, iterations);
    const c = await window.crypto.subtle.importKey("raw", pw, "PBKDF2", false, ["deriveBits"]);
    const s = await window.crypto.subtle.deriveBits(
    {
      name: "PBKDF2",
      hash: name,
      salt: salt,
      iterations: iterations
    }, c, digestlen*8);
    const digest2 = new Uint8Array(s);
    chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
    pw.free();
    salt.free();
  }
}

describe('PBKDF2', function () {
  describe('SHA256', function () {
    it('test', async function () {
      await testPBKDF2(PBKDF2.sha256, 32, "SHA-256", 10000);
    });
  });
  describe('SHA512', function () {
    it('test', async function () {
      await testPBKDF2(PBKDF2.sha512, 32, "SHA-512", 10000);
    });
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////
// DH
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIME
///////////////////////////////////////////////////////////////////////////////////////////////////

describe('Prime', function () {
  describe('test(string)', function () {
    it('test("3") [32][small]', function () {
      const r = Prime.test("3", false, 0);
      chai.expect(r).to.equal(1);
    });
    it('test("4572648") [32][small]', function () {
      const r = Prime.test("4572648", false, 0);
      chai.expect(r).to.equal(0);
    });
    it('test("18446744073709551557") [64][large]', function () {
      const r = Prime.test("18446744073709551557", false, 0);
      chai.expect(r).to.equal(1);
    });
  });
  describe('test(number)', function () {
    it('test(17) [32][small]', function () {
      const r = Prime.test(17, false, 0);
      chai.expect(r).to.equal(1);
    });
  });
  describe('test(bigint)', function () {
    it('test(0x0397ffffffffffffffffffffffffffffn) [128][large]', function () {
      const r = Prime.test(0x0397ffffffffffffffffffffffffffffn, false, 255);
      chai.expect(r).to.equal(2);
    });
    it('test(170141183460469231731687303715884105727n) [128][mersenne]', function () {
      const r = Prime.test(170141183460469231731687303715884105727n, false, 255);
      chai.expect(r).to.equal(1);
    });
  });
});
