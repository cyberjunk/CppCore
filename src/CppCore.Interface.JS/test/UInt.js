import { 
    UInt128 
} from '../libcppcore.js';

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}
function getRandomHexStr(max) {
    const symbols = "0123456789ABCDEF";
    const len = getRandomInt(max-1) + 1;
    var str = "0x";
    for (var i=0; i < len; i++) {
        str += symbols[getRandomInt(16)];
    }
    return str;
}
function testAdd(type, bits, maxhexsymbols, iterations) {
    var a2 = new type();        
    var b2 = new type();
    for(var n=0;n<iterations;n++) {
      var stra = getRandomHexStr(maxhexsymbols);
      var strb = getRandomHexStr(maxhexsymbols);
      var a1 = BigInt(stra);
      var b1 = BigInt(strb);
      a2.set(stra);
      b2.set(strb);
      a1 += b1;
      a1 = BigInt.asUintN(bits, a1);
      a2.add(b2);
      chai.expect(a1.toString()).to.equal(a2.toString());
    }
}

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
    it('test()', function () {
        testAdd(UInt128, 128, 32, 100);
    });
  });
});
