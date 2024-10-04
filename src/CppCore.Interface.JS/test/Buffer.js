import { Buffer } from '../libcppcore.js';

describe('Buffer', function () {
  describe('constructor()', function () {
    it('copy from Uint8Array', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a);      
      chai.expect(b.byteLength).to.equal(8);
      chai.expect(indexedDB.cmp(a, b)).to.equal(0);
    });
    it('init as view', function () {
      const a = new Uint8Array([0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08]);
      const b = new Buffer(a); 
      const c = new Buffer(b.buffer, b.byteOffset, b.byteLength)    
      chai.expect(c.byteLength).to.equal(8);
      chai.expect(indexedDB.cmp(a, c)).to.equal(0);
      chai.expect(b.buffer).to.equal(c.buffer);
    });
    it('init with size', function () {
      const a = new Buffer(16);      
      chai.expect(a.byteLength).to.equal(16);
    });
  });
  describe('slice()', function () {
    it('test1', function () {
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
    it('test1', function () {
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
