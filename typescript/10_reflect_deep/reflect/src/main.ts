import 'reflect-metadata';
import { getLogger } from 'xmcommon';
import { testOpt } from './opt';
const log = getLogger(__filename);

export const CONTROLLER_METADATA = 'controller';
export const ROUTE_METADATA = 'method';
export const PARAM_METADATA = 'param';

export type Param = 'params' | 'query' | 'body' | 'headers' | 'cookies';
export type HttpMethod = 'get' | 'post' | 'put' | 'delete' | 'patch';

export function Controller(path = ''): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata(CONTROLLER_METADATA, path, target);
    };
}

@Controller('/a')
class a {
    //
    getName() {
        return 'a';
    }
}
@Controller('/b')
class b {
    //
    setName() {
        return 'setName';
    }
}

// export function createMethodDecorator(method: HttpMethod = 'get') {
//     return (path = '/'): MethodDecorator =>
//         (target: object, name: string, descriptor: any) => {
//             Reflect.defineMetadata(
//                 ROUTE_METADATA,
//                 { type: method, path },
//                 descriptor.value,
//             );
//         };
// }

// export function createParamDecorator(type: Param) {
//     return (key?: string): ParameterDecorator =>
//         (target: object, name: string, index: number) => {
//             // 这里要注意这里 defineMetadata 挂在 target.name 上
//             // 但该函数的参数有顺序之分，下一个装饰器定义参数后覆盖之前的，所以要用 preMetadata 保存起来
//             const preMetadata =
//                 Reflect.getMetadata(PARAM_METADATA, target, name) || [];
//             const newMetadata = [{ key, index, type }, ...preMetadata];

//             Reflect.defineMetadata(PARAM_METADATA, newMetadata, target, name);
//         };
// }

class m {
    private k = 100;
    public getName() {
        return 'm';
    }
    public setName(paramJ: number) {
        this.k = paramJ;
    }
    public calc() {
        return this.k * 10;
    }
}

function test() {
    //
    const controllerMetadata: string = Reflect.getMetadata(
        CONTROLLER_METADATA,
        m,
    );
    console.log(JSON.stringify(controllerMetadata, null, 2));
    const mmm = Object.getOwnPropertyNames(m);
    log.info('mmm', mmm);
    const jjj = Reflect.getMetadataKeys(m);
    log.info('jjj', jjj);
    const proto: any = m.prototype; //Reflect.getPrototypeOf(m);

    log.info('getOwnPropertyNames', Object.getOwnPropertyNames(m.prototype));
    log.info('ownKeys', Reflect.ownKeys(m));
    const allNameList = Object.getOwnPropertyNames(proto); // Object.getOwnPropertyNames(proto);
    // const routeNameArr: string[] = [];
    for (const name of allNameList) {
        log.info('--->' + name);
        log.info('    **' + typeof proto[name]);
    }

    //log.info(JSON.stringify(routeNameArr));
}

function main() {
    // test();
    testOpt();
}
main();
