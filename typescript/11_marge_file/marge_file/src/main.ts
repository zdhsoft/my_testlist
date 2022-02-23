import { getLogger, utils, XCommonRet } from 'xmcommon';
import * as fs from 'fs';
import * as path from 'path';

const log = getLogger(__filename);

// log.info('hello world!');

// const dir = 'C:/adobeTemp/a.m3u8_content';
// const list = fs.readdirSync(dir);
// const k: number[] = [];
// for (const f of list) {
//     const t = utils.ToInteger(f, -1);
//     log.info('file:' + f + ' => ' + t);
//     if (t !== -1) {
//         k.push(t);
//     }
// }

// k.sort((a, b) => a - b);

// const s = fs.createWriteStream('C:/adobeTemp/a.ts');
// for (const fileid of k) {
//     const p = path.join(dir, String(fileid));
//     const data = fs.readFileSync(p);
//     log.info('--->' + fileid);
//     s.write(data);
// }
// log.info('aaaa 开始等待完成!');
// s.end(() => {
//     log.info('end ----->');
// });
// s.on('finish', () => {
//     log.info('finish event');
// });

async function readDir(paramDir: string) {
    const r = new XCommonRet();
    do {
        if (!utils.fileExists(paramDir)) {
            r.setError(-1, `指定的目录不存在!`);
        }
    } while (false);
    return r;
}

async function readM3U8File(paramFileName: string) {
    do {
        if (!utils.fileExists(paramFileName)) {
            log.info('文件不存在:' + paramFileName);
            break;
        }
        const data = fs.readFileSync(paramFileName, { encoding: 'utf8' });
        const t = data.split('\n');

        const fileList: string[] = [];
        t.forEach((v) => {
            const newV = v.trim();
            if (!newV.startsWith('#')) {
                fileList.push(newV);
            }
        });
        log.info(fileList);
    } while (false);
}

readM3U8File('C:/adobeTemp/a.m3u8');
