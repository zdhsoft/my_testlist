// aaa.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <regex>
using namespace std;

void testRegex() {
	//regex stRegDateTime("(\\d{4})-(0\\d{1}|1[0-2])-(0\\d{1}|[12]\\d{1}|3[01])\\s(0\\d{1}|1\\d{1}|2[0-3]):[0-5]\\d{1}:([0-5]\\d{1})");
	//^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d)$
	regex ss("^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d)$");
	regex ss1("^([1-2]\\d{3})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (20|21|22|23|[0-1]\\d):([0-5]\\d):([0-5]\\d).(\\d{1,3})$");
	string s = "2022-01-02 03:04:05";
	string s1 = "2022-01-02 03:04:05.123";
	smatch m, m1;
	
	if (regex_search(s, m, ss)) {
		std::cout << "matches for '" << s << "'\n";
		std::cout << "Prefix: '" << m.prefix() << "'\n";
		for (size_t i = 0; i < m.size(); ++i)
			std::cout << i << ": " << m[i] << '\n';
		std::cout << "Suffix: '" << m.suffix() << "\'\n\n";
	}
	if (regex_search(s1, m1, ss1)) {
		std::cout << ">> matches for '" << s1 << "'\n";
		std::cout << "Prefix: '" << m1.prefix() << "'\n";
		for (size_t i = 0; i < m1.size(); ++i)
			std::cout << i << ": " << m1[i] << '\n';
		std::cout << "Suffix: '" << m1.suffix() << "\'\n\n";
	}
}

class A {
private:
	int m;
public:
	A() {
		m = 0;
	}
	A(int mm) : m(mm) {}
	virtual ~A() {
		std::cout << "A的析构函数" << endl;
	}
};

class B : public A{
public:
	B() {}
	~B() {
		std::cout << "B的析构函数" << endl;
	}
};



int main()
{
	const A* a = new B();
	delete a;
//     std::cout << "Hello World!\n" << endl;;
//     testRegex();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
