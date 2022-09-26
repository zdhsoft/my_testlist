export module c11;
#include "iostream"

int test() {
	return 100;
};

using namespace std;
export void c11() {
	std::cout << "hello c11" << endl;
	int&& m = test();
	std::cout << "test value right ref:" << m << endl;
};