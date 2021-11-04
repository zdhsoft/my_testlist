const { getLogger, utils } = require('xmcommon');
const log = getLogger(__filename);

// log.info('hello');
let m = new WeakMap();

log.info(process.argv);

function testWeakMap() {
    memoryInfo("****11>>>");
    global.gc();
    memoryInfo("****12>>>");
    let k = new Array(5 * 1024 * 1024);
    memoryInfo("****13>>>");
    m.set(k, '1999');
    memoryInfo("****15>>>");
    //delete k;
    //memoryInfo("****16>>>");
    k = null;
    memoryInfo("****17>>>");
    global.gc();
    memoryInfo("****18>>>");
}

function memoryInfo(paramPrompt) {
    log.info(`${paramPrompt}:${utils.formatMemory(process.memoryUsage().heapUsed)}`);
}

memoryInfo("0>>>");
log.info('length0:' + m.length);
memoryInfo("1>>>");
testWeakMap();
memoryInfo("2>>>");
log.info('length1:' + m.length);
memoryInfo("3>>>");

let o = [];
let weakObjList = [];
function testFunciton() {
    let a = {a:1};
    let b = {b:2};
    let c = {c:"999"};
    o.push(c);
    weakObjList.push([new WeakRef(a), "a"]);
    weakObjList.push([new WeakRef(b), "b"]);
    weakObjList.push([new WeakRef(c), "c"]);
    delete a;
    delete b;
    a = null;
    b = null;
}

function checkLeak() {
    global.gc();
    log.info("--->checkLeak:" + weakObjList.length);
    for(let w of weakObjList) {
        log.info(w[0].deref(), w[1]);
    }
}


testFunciton();
checkLeak();
