/*************************************************************************
 * Copyright(c) 2017-2021,
 *
 * All rights reserved.
 *
 * @filename main.ts
 * @summary：项目主程序
 * @version: 1.0
 * ------------------------------------------------------------------------
 * version             author            reason             date
 * 1.0                 祝冬华       创建文件            2021-12-27
 *************************************************************************/

import { getLogger } from 'xmcommon';
const log = getLogger(__filename);

const rx_one = /^[\],:{}\s]*$/;
const rx_two = /\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g;
const rx_three =
    /"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g;
const rx_four = /(?:^|:|,)(?:\s*\[)+/g;
const rx_dangerous =
    /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g;

type TReviver = (holder: any, key: string, value: any) => any;

function walk(holder: any, key: any, reviver: TReviver) {
    const value = holder[key];
    if (value && typeof value === 'object') {
        for (const k in value) {
            if (Object.prototype.hasOwnProperty.call(value, k)) {
                const v = walk(value, k, reviver);
                if (v !== undefined) {
                    value[k] = v;
                } else {
                    delete value[k];
                }
            }
        }
    }
    return reviver(holder, key, value);
}

function parseJSON(paramText: string, reviver?: TReviver) {
    let text = String(paramText);
    rx_dangerous.lastIndex = 0;
    if (rx_dangerous.test(text)) {
        text = text.replace(rx_dangerous, function (a) {
            return '\\u' + ('0000' + a.charCodeAt(0).toString(16)).slice(-4);
        });
    }

    if (
        rx_one.test(
            text
                .replace(rx_two, '@')
                .replace(rx_three, ']')
                .replace(rx_four, ''),
        )
    ) {
        const j = eval('(' + text + ')');
        return typeof reviver === 'function' ? walk({ '': j }, '', reviver) : j;
    }
    throw new SyntaxError('JSON.parse');
}

function rrr(holder: any, key: string, value: any) {
    log.info(holder, key, value);
}
log.info('---------------');
const v = parseJSON('{"a": 100, "b": [1,2,4,5]}', rrr);
log.info('--------------->>>');
log.info(JSON.stringify(v, null, 2));
