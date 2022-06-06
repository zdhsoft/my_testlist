#include "a.h"
#include <iostream>
#include <map>
using namespace std;
int test2017() {
	cout << "test 2017!" << endl;
	map<int, int> m;
	m.insert(std::pair(1, 2));
	m.insert(std::pair(2, 4));
	m.insert(std::pair(3, 6));
	m.insert(std::pair(4, 8));
	for (const auto& [k, v] : m) {
		cout << "[" << k << "]=" << int(v);
		cout << endl;
	}
	return 0;
}