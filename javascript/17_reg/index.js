const r = /^([1-2]\d{3})[./\-\\\ \u5e74]{1}(0[1-9]|1[0-2]?|[23456789])[./\-\\\ \u6708]{1}(0[1-9]?|1[0-9]?|2[0-9]?|3[0-1]?|[456789])[\u65e5]?$/;
const a = ['2022年12月12日', '2022-1-1', '2022-01-32', '2022.11.9', '2022 1 1', '2022/01/01', '2022\\01\\01'];


const k = /^(0[1-9]?|1[0-9]?|2[0-9]?|3[0-1]?|[456789])$/;
const m = /^(0[1-9]|1[0-2]?|[23456789])$/;

const b = [];
for(let i = 0; i < 33; i++) {
    if (i < 10) {
        b.push('0' + String(i))
    }
    b.push(String(i));
}

function test(paramPrompt, paramValueList, paramReg) {
    paramValueList.forEach((v) => {
        console.log(`${paramPrompt}: ${v} => ${paramReg.test(v)}`)
    })
}

test('日期', a, r);
// test('num', b, m);
