function f(key: string): any {
    console.log('evaluate: ', key);
    return function () {
        console.log('call: ', key);
    };
}

/** FlowId装饰器  增加一个静态类属性 */
export function FLOW(paramFlowId: string) {
    // function classDecorator<T extends {new(...args:any[]):{}}>(constructor:T)
    // 上面注释是原型
    // eslint-disable-next-line @typescript-eslint/ban-types
    function classDecorator<T extends new (...args: any[]) => {}>(base: T) {
        return class extends base {
            public static FlowId = paramFlowId;
            public constructor(...args: any[]) {
                super(...args);
                base.prototype.getFlowId = () => paramFlowId;
            }
        };
    }
    return classDecorator;
}
/** 增加一个静态方法和创建方法 */
function moreInfo(name: string) {
    // eslint-disable-next-line @typescript-eslint/ban-types
    return <T extends new (...args: any[]) => {}>(base: T) => {
        return class A extends base {
            public constructor(...args: any[]) {
                super(...args);
            }
            public static getName() {
                return name;
            }

            public static createSelf(...args: any[]) {
                return new A(...args);
            }
        };
    };
}

export class SimpleClass {
    public constructor() {
        //
    }
}
interface IGirl {
    faceValue(): void;
}

// 女孩子
@f('Girl')
@moreInfo('Girl')
class Girl implements IGirl {
    public faceValue() {
        console.log('我原本的脸');
    }
}
@f('ThinFace')
@moreInfo('ThinFace')
class ThinFace implements IGirl {
    constructor(private girl: IGirl) {
        //
    }
    public faceValue() {
        this.girl?.faceValue();
        console.log('开启瘦脸');
    }
}
@f('IncreasingEyes')
@moreInfo('IncreasingEyes')
class IncreasingEyes implements IGirl {
    constructor(private girl: IGirl) {
        //
    }
    public faceValue() {
        this.girl?.faceValue();
        console.log('增大眼睛');
    }
}

export function testClass() {
    let girl: IGirl = new Girl();

    girl = new ThinFace(girl);
    girl = new IncreasingEyes(girl);

    // 闪瞎你的眼
    girl.faceValue(); //

    const a: IGirl = (Girl as any).createSelf();
    const b: IGirl = (ThinFace as any).createSelf(a);
    const c: IGirl = (IncreasingEyes as any).createSelf(b);

    console.log('----------CCCCCCCCCCCCCCCCCCCCCCCCCc------');

    c.faceValue();
    console.log('----------xxxxxxxxxxxxxx------');
    const nnn: { (...args: any[]): IGirl }[] = [];
    nnn.push((Girl as any).createSelf);
    nnn.push((ThinFace as any).createSelf);
    nnn.push((IncreasingEyes as any).createSelf);
    let k: IGirl = a;
    for (const create of nnn) {
        k = create(k);
    }
    k.faceValue();
    // console.log((Girl as any).createSelf().faceValue());
    // console.log((ThinFace as any).createSelf().faceValue());
    // console.log((IncreasingEyes as any).createSelf().faceValue());
}
