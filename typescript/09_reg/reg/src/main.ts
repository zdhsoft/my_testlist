/*************************************************************************
 * Copyright(c) 2017-2022,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2022-02-07
 *************************************************************************/

import { CommonReg } from './reg';

function t(paramReg: RegExp, paramValue: string, paramPrompt = '') {
    const execResult = paramReg.exec(paramValue);
    const testResult = paramReg.test(paramValue);
    console.log(
        `${paramPrompt} ${paramValue}=>${paramReg}=>${testResult}, ${JSON.stringify(
            execResult,
        )}`,
    );
}
console.log('hello world!');
t(CommonReg.baseDate, '2009-02-01');
t(CommonReg.baseDate, '2009/02/01');
t(CommonReg.baseDate, '2009\\02\\01');
t(CommonReg.baseDate, '2009.02.01');
t(CommonReg.baseDate, '2009 02 01');
t(CommonReg.simpleDate, '20090201');
t(CommonReg.baseTime, '20:19:23');
t(CommonReg.baseTime, '24:19:23');
t(CommonReg.baseTime, '00:00:00');
t(CommonReg.simpleTime, '010203');