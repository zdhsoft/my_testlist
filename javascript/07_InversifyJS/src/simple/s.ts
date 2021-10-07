import { injectable } from "../inversify";

@injectable()
export class x {
    private m_a: number  = 100;

    public getA(): number {
        return this.m_a;
    }
    public setA(paramA: number): void {
        this.m_a = paramA;
    }
}
