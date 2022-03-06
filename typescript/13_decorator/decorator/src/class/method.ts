// eslint-disable-next-line @typescript-eslint/no-empty-interface
interface IBase {
    //
}

// eslint-disable-next-line @typescript-eslint/ban-types
const s = new Map<string, { create: (...args: any[]) => {}; proto: object | null }>();

// 这个装饰器仅是将创建函数放到了map中
function S(paramKey: string) {
    if (s.has(paramKey)) {
        throw Error('已经存在一个Key=' + paramKey + '定义!');
    }
    // eslint-disable-next-line @typescript-eslint/ban-types
    return <T extends { new (...args: any[]): IBase }>(base: T) => {
        const f = (...args: any[]) => {
            return new base(...args);
        };
        s.set(paramKey, { create: f, proto: base.prototype });
        return base;
    };
}
@S('hello')
class A {
    public a() {
        return 100;
    }
}
@S('B')
class B {
    public b() {
        return 100;
    }
}
export function testMethod() {
    s.forEach((v, k) => {
        console.log(k, v.proto === A.prototype);
    });
}
