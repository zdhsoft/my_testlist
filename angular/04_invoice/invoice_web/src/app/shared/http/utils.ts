import * as md5 from "js-md5";

export const requestSign = () => {
  const time = Math.floor(new Date().getTime() / 1000);
  const appId = sessionStorage.getItem('appId');
  const clientkey = sessionStorage.getItem('clientkey');
  const userId = sessionStorage.getItem('userId');

  return {
    t: time,
    sign: md5(`${appId}${clientkey}${time}${userId}`),
  };
}

/** a_b_c -> aBC */
export const toCamelCase = (name: string) => {
  return name.replace(/\_(\w)/g, (str, letter) => letter.toUpperCase());
}

/** aBC -> a_b_c */
export const toSnakeCase = (name: string) => {
  return name.replace(/([A-Z])/g, (str, letter) => `_${letter}`).toLowerCase();
}

const checkParams = (obj: any) => {
  const isObj = typeof obj === 'object' && !Array.isArray(obj);
  const isArr = Array.isArray(obj);
  const isNumber = typeof obj === 'number';
  const isString = typeof obj === 'string';

  if (!isObj && !isArr && !isNumber && !isString) {
    throw new Error();
  }

  return {isObj, isArr};
}

export const resToCamelCase = (obj: any) => {
  if (!obj) { return obj }

  const {isObj, isArr} = checkParams(obj);

  let result = isObj && isArr ? ([] as any) : ({} as any);

  if (isObj) {
    for (const key in obj) {
      if (obj.hasOwnProperty(key)) {

        if (typeof obj[key] === 'object') {
          obj[key] = resToCamelCase(obj[key]);
        }

        result[toCamelCase(key)] = obj[key];
      }
    }
  }

  if (isArr) {
    result = obj.reduce((prev: any[], curr: any) => {
      if (typeof curr === 'object') {
        return prev.concat(resToCamelCase(curr));
      }
      return prev.concat(curr);
    }, [])
  }

  return result;
}

export const reqToSnakeCase = (obj: any) => {
  if (obj instanceof FormData) {
    return obj;
  }

  if (!obj) { return obj }

  const {isObj, isArr} = checkParams(obj);

  let result = isObj && isArr ? ([] as any) : ({} as any);

  if (isObj) {
    for (const key in obj) {
      if (obj.hasOwnProperty(key)) {

        if (typeof obj[key] === 'object') {
          obj[key] = reqToSnakeCase(obj[key]);
        }

        result[toSnakeCase(key)] = obj[key];
      }
    }
  }

  if (isArr) {
    result = obj.reduce((prev: any[], curr: any) => {
      if (typeof curr === 'object') {
        return prev.concat(reqToSnakeCase(curr));
      }
      return prev.concat(curr);
    }, [])
  }

  return result;
}
