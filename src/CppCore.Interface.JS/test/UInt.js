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
    if (str == "0x0") 
      str = "0x1";
    return str;
}

function opAddBigInt(t, a, b, r)    { r = a + b; return r; }
function opAddUInt  (t, a, b, r, q) { t.add(a,b,r); return r; }
function opSubBigInt(t, a, b, r)    { r = a - b; return r; }
function opSubUInt  (t, a, b, r, q) { t.sub(a,b,r); return r; }
function opMulBigInt(t, a, b, r)    { r = a * b; return r; }
function opMulUInt  (t, a, b, r, q) { t.mul(a,b,r); return r; }
function opDivBigInt(t, a, b, r)    { r = a / b; return r; }
function opDivUInt  (t, a, b, r, q) { t.divmod(a,b,r,q); return r; }

function testOp(type, bits, maxhexsymbols, iterations, opbig, opuint) {
    var a2 = new type();        
    var b2 = new type();
    var r2 = new type();
    var t2 = new type();
    for(var n=0;n<iterations;n++) {
      var stra = getRandomHexStr(maxhexsymbols);
      var strb = getRandomHexStr(maxhexsymbols);
      var a1 = BigInt(stra);
      var b1 = BigInt(strb);
      var r1 = BigInt(0);
      a2.set(stra);
      b2.set(strb);
      r1 = opbig(type, a1, b1, r1);
      r1 = BigInt.asUintN(bits, r1);
      r2 = opuint(type, a2, b2, r2, t2);
      chai.expect(r1.toString()).to.equal(r2.toString());
    }
}

describe('UInt', function () {
  describe('UInt32', function () {
    it('add()', function () { testOp(UInt32, 32, 8, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt32, 32, 8, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt32, 32, 8, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt32, 32, 8, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt64', function () {
    it('add()', function () { testOp(UInt64, 64, 16, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt64, 64, 16, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt64, 64, 16, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt64, 64, 16, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt128', function () {
    it('add()', function () { testOp(UInt128, 128, 32, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt128, 128, 32, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt128, 128, 32, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt128, 128, 32, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt256', function () {
    it('add()', function () { testOp(UInt256, 256, 64, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt256, 256, 64, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt256, 256, 64, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt256, 245, 64, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt512', function () {
    it('add()', function () { testOp(UInt512, 512, 128, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt512, 512, 128, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt512, 512, 128, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt512, 512, 128, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt1024', function () {
    it('add()', function () { testOp(UInt1024, 1024, 256, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt1024, 1024, 256, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt1024, 1024, 256, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt1024, 1024, 256, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt2048', function () {
    it('add()', function () { testOp(UInt2048, 2048, 512, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt2048, 2048, 512, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt2048, 2048, 512, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt2048, 2048, 512, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt4096', function () {
    it('add()', function () { testOp(UInt4096, 4096, 1024, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt4096, 4096, 1024, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt4096, 4096, 1024, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt4096, 4096, 1024, 100, opDivBigInt, opDivUInt); });
  });
  describe('UInt8192', function () {
    it('add()', function () { testOp(UInt8192, 8192, 2048, 100, opAddBigInt, opAddUInt); });
    it('sub()', function () { testOp(UInt8192, 8192, 2048, 100, opSubBigInt, opSubUInt); });
    it('mul()', function () { testOp(UInt8192, 8192, 2048, 100, opMulBigInt, opMulUInt); });
    it('div()', function () { testOp(UInt8192, 8192, 2048, 100, opDivBigInt, opDivUInt); });
  });
});
