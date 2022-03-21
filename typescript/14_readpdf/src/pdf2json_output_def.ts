export interface IPDF2JSON_PageR {
    /**  actual text */
    T?: string;
    /** style index from style dictionary */
    S?: number;
    /** fontFaceId, fontSize */
    TS?: number[];

    RA?: number;
}
export interface IPDF2JSON_Page {
    /** width of the page in page unit */
    Width?: number;
    /** height of the page in page unit */
    Height?: number;
    /** horizontal line array */
    HLines?: { x: number; y: number; w: number; l: number; oc: string }[];
    /** vertical line array, */
    VLines?: { x: number; y: number; w: number; l: number; oc: string }[];
    /** an array of rectangular area with solid color fills */
    Fills?: any[];
    /** an array of text blocks with position, actual text and styling information */
    Texts?: {
        /** relative coordinates for positioning */
        x?: number;
        /** relative coordinates for positioning */
        y?: number;
        w?: number;
        /** a color index in color dictionary */
        clr?: number;
        sw?: number;
        /** text alignmen */
        A?: string;
        /**  an array of text run, each text run object has two main fields */
        R?: IPDF2JSON_PageR[];
    }[];
}

export interface IPDF2JSON_Metadata {
    [define: string]: string;
}

export interface IPDFJson {
    Transcoder: string;
    Meta: {
        PDFFormatVersion?: string;
        IsAcroFormPresent?: boolean;
        IsXFAPresent?: boolean;
        Author?: string;
        Subject?: string;
        Creator?: string;
        Producer?: string;
        CreationDate?: string;
        ModDate?: string;
        Metadata?: IPDF2JSON_Metadata;
    };
    Pages: IPDF2JSON_Page[];
}
