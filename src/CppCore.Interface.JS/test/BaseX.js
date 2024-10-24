import { 
  BaseX,
  Buffer
} from '../libcppcore.js';

describe('BaseX', function () {
  describe('constructor()', function () {
    it('constructor(string)', function () {
      const b = new BaseX("0123456789");      
      chai.expect(b._alphabet.byteLength).to.equal(10);
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
      chai.expect(indexedDB.cmp(t1._buffer,t2)).to.equal(0);
    });
    it('decode("18446744073709551615", 64)', function () {
      const b = new BaseX("0123456789");
      const t1 = b.decode("18446744073709551615", 64);
      const t2 = new Uint8Array([0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF]);
      chai.expect(indexedDB.cmp(t1._buffer,t2)).to.equal(0);
    });
  });
  describe('[B16] decode()', function () {
    it('decode("A", 32)', function () {
      const b = new BaseX("0123456789ABCDEF");
      const t1 = b.decode("A", 32);
      const t2 = new Uint8Array([0x0A, 0x00, 0x00, 0x00]);
      chai.expect(indexedDB.cmp(t1._buffer,t2)).to.equal(0);
    });
    it('decode("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 128)', function () {
      const b = new BaseX("0123456789ABCDEF");
      const t1 = b.decode("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 128);
      const t2 = new Uint8Array([
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
      ]);
      chai.expect(indexedDB.cmp(t1._buffer,t2)).to.equal(0);
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
