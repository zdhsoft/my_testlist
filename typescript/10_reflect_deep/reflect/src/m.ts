export interface Type<T = any> extends Function {
    new (...args: any[]): T;
}
export interface ModuleMetadata {
    controllers?: Type<any>[];
}

export function Module(metadata: ModuleMetadata): ClassDecorator {
    // const propsKeys = Object.keys(metadata);
    // validate_module_keys_util_1.validateModuleKeys(propsKeys);
    return (target) => {
        for (const property in metadata) {
            if (metadata.hasOwnProperty(property)) {
                Reflect.defineMetadata(
                    property,
                    (metadata as any)[property],
                    target,
                );
            }
        }
    };
}
