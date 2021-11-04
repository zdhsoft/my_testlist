import 'reflect-metadata';

export const HTTP_CODE_METADATA = '__httpCode__';

function HttpCode(statusCode: number): MethodDecorator {
    return (
        target: object,
        key: string | symbol,
        descriptor: TypedPropertyDescriptor<any>,
    ) => {
        Reflect.defineMetadata(HTTP_CODE_METADATA, statusCode, descriptor.value);
        return descriptor;
    };
}


class aaa {
    @HttpCode(200)
    public callWithClientUseFactory(): number {
        return 100;
    }
    @HttpCode(345)
    public static mmm(): number {
        return 999;
    }
}

const b = new aaa();
const code = Reflect.getMetadata(HTTP_CODE_METADATA, b.callWithClientUseFactory);
console.log(code);
const ccc = Reflect.getMetadata(HTTP_CODE_METADATA, aaa.mmm);
console.log(ccc);
b.callWithClientUseFactory();
