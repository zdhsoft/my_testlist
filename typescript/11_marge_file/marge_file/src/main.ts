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

interface IFileInfo {
    fullPath?: string;
    baseName?: string;
    extName?: string;
    videoPath?: string;
    orgExtName?: string;
}

async function readDir(paramDir: string) {
    const r = new XCommonRet<IFileInfo[]>();
    do {
        if (!utils.fileExistsSync(paramDir)) {
            r.setError(-1, `指定的目录不存在:` + paramDir);
            break;
        }

        const list = fs.readdirSync(paramDir);
        const m3u8List: IFileInfo[] = [];
        list.forEach((f) => {
            const basename = path.basename(f);
            const extname = path.extname(f);
            const lowExtName = extname.trim().toLowerCase();

            if (lowExtName === '.m3u8') {
                const b = basename.split('.');
                const info: IFileInfo = {
                    fullPath: path.join(paramDir, f),
                    baseName: b[0],
                    extName: lowExtName,
                    orgExtName: extname,
                    videoPath: path.join(paramDir, b[0]),
                };
                m3u8List.push(info);
            }
        });
        m3u8List.forEach((v) => {
            log.info('--->' + JSON.stringify(v));
        });
        r.setData(m3u8List);
    } while (false);
    return r;
}

async function readM3U8File(
    paramFileName: string,
    paramInfo: IFileInfo,
    parmOutDir: string,
) {
    do {
        if (!utils.fileExistsSync(paramFileName)) {
            log.info('文件不存在:' + paramFileName);
            break;
        }
        const dirname = paramFileName + '_contents';
        if (!utils.fileExistsSync(dirname)) {
            log.info('目录不存在:' + dirname);
            break;
        }

        log.info('begin:' + paramFileName);

        const sss = (paramInfo.baseName as string).split('-');
        let bbname = paramInfo.baseName as string;
        if (sss?.length > 1) {
            const mm: string[] = [];
            for (let i = 0; i < sss.length - 1; i++) {
                mm.push(sss[i]);
            }
            bbname = mm.join('');
        }
        const outname = path.join(parmOutDir, bbname + '.mp4');

        if (utils.fileExistsSync(outname)) {
            log.info('exits: ' + outname);
            return;
        }
        const fsout = fs.createWriteStream(outname);

        const data = fs.readFileSync(paramFileName, { encoding: 'utf8' });
        const t = data.split('\n');

        //const fileList: string[] = [];
        t.forEach((v) => {
            const newV = v.trim();
            if (newV.length <= 1) {
                return;
            }
            if (!newV.startsWith('#')) {
                const s = newV.split('/');
                const ss = s[s.length - 1];
                const ff = path.join(dirname, ss);
                try {
                    // log.info(ff, newV, ss);
                    if (utils.fileExistsSync(ff)) {
                        const data = fs.readFileSync(ff);
                        fsout.write(data);
                    }
                } catch (e) {
                    log.info('----->' + String(e));
                }
            }
        });
        await utils.WaitClassFunctionEx(fsout, 'end');
    } while (false);
}

const fileDir = 'g:/v';
const outDir = 'C:/adobeTemp';
async function main() {
    const r = new XCommonRet();
    do {
        const listResult = await readDir(fileDir);
        if (listResult.isNotOK) {
            r.assignFrom(listResult);
            break;
        }
        //
        const list = listResult.data as IFileInfo[];
        for (const f of list) {
            await readM3U8File(f.fullPath as string, f, outDir);
        }
    } while (false);
    if (r.isNotOK) {
        log.info('exit:' + r.getErrorInfo());
    } else {
        log.info('finish alll!');
    }
    return r;
}
main();

// readM3U8File('C:/adobeTemp/a.m3u8');
