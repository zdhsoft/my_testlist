export enum EnumOutType {
    CLIENT = 'c',
    SERVER = 's',
}

export enum EnumDataType {
    ANY = 'any',
    BOOL = 'bool',
    INT = 'int',
    NUMBER = 'number',
    STRING = 'string',
    OBJECT = 'object',

    ARRAY_ANY = 'array:any',
    ARRAY_BOOL = 'array:bool',
    ARRAY_INT = 'array:int',
    ARRAY_NUMBER = 'array:number',
    ARRAY_STRING = 'array:string',
    ARRAY_OBJECT = 'array:object',
}

const TypeSet = {
    SetTypeAny: new Set<EnumDataType>(),
    SetTypeBool: new Set<EnumDataType>(),
    SetTypeInt: new Set<EnumDataType>(),
    SetTypeNumber: new Set<EnumDataType>(),
    SetTypeString: new Set<EnumDataType>(),
    SetTypeObject: new Set<EnumDataType>(),
    SetTypeArray: new Set<EnumDataType>(),
};

TypeSet.SetTypeAny.add(EnumDataType.ANY).add(EnumDataType.ARRAY_ANY);
TypeSet.SetTypeBool.add(EnumDataType.BOOL).add(EnumDataType.ARRAY_BOOL);
TypeSet.SetTypeInt.add(EnumDataType.INT).add(EnumDataType.ARRAY_INT);
TypeSet.SetTypeNumber.add(EnumDataType.NUMBER).add(EnumDataType.ARRAY_NUMBER);
TypeSet.SetTypeString.add(EnumDataType.STRING).add(EnumDataType.ARRAY_STRING);
TypeSet.SetTypeObject.add(EnumDataType.OBJECT).add(EnumDataType.ARRAY_OBJECT);
TypeSet.SetTypeArray.add(EnumDataType.ARRAY_ANY)
    .add(EnumDataType.ARRAY_BOOL)
    .add(EnumDataType.ARRAY_INT)
    .add(EnumDataType.ARRAY_NUMBER)
    .add(EnumDataType.ARRAY_STRING)
    .add(EnumDataType.ARRAY_OBJECT);

export class XTypeUtils {
    public static isAny(paramType: EnumDataType) {
        return TypeSet.SetTypeAny.has(paramType);
    }
    public static isBool(paramType: EnumDataType) {
        return TypeSet.SetTypeBool.has(paramType);
    }
    public static isInt(paramType: EnumDataType) {
        return TypeSet.SetTypeInt.has(paramType);
    }
    public static isNumber(paramType: EnumDataType) {
        return TypeSet.SetTypeNumber.has(paramType);
    }
    public static isString(paramType: EnumDataType) {
        return TypeSet.SetTypeString.has(paramType);
    }
    public static isObject(paramType: EnumDataType) {
        return TypeSet.SetTypeObject.has(paramType);
    }
    public static isArray(paramType: EnumDataType) {
        return TypeSet.SetTypeArray.has(paramType);
    }
}
