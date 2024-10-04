import { CString } from '../libcppcore.js';

describe('CString', function () {
  describe('constructor()', function () {
    it('from size', function () {
      const s = new CString(15);
      chai.expect(s.usedLength).to.equal(0);
      chai.expect(s.maxLength).to.equal(15);
      chai.expect(s._buffer.byteLength).to.equal(16);
    });
    it('from string', function () {
      const s = new CString("Hello World!");
      chai.expect(s.usedLength).to.equal(12);
      chai.expect(s.maxLength).to.equal(12);
      chai.expect(s._buffer.byteLength).to.equal(13);
    });
  });
});
