import { 
    UInt32, 
    UInt64, 
    UInt128, 
    UInt256, 
    UInt512, 
    UInt1024, 
    UInt2048, 
    UInt4096, 
    UInt8192 
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

function opAddBigInt(a, b) { a += b; return a; }
function opAddUInt  (a, b) { a.add(b); return a; }
function opSubBigInt(a, b) { a -= b; return a; }
function opSubUInt  (a, b) { a.sub(b); return a; }
function opMulBigInt(a, b) { a *= b; return a; }
function opMulUInt  (a, b) { a.mul(b); return a; }

function testOp(type, bits, maxhexsymbols, iterations, opbig, opuint) {
    var a2 = new type();        
    var b2 = new type();
    for(var n=0;n<iterations;n++) {
      var stra = getRandomHexStr(maxhexsymbols);
      var strb = getRandomHexStr(maxhexsymbols);
      var a1 = BigInt(stra);
      var b1 = BigInt(strb);
      a2.set(stra);
      b2.set(strb);
      a1 = opbig(a1, b1);
      a1 = BigInt.asUintN(bits, a1);
      a2 = opuint(a2, b2);
      chai.expect(a1.toString()).to.equal(a2.toString());
    }
}

describe('UInt', function () {
  describe('UInt32', function () {
    it('add()', function () { testOp(UInt32, 32, 8, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt32, 32, 8, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt32, 32, 8, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt64', function () {
    it('add()', function () { testOp(UInt64, 64, 16, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt64, 64, 16, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt64, 64, 16, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt128', function () {
    it('add()', function () { testOp(UInt128, 128, 32, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt128, 128, 32, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt128, 128, 32, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt256', function () {
    it('add()', function () { testOp(UInt256, 256, 64, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt256, 256, 64, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt256, 256, 64, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt512', function () {
    it('add()', function () { testOp(UInt512, 512, 128, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt512, 512, 128, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt512, 512, 128, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt1024', function () {
    it('add()', function () { testOp(UInt1024, 1024, 256, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt1024, 1024, 256, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt1024, 1024, 256, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt2048', function () {
    it('add()', function () { testOp(UInt2048, 2048, 512, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt2048, 2048, 512, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt2048, 2048, 512, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt4096', function () {
    it('add()', function () { testOp(UInt4096, 4096, 1024, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt4096, 4096, 1024, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt4096, 4096, 1024, 100, opMulBigInt, opMulUInt); });
  });
  describe('UInt8192', function () {
    it('add()', function () { testOp(UInt8192, 8192, 1024, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt8192, 8192, 1024, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt8192, 8192, 1024, 100, opMulBigInt, opMulUInt); });
  });
});
