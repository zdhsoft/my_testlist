import { utils } from 'xmcommon';

export enum EnumOutType {
    CLIENT = 'c',
    SERVER = 's',
}

export enum EnumDataBaseType {
    UNKNOWN = 0,
    BOOL = 1,
    INT = 2,
    NUMBER = 3,
    STRING = 4,
    OBJECT = 5,
    ANY = 6,
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

    public static checkType(paramType: EnumDataBaseType, paramData: any) {
        switch (paramType) {
            case EnumDataBaseType.BOOL:
                return utils.isBoolean(paramData);
            case EnumDataBaseType.INT:
                return utils.isInteger(paramData);
            case EnumDataBaseType.STRING:
                return utils.isString(paramData);
            case EnumDataBaseType.NUMBER:
                return utils.isNumber(paramData);
            case EnumDataBaseType.OBJECT:
                return utils.isObject(paramData);
            case EnumDataBaseType.ANY:
                return true;
            default:
                return false;
        }
    }

    public static baseType(paramType: EnumDataType): EnumDataBaseType {
        if (this.isAny(paramType)) {
            return EnumDataBaseType.ANY;
        } else if (this.isBool(paramType)) {
            return EnumDataBaseType.BOOL;
        } else if (this.isInt(paramType)) {
            return EnumDataBaseType.INT;
        } else if (this.isString(paramType)) {
            return EnumDataBaseType.STRING;
        } else if (this.isNumber(paramType)) {
            return EnumDataBaseType.NUMBER;
        } else if (this.isObject(paramType)) {
            return EnumDataBaseType.OBJECT;
        }
        return EnumDataBaseType.UNKNOWN;
    }
}

/** 通用正则表达式 */
export const CommonReg = {
    /** YYYY-MM-DD hh:mm:ss 格式的正则表达式 */
    dateTime: /^[1-2]\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\d):[0-5]\d:[0-5]\d$/,
    /** 货币类正则表达式 */
    curreny: /^[-+]?\d+(?:\.\d{0,4})?$/,
    /** 货币千分位 */
    curreny_thousandth: /^[-+]?\d{1,3}(,\d{3})*(\.\d{0,4})?$/,
    /** YYYY-MM-DD 支持 . - / \ 空格分隔符 格式 */
    baseDate: /^([1-3]\d{3})[./\-\\\ ](0[1-9]|1[0-2])[./\-\\\ ](0[1-9]|[1-2][0-9]|3[0-1])$/,
    /** 范围日期 */
    baseRangeDate:
        /^([1-2]\d{3})[./\-\\\ ](0[1-9]|1[0-2])[./\-\\\ ](0[1-9]|[1-2][0-9]|3[0-1]) ([1-2]\d{3})[./\-\\\ ](0[1-9]|1[0-2])[./\-\\\ ](0[1-9]|[1-2][0-9]|3[0-1])$/,
    /** YYYY-MM-DD 格式的日期正则表达式 */
    simpleDate: /^([1-2]\d{3})(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])$/,
    /** hh:mm:ss的正则表达式 */
    baseTime: /^([0-1]\d{1}|2[0-3]):([0-5]\d{1}):([0-5]\d{1})$/,
    /** hhmmss的正则表达式 */
    simpleTime: /^([0-1]\d{1}|2[0-3])([0-5]\d{1})([0-5]\d{1})$/,
    /** 仅数字 */
    onlyDigit: /^\d+$/,
    /** 仅小写字母 */
    onlyLowercase: /^[a-z]+$/,
    /** 仅大写字母 */
    onlyCapitalLetter: /^[A-Z]+$/,
    /** 仅大小写字母 */
    onlyLetter: /^[A-Za-z]+$/,
    /** 数字与大小写字母 */
    digitOrLetter: /^[A-Za-z0-9]+$/,
    /** 15位身份证 */
    idNumber15: /^([1-6][1-9]|50)\d{4}\d{2}((0[1-9])|10|11|12)(([0-2][1-9])|10|20|30|31)\d{3}$/,
    /** 18位身份证 */
    idNumber18: /^([1-6][1-9]|50)\d{4}(18|19|20)\d{2}((0[1-9])|10|11|12)(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$/,
    /** email地址 */
    email: /^\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/,
    /** ascii字符 */
    ascii: /^[\x00-\x7F]+$/,
    /** 字母是大写的16进制 */
    uppercaseHEX: /^[A-F0-9]+$/,
    /** 字母是小写的16进制 */
    lowercaseHEX: /^[a-f0-9]+$/,
    /** url */
    url: /^(?=^.{3,255}$)(http(s)?:\/\/)?(www\.)?[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+(:\d+)*(\/\w+\.\w+)*([\?&]\w+=\w*)*$/,
    /** 整数 */
    integer: /^((0{1})|(-{0,1}[1-9]\d*))$/,
    /** 数字 */
    decimal: /^-?([1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0)$/,
    /** 中国手机号 xxxxxxxxxxx */
    mobile_cn_none: /^(\+?0?86\-?)?(1\d{10})$/,
    /** 中国手机号 xxx-xxxx-xxxx */
    mobile_cn_344: /^(\+?0?86\-?)?(1\d{2})-(\d{4})-(\d{4})$/,
    /** 中国手机号 xxx-xxx-xxxxx */
    mobile_cn_335: /^(\+?0?86\-?)?(1\d{2})-(\d{3})-(\d{5})$/,
    /** 中国手机号 xxxx-xxxx-xxx */
    mobile_cn_443: /^(\+?0?86\-?)?(1\d{3})-(\d{4})-(\d{3})$/,
    /** 国外手机号 */
    mobile_other: /^([\+\-\d\.]{2,20})$/,
};
