#include <iostream>;
#include "module01.h";
using namespace std;
int main(int argc, char* argv[]) {

	int a = 9990'9909;
	int b = 999'999;

	auto m = a <=> b;
	cout << int(m) << endl;

	cout << "hello world for C++ 20" << endl;
	cout << a << endl;
	cout << "-------------------------------- test concept" << endl;
	testConcept();
	cout << "-------------------------------- test concept" << endl;
	return 0;

}