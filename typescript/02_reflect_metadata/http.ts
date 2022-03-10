/* eslint-disable @typescript-eslint/no-explicit-any */
import 'reflect-metadata';

enum EnumMD {
    type = 'design:type',
    paramTypes = 'design:paramtypes',
    returnType = 'design:returntype',
    injectable = '__injectable__',
    module = '__module__',
    controller = '__controller__',
}

const serviceList: any[] = [];
const controllerList: any[] = [];

// function classFactory<T>(_constructor: { new(...args: Array<any>): T }): T {
//     let paramTypes: Array<Function> = Reflect.getMetadata('design:paramtypes', _constructor);
//     //参数实例化
//     let paramInstance = paramTypes.map((val: Function) => {
//         //依赖的类必须全部进行注册
//         if (IOC.classContainer.indexOf(val) == -1) throw new Error(`${val}没有被注册`)
//         //参数还有依赖
//         else if (val.length) {
//             return this.classFactory(val as any);
//         }
//         //没有依赖直接创建实例
//         else {
//             return new (val as any)();
//         }
//     });
//     let autolist: Array<AutoBuildInfo> = (_constructor as Function).prototype.$$ejectprop;
//     let result = new _constructor(...paramInstance);
//     if (autolist && autolist.length > 0) {
//         for (let item of autolist) {
//             result[item.keyName] = this.classFactory(item.keyType as any);
//         }
//         Reflect.deleteProperty(result.constructor.prototype, '$$ejectprop');
//     }
//     return result
// }

export function Injectable(paramOpts: any = {}): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata(EnumMD.injectable, paramOpts , target);
        Reflect.defineMetadata(EnumMD.type, target, target);
    };
}

interface IModelOptions {
    service?: any[];
    controller?: any[];
}

export function Module(paramOpts: IModelOptions) {
    return (target: object) => {
        Reflect.defineMetadata(EnumMD.module, paramOpts, target);
    }
}

export function Controller(paramPath?: string) {
    return (target: object) => {
        Reflect.defineMetadata(EnumMD.controller, paramPath, target);
    }
}

@Injectable()
class XChatService {
    constructor() {
        //
        console.log('XChatService create');
    }
    public getName() {
        return 'name';
    }
}
@Injectable()
class XTestService {
    constructor() {
        //
        console.log('XTestService create');
    }
}
@Controller('/')
class XTestController {
    constructor(private readonly chatService: XChatService, private readonly testService: XTestService) {
        //
    }
}

@Module({
    service:[XChatService, XTestService],
    controller:[XTestController]
})
class AppModule {
    //
}

function init(appModule: object) {
    const v = Reflect.getMetadata(EnumMD.module, appModule) as IModelOptions;
    console.log(JSON.stringify(v));
    v.service?.forEach((s) => {
        const opts = Reflect.getMetadata(EnumMD.injectable, s);
        const type = Reflect.getMetadata(EnumMD.type, s);
        // const param = Reflect.getMetadata(EnumMD.paramTypes, s);
        // const ret = Reflect.getMetadata(EnumMD.returnType, s);
        if (typeof type === 'function') {
            const serviceObj = new type();
            Object.setPrototypeOf(serviceObj, type);
            serviceList.push(serviceObj);
        }
        console.log('service:****', JSON.stringify(opts))
    });

    v.controller?.forEach((s) => {
        const i = Reflect.getMetadata(EnumMD.controller, s);
        const m: object[] = Reflect.getMetadata(EnumMD.paramTypes, s);
        const type = Reflect.metadata(EnumMD.type, s);
        const params: any[] = [];
        m.forEach((p)=>{
            let found = false;
            for (const pp of serviceList) {
                const ppp = Object.getPrototypeOf(pp);
                if (p === ppp) {
                    found = true;
                    params.push(pp);
                    break;
                }
            }
            if(!found) {
                params.push(null);
            }
        });
        const c = new type(...params);
        controllerList.push(c);
        console.log('controller:****', JSON.stringify(i), JSON.stringify(m));
    });

}

function main() {
    init(AppModule);
}

main();
