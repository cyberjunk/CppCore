import {
    Buffer,
    AES128ECB, AES192ECB, AES256ECB,
    AES128CBC, AES192CBC, AES256CBC,
    AES128CTR, AES192CTR, AES256CTR
} from '../libcppcore.js';

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
const DATA16 = new Buffer(new Uint8Array([
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F
]));

function test1(type, key, iv, n) {
    const data_enc = new Buffer(16);
    const data_dec = new Buffer(16);
    const aes = new type();
    aes.setKey(key);
    if (iv) aes.setIV(iv);
    aes.encrypt(DATA16, data_enc, n);
    aes.decrypt(data_enc, data_dec, n);
    chai.expect(indexedDB.cmp(DATA16, data_dec)).to.equal(0);
    chai.expect(indexedDB.cmp(DATA16, data_enc)).to.not.equal(0);
    chai.expect(indexedDB.cmp(data_enc, data_dec)).to.not.equal(0);
}

describe('AES', function () {
  describe('AES-ECB', function () {
    it('AES128-ECB', function () { test1(AES128ECB, KEY128, null, 1); });
    it('AES192-ECB', function () { test1(AES192ECB, KEY192, null, 1); });
    it('AES256-ECB', function () { test1(AES256ECB, KEY256, null, 1); });
  });
  describe('AES-CBC', function () {
    it('AES128-CBC', function () { test1(AES128CBC, KEY128, IV, 1); });
    it('AES192-CBC', function () { test1(AES192CBC, KEY192, IV, 1); });
    it('AES256-CBC', function () { test1(AES256CBC, KEY256, IV, 1); });
  });
  describe('AES-CTR', function () {
    it('AES128-CTR', function () { test1(AES128CTR, KEY128, IV, 16); });
    it('AES192-CTR', function () { test1(AES192CTR, KEY192, IV, 16); });
    it('AES256-CTR', function () { test1(AES256CTR, KEY256, IV, 16); });
  });
});
