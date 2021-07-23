//  对应的博客地址 https://zdhsoft.blog.csdn.net/article/details/119023500

let {datetimeUtils, codeUtils} = require('xmcommon');


const MM = 1000000;
const NN = 10000;

let keys = [];
function initKey() {
    console.log('初始化key:' + MM);
    keys = [];
    for(let i = 0; i < MM; i++) {
        let md5Value = codeUtils.MD5FromString(i.toString());
        keys.push(md5Value);
    }
}

function initObject() {
    console.log('初始化对象:' + MM);
    let o = {};
    for(let i = 0; i < keys.length; i++) {
        o[keys[i]] = i;
    }
    return o;
}

function initMap() {
    console.log('初始化Map:' + MM);
    let m = new Map();
    for(let i = 0; i < keys.length; i++) {
        m.set(keys[i], i);
    }
    return m;
}
initKey();
let o = initObject();
let m = initMap();
console.log("初始化完成，开始测试对象...")
let d1 = datetimeUtils.getNow();
for(let i = 0; i < keys.length; i++) {
    for(let j = 0; j < NN; j++) {
        let t = o[keys[i]];
    }
}
let d2 = datetimeUtils.getNow();
console.log("初始化完成，开始测试Map...");
let d4 = datetimeUtils.getNow();
for(let i = 0; i < keys.length; i++) {
    for(let j = 0; j < NN; j++) {
        let t = m.get(keys[i]);
    }
}
let d3 = datetimeUtils.getNow();
console.log('测试完成！');
let deta1 = d2 - d1;
let deta2 = d3 - d4;
console.log(`object:${deta1}, map:${deta2}`);
