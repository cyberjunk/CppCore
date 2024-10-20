import {
    Buffer,
    HMACSHA256,
    HMACSHA512
} from '../libcppcore.js';

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}

async function test(type, digestlen, name) {
  const hmac = new type();
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<100;n++) {
    const datalen = getRandomInt(1024-1)+1;
    const data = new Buffer(datalen);
    for (var i=0;i<datalen;i++) {
      data[i] = getRandomInt(256);
    }
    const keylen = getRandomInt(64-1)+1;
    const key = new Buffer(keylen);
    for (var i=0;i<keylen;i++) {
      key[i] = getRandomInt(256);
    }
    hmac.reset(key);
    hmac.step(data);
    hmac.finish(digest1);
    const c = await window.crypto.subtle.importKey('raw', key, { name: 'HMAC', hash: name },true, ['sign']);
    const s = await window.crypto.subtle.sign('HMAC', c, data);
    const digest2 = new Uint8Array(s);
    chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
    data.free();
    key.free();
  }
}

describe('HMAC', function () {
    describe('SHA256', function () {
      it('test', async function () {
        await test(HMACSHA256, 32, "SHA-256");
      });
    });
    describe('SHA512', function () {
      it('test', async function () {
        await test(HMACSHA512, 64, "SHA-512");
      });
    });
});
