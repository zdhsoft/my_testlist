const SINGLETON_KEY = Symbol();

const m: any[] = [];

type SingletonX<T extends new (...args: any[]) => any> = T & {
    [SINGLETON_KEY]: T extends new (...args: any[]) => infer I ? I : never;
};

export function Singleton<T extends new (...args: any[]) => any>(type: T): T {
    console.log('-------------》》》');
    const a = new Proxy(type, {
        // this will hijack the constructor
        construct(target: SingletonX<T>, argsList, newTarget) {
            console.log('-------------');
            // we should skip the proxy for children of our target class
            if (target.prototype !== newTarget.prototype) {
                return Reflect.construct(target, argsList, newTarget);
            }
            // if our target class does not have an instance, create it
            if (!target[SINGLETON_KEY]) {
                target[SINGLETON_KEY] = Reflect.construct(target, argsList, newTarget);
            }
            // return the instance we created!
            return target[SINGLETON_KEY];
        },
    });
    const mm = new a();
    m.push(mm);
    return a;
}

export function initMaster() {
    for (const f of m) {
        const r = f.init();
        console.log(JSON.stringify(r));
    }
}
