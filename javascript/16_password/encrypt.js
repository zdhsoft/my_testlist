
const crypto = require('crypto');
const algorithm = 'aes-256-cbc';

const keyStr = "85Z5j&;7kelAILgn;.SZy6KH#T<S&CWZ"
const ivStr = "fpDrRDmL&jUF9m|p";
const key = Buffer.from(keyStr);
const iv = Buffer.from(ivStr);

const textEncoding = 'utf-8';

function encrypt(paramText, paramKey, paramIv) {
    const c = crypto.createCipheriv(algorithm, paramKey, paramIv);
    let t = c.update(paramText, textEncoding);
    t = Buffer.concat([t, c.final()]);
    return t.toString('base64');
}

function decrypt(paramText, paramKey, paramIv) {
    const b = Buffer.from(paramText, 'base64');
    const d = crypto.createDecipheriv(algorithm, paramKey, paramIv);
    let t = d.update(b);
    t = Buffer.concat([t, d.final()]);
    return t.toString(textEncoding);
}

const text = '测试加密abcdefg';
console.log(`原文：[${text}]`);
const mi = encrypt(text, key, iv);
console.log(`密文：[${mi}]`);
const jm = decrypt(mi, key, iv);
console.log(`解密:[${jm}]`);
