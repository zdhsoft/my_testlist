export class XUtils {
  public static isNull(paramValue: unknown | null | undefined) {
    return paramValue === undefined || paramValue === null;
  }

  public static isNotNull(paramValue: undefined | null | unknown) {
    return !this.isNull(paramValue);
  }
}
