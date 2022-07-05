import * as _ from 'lodash';
import { utils, XCommonRet } from 'xmcommon';
const SINGLETON_KEY = Symbol();

const masterList: any[] = [];
type Singleton<T extends new (...args: any[]) => any> = T & {
    [SINGLETON_KEY]: T extends new (...args: any[]) => infer I ? I : never;
};

export function MASTER<T extends new (...args: any[]) => any>(type: T): T {
    const MasterProxy = new Proxy(type, {
        construct(target: Singleton<T>, argsList, newTarget) {
            if (target.prototype !== newTarget.prototype) {
                return Reflect.construct(target, argsList, newTarget);
            }
            if (!target[SINGLETON_KEY]) {
                target[SINGLETON_KEY] = Reflect.construct(target, argsList, newTarget);
            }
            return target[SINGLETON_KEY];
        },
    });
    masterList.push(new MasterProxy());
    return MasterProxy;
}

export function initMaster() {
    for (const f of masterList) {
        if (_.isFunction(f.init)) {
            const r = f.init();
            if (r instanceof XCommonRet) {
                if (r.isNotOK) {
                    console.log('----------' + JSON.stringify(r));
                    process.exit(-1);
                }
            } else if (utils.isNotNull(r)) {
                console.log('-----' + r);
            }
        }
        console.log(JSON.stringify(r));
    }
}
