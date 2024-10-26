import { CString } from '../libcppcore.js';

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
