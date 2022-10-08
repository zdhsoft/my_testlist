export module mo.test.type;
#include <iostream>
#include <vector>

using namespace std;

#define p(T) cout << #T << " size:" << sizeof(T) << endl
template<class T>
void printType(const char* paramPrompt) {
	cout << paramPrompt << " size:" << sizeof(T) << endl;
}

export void typeMain() {
	cout << "TypeMain" << endl;
	printType<bool>("bool");
	printType<char>("char");
	p(int);
	p(wchar_t);
	p(char16_t);
	p(char32_t);
	p(short);
	p(int);
	p(long);
	p(long long);
	p(float);
	p(double);
	p(long double);
	// p(long long double);

}