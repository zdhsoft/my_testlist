export module mo.test.reg;
#include <regex>
#include <string>
#include <iostream>
using namespace std;
export void testReg() {
	regex stRegDateTime("(\\d{4})-(0\\d{1}|1[0-2])-(0\\d{1}|[12]\\d{1}|3[01])\\s(0\\d{1}|1\\d{1}|2[0-3]):[0-5]\\d{1}:([0-5]\\d{1})");
	string s = "2022-01-02 03:04:05";
	cout << "testReg" << endl;
}