export module c11;
#include "iostream"
#include <vector>

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

void testVector() {
	const int intList[] = { 1, 2, 3, 4, 5 };
	std::vector<int> m = { 1, 2, 3, 4, 5 };
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << "testVector:" << *it << endl;
	}
}
export void c11() {
	std::cout << "hello c11" << endl;
	auto && m = test();
	auto&& t = test();
	auto& k = m;
	foo(k);
	k++;
	foo(m);
	foo(1000);
	foo(t);
	cout << "-----------------" << endl;
	std::cout << "test value right ref:" << m << endl;
	testVector();
};