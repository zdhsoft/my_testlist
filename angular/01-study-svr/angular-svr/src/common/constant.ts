import session from 'express-session';

/** URL 前缀 */
export const urlPrefix = {
    /** 所有需要拦载的api前缀 */
    API: '/api/',
    /** 本地调用的api，这里不需要做用户登录验证 */
    LOCAL_API: '/api/local/',
    /** 需要检查的api */
    CHECK_API: '/api/fun/',
};

export enum EnumErrType {
    OK = 0,
    Error = -1,
    NeedAdmin = 1, // 需要管理员
    NeedLogin = 2, // 登录
    RegisterFail = 3, // 注册失败
    AccountList = 4, // 用户列表
    ChangePassword = 5, // 修改密码
    ChangeInfo = 6, // 修改信息，名称和email
}
export interface XSessionError {
    type: EnumErrType;
    account?: string;
    errorMsg?: string;
    name?: string;
    email?: string;
}

export interface XSessionUser {
    id?: number;
    account?: string;
    name?: string;
    email?: string;
    ip?: string;
    login_time?: Date;
    env?: string;
}

export interface XSession extends session.Session {
    error?: XSessionError;
    isLogin?: boolean;
    user?: XSessionUser;
}

export const GlobalConst = {
    admin: 'admin',
};
