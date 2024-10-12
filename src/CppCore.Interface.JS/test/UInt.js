import { 
    UInt128 
} from '../libcppcore.js';

describe('UInt', function () {
  describe('UInt128', function () {
    it('add()', function () {
      const a = new UInt128("9999999999999999999999");
      const b = new UInt128("1");
      const c = new UInt128("10000000000000000000000")
      a.add(b);
      chai.expect(indexedDB.cmp(a._buffer, c._buffer)).to.equal(0);
    });
    it('sub()', function () {
        const a = new UInt128("9999999999999999999999");
        const b = new UInt128("9999999999999999999999");
        const c = new UInt128("0")
        a.sub(b);
        chai.expect(indexedDB.cmp(a._buffer, c._buffer)).to.equal(0);
    });
  });
});
