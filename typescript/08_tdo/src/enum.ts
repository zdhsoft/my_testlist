enum EnumA {
    a = 1,
    b = 2,
    c = 3,
    d = 4,
}
enum EnumB {
    aa = 'a',
    bb = 'b',
    cc = 'c',
    dd = 'd',
}

/** 取枚举key列表 */
function getEnumKeys(paramEnum: object) {
    return Object.keys(paramEnum).filter((paramK) => isNaN(Number(paramK)));
}
/** 取枚举值列表 */
function getEnumValues<T = any>(paramEnum: object) {
    const keys = getEnumKeys(paramEnum);
    return keys.map((paramK) => (paramEnum as any)[paramK]) as T[];
}

const keys2 = Object.keys(EnumA).filter((v) => isNaN(Number(v)));
console.log(keys2);
const keys3 = Object.keys(EnumB).filter((v) => isNaN(Number(v)));
console.log(Object.keys(EnumB), '\n', keys3);

console.log('-----+++++', getEnumValues<EnumA>(EnumA));
console.log('----------', getEnumValues<EnumB>(EnumB));
