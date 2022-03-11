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

function classFactory<T>(_constructor: { new(...args: Array<any>): T }): T {

    const paramTypes: Array<any> = Reflect.getMetadata(EnumMD.paramTypes, _constructor);
    const OOO: object = {};
    const _oo = Object.getPrototypeOf(OOO);
    const args: object[] = [];
    for(const p of paramTypes) {
        let found = false;
        const _op = p.prototype;
        for (const s of serviceList) {
            const _os = Object.getPrototypeOf(s);

            if (_op === _os) {
                args.push(s);
                found = true;
                break;
            }
        }

        if(!found) {
            if(_oo === _op) {
                console.log("------", p.toString());
                args.push(p)
            } else {
                console.log('... not found!');
            }
        }
    }

    const result = new _constructor(...args);
    return result;
}

export function Injectable(paramOpts: any = {}): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata(EnumMD.injectable, paramOpts , target);
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

    public getName() {
        return 'hahahahaha';
    }
}
@Controller('/')
class XTestController {
    constructor(private readonly chatService: XChatService, private readonly testService: XTestService) {
        console.log('XTestController:chatService', chatService.getName());
        console.log('XTestController:testService', testService.getName());
    }
}

@Controller('/kkk')
class XKKKController {
    constructor(private readonly chatService: XChatService) {
        console.log('XKKKController:chatService', chatService.getName());
    }
}
@Module({
    service:[XChatService, XTestService],
    controller:[XTestController, XKKKController]
})
class AppModule {
    //
}

function init(appModule: object) {
    const v = Reflect.getMetadata(EnumMD.module, appModule) as IModelOptions;
    console.log(JSON.stringify(v));
    v.service?.forEach((s) => {
        const r = classFactory(s);
        serviceList.push(r);
    });

    v.controller?.forEach((s)=>{
        const r = classFactory(s);
        serviceList.push(r);
        const path = Reflect.getMetadata(EnumMD.controller,s);
        console.log('----path:' + path);
    });
}

function main() {
    init(AppModule);
}

main();
