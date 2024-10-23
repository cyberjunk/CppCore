import {
    Buffer,
    PBKDF2
} from '../libcppcore.js';

function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}

async function test(func, digestlen, name, iterations) {
  //const hmac = new type();
  const digest1 = new Buffer(digestlen);
  for(var n=0;n<10;n++) {
    const pwlen = getRandomInt(1024-1)+1;
    const pw = new Buffer(pwlen);
    for (var i=0;i<pwlen;i++) {
      pw[i] = getRandomInt(256);
    }
    const saltlen = getRandomInt(64-1)+1;
    const salt = new Buffer(saltlen);
    for (var i=0;i<saltlen;i++) {
      salt[i] = getRandomInt(256);
    }
    func(pw, salt, digest1, iterations);
    const c = await window.crypto.subtle.importKey("raw", pw, "PBKDF2", false, ["deriveBits"]);
    const s = await window.crypto.subtle.deriveBits(
    {
        name: "PBKDF2",
        hash: name,
        salt: salt,
        iterations: iterations
    }, c, digestlen*8);
    const digest2 = new Uint8Array(s);
    chai.expect(indexedDB.cmp(digest1, digest2)).to.equal(0);
    pw.free();
    salt.free();
  }
}

describe('PBKDF2', function () {
    describe('SHA256', function () {
      it('test', async function () {
        await test(PBKDF2.sha256, 32, "SHA-256", 10000);
      });
    });
    describe('SHA512', function () {
      it('test', async function () {
        await test(PBKDF2.sha512, 32, "SHA-512", 10000);
      });
    });
});
