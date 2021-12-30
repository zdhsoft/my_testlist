import fs from 'fs';
import { utils, common_ret } from 'xmcommon';

export class CommonUtils {
    /**
     * 读本地文件
     * @param paramFile 指定的文件名
     * @param paramCharset 字符集，默认填null，如果这里有设置编码，则会返回字符串，否则返回buffer
     */
    public static async readFileSync(paramFile: string, paramCharset: string | null = null): Promise<common_ret> {
        const ret = new common_ret();
        try {
            const [err, data] = await utils.WaitClassFunctionEx(fs, 'readFile', paramFile, { encoding: paramCharset });
            if (err) {
                ret.setError(-1, String(err));
            } else {
                ret.setOK(data);
            }
        } catch (e) {
            ret.setError(-2, String(e));
        }
        return ret;
    }
}
