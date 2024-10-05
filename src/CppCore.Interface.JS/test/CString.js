import { CString } from '../libcppcore.js';

describe('CString', function () {
  describe('constructor()', function () {
    it('constructor(null)', function () {
      const s = new CString();
      chai.expect(s.usedLength).to.equal(0);
      chai.expect(s.maxLength).to.equal(15);
      chai.expect(s._buffer.byteLength).to.equal(16);
    });
    it('constructor(number)', function () {
      const s = new CString(15);
      chai.expect(s.usedLength).to.equal(0);
      chai.expect(s.maxLength).to.equal(15);
      chai.expect(s._buffer.byteLength).to.equal(16);
    });
    it('constructor(string)', function () {
      const s = new CString("Hello World!");
      chai.expect(s.usedLength).to.equal(12);
      chai.expect(s.maxLength).to.equal(12);
      chai.expect(s._buffer.byteLength).to.equal(13);
    });
    it('constructor(cstring)', function () {
      const t = new CString("Hello World!");
      const s = new CString(t);
      chai.expect(s.usedLength).to.equal(12);
      chai.expect(s.maxLength).to.equal(12);
      chai.expect(s._buffer.byteLength).to.equal(13);
    });
  });
  describe('fromString()', function () {
    it('fromString(string)', function () {
      const s = new CString(31);
      s.fromString("0123456789");
      chai.expect(s.usedLength).to.equal(10);
      chai.expect(s.maxLength).to.equal(31);
      chai.expect(s._buffer.byteLength).to.equal(32);
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
