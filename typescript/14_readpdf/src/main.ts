// eslint-disable-next-line @typescript-eslint/no-var-requires

// eslint-disable-next-line @typescript-eslint/no-var-requires
const PDFParser = require('pdf2json');
const pdfParser = new PDFParser();
import * as fs from 'fs';
import { IPDFJson } from './pdf2json_output_def';
import { XPDFReadUtils } from './pdfread_utils';
// eslint-disable-next-line @typescript-eslint/no-var-requires
// const pdf_table_extractor = require('pdf-table-extractor');
const pdffile = 'd:/生产问题/C107922_19370_20210303T154840_133560105_01.pdf';

async function main() {
    const a = await XPDFReadUtils.readPDFTextSync(pdffile);
    console.log(JSON.stringify(a, null, 2));
}

main();

// interface IExtractorPage {
//     page: number;
//     tables: string[];
// }
// interface IExtractorPDF {
//     pageTables: IExtractorPage[];
//     numPages: number;
//     currentPages: number;
// }

// pdfParser.on('pdfParser_dataError', (errData: any) =>
//     console.error(errData.parserError),
// );
// pdfParser.on('pdfParser_dataReady', (pdfData: IPDFJson) => {
//     const d = pdfParser.getRawTextContent();
//     fs.writeFileSync('./raw.txt', String(d));
//     FilterT(pdfData);
//     fs.writeFileSync('./F1040EZ.json', JSON.stringify(pdfData, null, 2));
// });

// pdfParser.on('readable', (meta: any) =>
//     console.log('PDF Metadata', JSON.stringify(meta, null, 2)),
// );
// pdfParser.on('data', (page: any) =>
//     console.log(
//         page ? 'One page paged' : 'All pages parsed',
//         JSON.stringify(page, null, 2),
//     ),
// );
// pdfParser.on('error', (err: any) => console.error('Parser Error', err));

// const data = fs.readFileSync(pdffile);
// pdfParser.parseBuffer(data);

// //PDF parsed
// function success(result: any) {
//     console.log(JSON.stringify(result, null, 2));
// }

// //Error
// function error(err: any) {
//     console.error('Error: ' + err);
// }

// pdf_table_extractor(pdffile, success, error);
