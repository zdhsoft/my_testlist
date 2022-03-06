interface IBase {
    result: number;
}

const m = new Map<string, { (a: number, b: number): IBase }>();
const s = new Map<string, { (a: number, b: number): IBase }>();

// declare type ClassDecorator = <TFunction extends Function>(target: TFunction) => TFunction | void;
// declare type PropertyDecorator = (target: Object, propertyKey: string | symbol) => void;
// declare type MethodDecorator = <T>(target: Object, propertyKey: string | symbol, descriptor: TypedPropertyDescriptor<T>) => TypedPropertyDescriptor<T> | void;
// declare type ParameterDecorator = (target: Object, propertyKey: string | symbol, parameterIndex: number) => void;

class K(paramKey: string): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata(SCOPE_OPTIONS_METADATA, options, target);
      };
}

// 这个装饰器为类增加了key和create方法
function M(paramKey: string) {
    console.log('-------------------->' + paramKey);
    // eslint-disable-next-line @typescript-eslint/ban-types
    return <T extends { new (...args: any[]): IBase }>(base: T) => {
        console.log('==================>' + paramKey);
        class A extends base {
            constructor(...args: any[]) {
                super(...args);
                console.log('**************************' + paramKey);
            }
            public static get key() {
                return paramKey;
            }
            public static create(a: number, b: number): A {
                return new A(a, b);
            }
        }

        if (m.has(paramKey)) {
            throw Error('已经存在一个Key=' + paramKey + '定义!');
        }

        m.set(paramKey, A.create);
        return A;
    };
}
// 这个装饰器仅是将创建函数放到了map中
function S(paramKey: string) {
    if (s.has(paramKey)) {
        throw Error('已经存在一个Key=' + paramKey + '定义!');
    }
    // eslint-disable-next-line @typescript-eslint/ban-types
    return <T extends { new (...args: any[]): IBase }>(base: T) => {
        const f = (a: number, b: number) => {
            return new base(a, b);
        };

        s.set(paramKey, f);
        return base;
    };
}

@M('a1')
@S('aaaaaa1')
class a1 {
    private m_r: number;
    constructor(a: number, b: number) {
        this.m_r = a + b;
    }

    get result() {
        return this.m_r;
    }
}

@M('a2')
@S('aaaaaa2')
class a2 {
    private m_r: number;
    constructor(a: number, b: number) {
        this.m_r = a * b;
    }
    get result() {
        return this.m_r;
    }
}

@M('a3')
@S('aaaaaa3')
class a3 {
    private m_r: number;
    constructor(a: number, b: number) {
        this.m_r = a - b;
    }
    get result() {
        return this.m_r;
    }
}

export function testAAA() {
    m.forEach((c) => {
        const v = c(1, 2);
        console.log(1, 2, '=>', v.result);
    });

    s.forEach((c) => {
        const v = c(4, 5);
        console.log(4, 5, '=>', v.result);
    });
}
