import * as xlsx from 'xlsx';
export class XExcelUtils {
    /**
     * 读取excel 信息并返回：
     * @param paramFilePath 读取的文件路径
     */
    public static readExcelByFile(paramFilePath: string) {
        const book = xlsx.readFile(paramFilePath); //  xlsx.readFileSync(filePath);
        const obj: any = {};
        for (const s of book.SheetNames) {
            const sheet = book.Sheets[s];
            const sheetObject = xlsx.utils.sheet_to_json(sheet);
            obj[s] = sheetObject;
        }
        return obj;
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
