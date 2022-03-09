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
        console.log('hello');
    }
    public getName() {
        return 'name';
    }

}
@Controller('/')
class XTestController {
    constructor(private readonly chatService: XChatService) {
        //
    }
}

@Module({
    service:[XChatService],
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
            serviceList.push(serviceObj);
        }
        console.log('service:****', JSON.stringify(opts))


    });

    v.controller?.forEach((s) => {
        const i = Reflect.getMetadata(EnumMD.controller, s);

        console.log('controller:****', JSON.stringify(i))
    });

}

function main() {
    init(AppModule);
}

main();
