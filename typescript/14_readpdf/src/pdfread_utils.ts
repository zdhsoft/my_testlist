import { IPDFJson } from './pdf2json_output_def';

// eslint-disable-next-line @typescript-eslint/no-var-requires
const PDFParser = require('pdf2json');
import { utils } from 'xmcommon';

export class XPDFReadUtils {
    public static async readPDFTextSync(paramFileName: string) {
        const [err, list] = await utils.WaitFunctionEx(XPDFReadUtils.readPDFText, paramFileName);
        return {
            err,
            list: list as string[],
        };
    }

    public static readPDFText(paramFileName: string, paramCallBack: (err?: any, text?: string[]) => void) {
        const pdfParser = new PDFParser();
        pdfParser.on('pdfParser_dataError', (errData: any) => paramCallBack(errData));
        pdfParser.on('pdfParser_dataReady', (pdfData: IPDFJson) => {
            const texts = XPDFReadUtils.FilterT(pdfData);
            paramCallBack(undefined, texts);
        });

        pdfParser.loadPDF(paramFileName);
    }

    private static FilterT(pdf: IPDFJson) {
        const TextList: string[] = [];
        pdf?.Pages?.forEach((page) => {
            page?.Texts?.forEach((text) => {
                text?.R?.forEach((R) => {
                    const T = R?.T;
                    if (T !== undefined && T !== null) {
                        R.T = decodeURIComponent(R?.T as string);
                        TextList.push(R.T);
                    }
                });
            });
        });
        return TextList;
    }
}
