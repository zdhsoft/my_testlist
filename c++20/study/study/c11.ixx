export module c11;
#include "iostream"

int test() {
	return 100;
};


using namespace std;
void foo(int & v) {
	std::cout << "left value:" << v << endl;
}

void foo(int&& v) {
	std::cout << "right value:" << v << endl;
}
export void c11() {
	std::cout << "hello c11" << endl;
	auto && m = test();
	auto& k = m;
	foo(k);
	k++;
	foo(m);
	cout << "-----------------" << endl;
	std::cout << "test value right ref:" << m << endl;
};