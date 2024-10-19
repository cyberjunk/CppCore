import { 
    Buffer, 
    SHA256,
    SHA512
} from '../libcppcore.js';

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}

function test(type, digestlen, name) {
  const hash = new type();
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<100;n++) {
    const len = getRandomInt(1024);
    const data = new Buffer(len);
    for (var i=0;i<len;i++) {
      data[i] = getRandomInt(256);
    }
    hash.reset();
    hash.step(data);
    hash.finish(digest1);
    window.crypto.subtle.digest(name, data).then((d) => {
      const digest2 = new Uint8Array(d);
      chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
      data.free();
    });
  }
}

describe('Hash', function () {
  describe('SHA256', function () {
    it('test', function () {
      test(SHA256, 32, "SHA-256");
    });
  });
  describe('SHA512', function () {
    it('test', function () {
      test(SHA512, 64, "SHA-512");
    });
  });
});
