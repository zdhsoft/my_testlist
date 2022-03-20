// eslint-disable-next-line @typescript-eslint/no-var-requires

// eslint-disable-next-line @typescript-eslint/no-var-requires
const PDFParser = require('pdf2json');
const pdfParser = new PDFParser();
import * as fs from 'fs';
// eslint-disable-next-line @typescript-eslint/no-var-requires
const pdf_table_extractor = require('pdf-table-extractor');
const pdffile = 'd:/生产问题/C107922_19370_20210303T154840_133560105_01.pdf';

interface IExtractorPage {
    page: number;
    tables: string[];
}
interface IExtractorPDF {
    pageTables: IExtractorPage[];
    numPages: number;
    currentPages: number;
}

interface IPageR {
    T: string;
    S: number;
    TS: number[];
}
interface IPage {
    Width: number;
    Height: number;
    HLines: { x: number; y: number; w: number; l: number; oc: string }[];
    VLines: { x: number; y: number; w: number; l: number; oc: string }[];
    Fills: any[];
    Texts: {
        x: number;
        y: number;
        w: number;
        sw: number;
        A: string;
        R: IPageR[];
    }[];
}

interface IPDFJson {
    Transcoder: string;
    Meta: {
        PDFFormatVersion: string;
        IsAcroFormPresent: boolean;
        IsXFAPresent: boolean;
        Producer: string;
        CreationDate: string;
        ModDate: string;
        Metadata: any;
    };
    Pages: IPage[];
}

function FilterT(pdf: IPDFJson) {
    const TextList: string[] = [];
    pdf?.Pages?.forEach((page) => {
        page?.Texts?.forEach((text) => {
            text.R.forEach((R) => {
                const T = R?.T;
                if (T !== undefined && T !== null) {
                    R.T = decodeURIComponent(R.T);
                    TextList.push(R.T);
                }
            });
        });
    });

    fs.writeFileSync('./t.txt', TextList.join('\n'), 'utf8');
}

pdfParser.on('pdfParser_dataError', (errData: any) =>
    console.error(errData.parserError),
);
pdfParser.on('pdfParser_dataReady', (pdfData: IPDFJson) => {
    const d = pdfParser.getRawTextContent();
    fs.writeFileSync('./raw.txt', String(d));
    FilterT(pdfData);
    fs.writeFileSync('./F1040EZ.json', JSON.stringify(pdfData, null, 2));
});

pdfParser.on('readable', (meta: any) =>
    console.log('PDF Metadata', JSON.stringify(meta, null, 2)),
);
pdfParser.on('data', (page: any) =>
    console.log(
        page ? 'One page paged' : 'All pages parsed',
        JSON.stringify(page, null, 2),
    ),
);
pdfParser.on('error', (err: any) => console.error('Parser Error', err));

// const data = fs.readFileSync(pdffile);
// pdfParser.parseBuffer(data);

//PDF parsed
function success(result: any) {
    console.log(JSON.stringify(result, null, 2));
}

//Error
function error(err: any) {
    console.error('Error: ' + err);
}

pdf_table_extractor(pdffile, success, error);
