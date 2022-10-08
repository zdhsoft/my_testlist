
// 虽然测试，但是不能用。。。
const u = 'magnet:?xt=urn:btih:19b097d41a2f11438b52acd22ab74fd195c2db5f&dn=[%E7%94%B5%E5%BD%B1%E5%A4%A9%E5%A0%82www.dytt89.com]%E6%B5%B4%E8%A1%80%E6%97%A0%E5%90%8D%E5%B7%9D-2021_HD%E5%9B%BD%E8%AF%AD%E4%B8%AD%E5%AD%97.mp4&tr=http://t.t789.me:2710/announce&tr=http://t.t789.co:2710/announce&tr=http://t.t789.vip:2710/announce';
let url = new URL(u);
const s = decodeURIComponent(u);
console.log(JSON.stringify(s));
