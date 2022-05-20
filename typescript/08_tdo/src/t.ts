import { getLogger } from 'xmcommon';

const log = getLogger(__filename);
export class T {
    private m_a = 100;
    private m_bbb = '999';
    private m_k = new Date();

    public constructor() {
        //
    }

    /** 属性说明 */
    public get a(): number {
        return this.m_a;
    }
    public set a(parama: number) {
        this.m_a = parama;
    }

    public get k() {
        return this.m_k;
    }

    /** 属性说明 */
    public get bbb(): string {
        return this.m_bbb;
    }
    public set bbb(parambbb: string) {
        log.info('set bbb:' + parambbb);
        this.m_bbb = parambbb;
    }

    public toJSON() {
        return {
            a: this.a,
            bbb: this.bbb,
            k: this.k,
            bool: true,
            boolf: false,
            v: ['a', 'b'],
            mm: { a: 1, b: 2 },
            c: 99.99,
        };
    }
}
