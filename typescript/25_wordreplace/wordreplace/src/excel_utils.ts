import * as xlsx from 'xlsx';
import { XCommonRet } from 'xmcommon';
import fs from 'fs';
export class XExcelUtils {
    /**
     * 读取excel 信息并返回：
     * @param paramFilePath 读取的文件路径
     */
    public static readExcelByFile(paramFilePath: string) {
        const r = new XCommonRet();
        do {
            //
            if (!fs.existsSync(paramFilePath)) {
                r.setError(-1, `文件不存在:${paramFilePath}`);
                break;
            }

            const fsstat = fs.statSync(paramFilePath);
            if (!fsstat.isFile()) {
                r.setError(-2, `它不是文件:${paramFilePath}`);
                break;
            }
            try {
                const book = xlsx.readFile(paramFilePath); //  xlsx.readFileSync(filePath);
                const obj: any = {};
                for (const s of book.SheetNames) {
                    const sheet = book.Sheets[s];
                    const sheetObject = xlsx.utils.sheet_to_json(sheet);
                    obj[s] = sheetObject;
                }
                r.setOK(obj);
            } catch (e) {
                r.setError(-3, `读取文件发生异常:${paramFilePath}:error:${e}`);
                break;
            }
        } while (false);
        return r;
        // // 取第一个Sheet页面
        // const sheet = book.Sheets[book.SheetNames[0]];
        // // 默认第一行是key，key不存在时，值也不显示
        // const sheetObject = xlsx.utils.sheet_to_json(sheet);
        // // const sheetObject = xlsx.utils.book_to
        // return sheetObject;
    }
    /**
     * 读取excel 信息并返回：
     * @param paramData 读取的文件路径
     */
    public static readExcelByBuffer(paramData: Buffer) {
        const book = xlsx.read(paramData, { type: 'buffer' });
        // 取第一个Sheet页面
        const sheet = book.Sheets[book.SheetNames[0]];
        // 默认第一行是key，key不存在时，值也不显示
        const sheetObject = xlsx.utils.sheet_to_json(sheet);
        return sheetObject;
    }
}
