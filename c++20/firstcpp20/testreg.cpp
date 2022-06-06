#include "testreg.h"
#include <iostream>
#include <cstdio>
#include <regex>

// export const CommonRegExp = {
//     /** YYYY-MM-DD hh:mm:ss 格式的正则表达式 */
//     dateTime: /^[1-2]\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\d):[0-5]\d:[0-5]\d$/,
//     /** 货币类正则表达式 */
//     curreny: /^\d+(?:\.\d{0,2})?$/,
//     /** YYYY-MM-DD 支持 . - / \ 空格分隔符 格式 */
//     baseDate: /^([1-2]\d{3})[./\-\\\ ](0[1-9]|1[0-2])[./\-\\\ ](0[1-9]|[1-2][0-9]|3[0-1])$/,
//     /** YYYY-MM-DD 格式的日期正则表达式 */
//     simpleDate: /^([1-2]\d{3})(0[1-9]|1[0-2])(0[1-9]|[1-2][0-9]|3[0-1])$/,
//     /** hh:mm:ss的正则表达式 */
//     baseTime: /^([0-1]\d{1}|2[0-3]):([0-5]\d{1}):([0-5]\d{1})$/,
//     /** hhmmss的正则表达式 */
//     simpleTime: /^([0-1]\d{1}|2[0-3])([0-5]\d{1})([0-5]\d{1})$/,
// };
using namespace std;
int testReg() {
	//
	regex rePattern1("^[1-2]\\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):[0-5]\\d:[0-5]\\d$");
	auto s = "2021-01-01 18:00:00";
	regex r1("^\\d*$");
	cout << "比较日期：" << boolalpha << regex_match(s, rePattern1) << endl;
	cout << "数据：" << boolalpha << regex_match("123454567822", r1) << endl;
	return 0;
}