/*************************************************************************
 * Copyright(c) 2017-2022,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 zdhsoft      创建文件            2022-09-05
 *************************************************************************/
import { utils } from 'xmcommon';
import path from 'path';
import fs from 'fs';

function printUsage() {
    console.log('usage: --cfg 规则文件 --srcdir 源文件目录 --destdir 目标目录');
}

const cfgList: { key: string; dir: string; line: string; code: number }[] = [];

function loadCfg(paramCfg: string, paramDest: string): boolean {
    let r = true;
    const data = fs.readFileSync(paramCfg, 'utf8');
    const list = data.split(/\r?\n/);
    for (let i = 0; i < list.length; i++) {
        const line = list[i];
        const s = line.split(/\s+/);
        if (s.length === 0) {
            continue;
        }
        if (s.length === 1 && s[0] === '') {
            continue;
        }
        if (s.length !== 2) {
            console.log(`第${i + 1}行是无效的:${line}`);
            r = false;
            break;
        }
        cfgList.push({ key: s[0], dir: s[1], line, code: i });
    }
    if (!r) {
        return r;
    }
    for (let i = 0; i < cfgList.length; i++) {
        const cfg = cfgList[i];
        const dest = path.join(paramDest, cfg.dir);
        if (utils.fileExistsSync(dest)) {
            if (!utils.isDirSync(dest)) {
                console.log(`${dest}已经存在，但不是目录! lines: 第${cfg.code + 1}行的:${cfg.line}`);
                r = false;
                break;
            }
        } else {
            // 如果不存在，则创建
            const result = utils.mkdirsSyncEx(dest);
            if (!result.ret) {
                console.log(`创建目录失败: ${dest}`);
                r = false;
                break;
            }
        }
    }
    if (!r) {
        return r;
    }
    return true;
}

function findPath(paramFileName: string) {
    for (const c of cfgList) {
        if (paramFileName.includes(c.key)) {
            return c;
        }
    }
    return null;
}

function doCopy(paramSrc: string, paramDest: string) {
    const list = fs.readdirSync(paramSrc);
    let cnt = 0;

    console.log('开始复制文件...');

    for (let i = 0; i < list.length; i++) {
        const fileName = list[i];
        const srcFile = path.join(paramSrc, fileName);
        if (!utils.isFileSync(srcFile)) {
            // 如果不是文件则跳过
            console.log(`不是文件,跳过[${i + 1}:${list.length}]: ${srcFile}`);
            continue;
        }
        const findResult = findPath(fileName);
        let destFile = path.join(paramDest, fileName);
        if (findResult !== null) {
            destFile = path.join(paramDest, findResult.dir, fileName);
        }
        console.log(`copy file:[${i + 1}:${list.length}], ${srcFile} => ${destFile}...`);
        fs.copyFileSync(srcFile, destFile);
        cnt++;
    }

    console.log(`完成，成功复制${cnt}个文件`);
}

function main() {
    const args = utils.options(process.argv);
    const cfg: string = args.args['cfg'];
    const srcdir: string = args.args['srcdir'];
    const destdir: string = args.args['destdir'];
    if (utils.isNull(cfg) || utils.isNull(srcdir) || utils.isNull(destdir)) {
        printUsage();
        return;
    }

    if (!utils.fileExistsSync(srcdir)) {
        console.log(`目录：${srcdir}不存在!`);
        return;
    }

    if (!utils.isDirSync(srcdir)) {
        console.log(`${srcdir}不是一个目录!`);
        return;
    }

    if (!utils.fileExistsSync(destdir)) {
        console.log(`目录：${destdir}不存在!`);
        return;
    }

    if (!utils.isDirSync(destdir)) {
        console.log(`${destdir}不是一个目录!`);
        return;
    }

    if (!utils.fileExistsSync(cfg)) {
        console.log(`文件：${cfg}不存在!`);
        return;
    }

    if (!utils.isFileSync(cfg)) {
        console.log(`${cfg}不是一个文件!`);
        return;
    }

    if (!loadCfg(cfg, destdir)) {
        return;
    }
    doCopy(srcdir, destdir);
}

main();
