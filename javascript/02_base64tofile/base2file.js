const fs = require('fs');

/**
 * 这个脚本以前就写过，就几行代码，但是一时半会找不到，网上的基本上，都是用不了的！只好自己再写一个。
 */

function printUsage() {
    let prompt = [
        'BASE64编写的文件转二进制文件的脚本。',
        'version: 1.0',
        '作者：zdhsoft',
        '参数：',
        'node base2file.js base64FileName outFileName',
    ];

    for(let p of prompt) {
        console.log(p);
    }
}

/**
 * 检查参数
 */
function checkArgs() {
    let result = {
        /** @type {boolean} 结果 */
        ret: true,
        /** @type {[string]} 获取的参数 */
        argv:[]
    }
    /** @type {[string]} 系统传入参数 */
    const systemArgv = process.argv;

    for (let i = 2; i < systemArgv.length; i++) {
        result.argv.push(systemArgv[i]);
    }

    if (result.argv.length !== 2) {
        console.log("传入参数不对");
        result.ret = false;
        return result;
    }
    return result;
}

/**
 * 将base64转为二进制文件
 * @param {string} paramSrcFileName 源文件名
 * @param {string} paramOutFileName 目标文件名
 */
function base2file(paramSrcFileName, paramOutFileName) {
    console.log(`begin ${paramSrcFileName}==>`)
    let base64Data = fs.readFileSync(paramSrcFileName);
    let base64String = base64Data.toString('utf-8');
    let destData = Buffer.from(base64String, 'base64');
    fs.writeFileSync(paramOutFileName, destData);
    console.log(`end!`)

}

function main() {
    printUsage();
    let {ret, argv} = checkArgs();
    if (!ret) {
        return;
    }
    base2file(argv[0], argv[1]);
}

main();
console.log('>>finish!');
