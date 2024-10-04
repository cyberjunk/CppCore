import { Buffer } from '../libcppcore.js';

describe('Buffer', function () {
  describe('constructor()', function () {
    it('from size', function () {
      const b = new Buffer(16);      
      chai.expect(b.byteLength).to.equal(16);
    });
  });
});
