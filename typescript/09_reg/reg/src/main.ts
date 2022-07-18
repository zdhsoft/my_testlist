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
        `${paramPrompt} [${paramValue}] => [${paramReg}] => ${testResult}, ${JSON.stringify(
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
t(CommonReg.onlyDigit, '123');
t(CommonReg.onlyDigit, '123aa');
t(CommonReg.onlyDigit, '');
console.log(
    'onlyLowercase-------------------------------------------------------',
);
t(CommonReg.onlyLowercase, 'abc');
t(CommonReg.onlyLowercase, '123aa');
t(CommonReg.onlyLowercase, '');
t(CommonReg.onlyLowercase, 'aA');
console.log(
    'onlyCapitalLetter-------------------------------------------------------',
);
t(CommonReg.onlyCapitalLetter, 'ABC');
t(CommonReg.onlyCapitalLetter, 'ABC123');
t(CommonReg.onlyCapitalLetter, '');
t(CommonReg.onlyCapitalLetter, 'aA');
console.log('integer-------------------------------------------------------');
t(CommonReg.integer, '0');
t(CommonReg.integer, '-0');
t(CommonReg.integer, '123450');
t(CommonReg.integer, '+12345');
t(CommonReg.integer, '');
t(CommonReg.integer, '-1234560');
t(CommonReg.integer, '012345');
console.log('mobile_cn-------------------------------------------------------');
t(CommonReg.mobile_cn, '01234511111');
t(CommonReg.mobile_cn, '012345111112');
t(CommonReg.mobile_cn, '');
t(CommonReg.mobile_cn, '18820248184');
t(CommonReg.mobile_cn, '+8618820248184');
t(CommonReg.mobile_cn, '8618820248184');
t(CommonReg.mobile_cn, '86-18820248184');
t(CommonReg.mobile_cn, '086-18820248184');
t(CommonReg.mobile_cn, '+86-18820248184');
t(CommonReg.mobile_cn, '+8818820248184');
console.log(
    'mobile_other-------------------------------------------------------',
);
t(CommonReg.mobile_other, '01234511111');
t(CommonReg.mobile_other, '012345111112');
t(CommonReg.mobile_other, '');
t(CommonReg.mobile_other, '18820248184');
t(CommonReg.mobile_other, '+8618820248184');
t(CommonReg.mobile_other, '8618820248184');
t(CommonReg.mobile_other, '86-18820248184');
t(CommonReg.mobile_other, '086-18820248184');
t(CommonReg.mobile_other, '+86-18820248184');
t(CommonReg.mobile_other, '+8818820248184');
console.log('-------------------------------------------------------');
t(CommonReg.mobile_cn_344, '+86188-2024-8184');
t(CommonReg.mobile_cn_335, '+86188-202-48184');
t(CommonReg.mobile_cn_443, '+861882-0248-184');
console.log('-------------------------------------------------------');
t(CommonReg.curreny_thousandth, '123,3.13');
t(CommonReg.curreny_thousandth, '1,233.13');
t(CommonReg.curreny_thousandth, '1,233.13345');
t(CommonReg.curreny, '1233.13345');
t(CommonReg.curreny, '1233.1334');
t(CommonReg.curreny, '-1233.1334');
t(CommonReg.curreny, '+1233.1334');
console.log('rangeDate----------------------------------------------------');
t(CommonReg.baseRangeDate, '2009-02-01 2009-02-01');
t(CommonReg.baseRangeDate, '2009/02/01 2009/02/01');
t(CommonReg.baseRangeDate, '2009\\02\\01 2009\\02\\01');
t(CommonReg.baseRangeDate, '2009.02.01 2009.02.01');
t(CommonReg.baseRangeDate, '2009 02 01 2009 02 01');
function tttt() {
    const f = '2009-02-01 2009-02-01';
    const result = CommonReg.baseRangeDate.exec(f);
    if (Array.isArray(result)) {
        const begin = [result[1], result[2], result[3]].join('-');
        const end = [result[4], result[5], result[6]].join('-');
        const beginDate = new Date(begin);
        const endDate = new Date(end);

        console.log(begin, end, beginDate, endDate);
    }
}
tttt();
