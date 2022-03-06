export const CONTROLLER_METADATA = 'controller';
export const ROUTE_METADATA = 'method';
export const PARAM_METADATA = 'param';

export type HttpMethod = 'get' | 'post' | 'put' | 'delete' | 'patch';
export type Param = 'params' | 'query' | 'body' | 'headers' | 'cookies';
export type Parse = 'number' | 'string' | 'boolean';

export function Controller(path = ''): ClassDecorator {
    return (target: object) => {
        Reflect.defineMetadata(CONTROLLER_METADATA, path, target);
    };
}

// declare type MethodDecorator = <T>(target: Object, propertyKey: string | symbol, descriptor: TypedPropertyDescriptor<T>) => TypedPropertyDescriptor<T> | void;
// declare type ParameterDecorator = (target: Object, propertyKey: string | symbol, parameterIndex: number) => void;
export function createMethodDecorator(method: HttpMethod = 'get') {
    return (path = '/'): MethodDecorator =>
        (target: object, propertyKey: string | symbol, descriptor: any) => {
            Reflect.defineMetadata(ROUTE_METADATA, { type: method, path }, descriptor.value);
        };
}

export function createParamDecorator(type: Param) {
    return (key?: string): ParameterDecorator =>
        (target: object, name: string | symbol, index: number) => {
            // 这里要注意这里 defineMetadata 挂在 target.name 上
            // 但该函数的参数有顺序之分，下一个装饰器定义参数后覆盖之前的，所以要用 preMetadata 保存起来
            const preMetadata = Reflect.getMetadata(PARAM_METADATA, target, name) || [];
            const newMetadata = [{ key, index, type }, ...preMetadata];

            Reflect.defineMetadata(PARAM_METADATA, newMetadata, target, name);
        };
}
