#include <iostream>
#include "a.h";
using namespace std;
class Test
{
	int m_v1;
	int m_v2;
public:
	/**
	 * @param paramV1 value for v1
	 * @param paramV2 value for v2
	 */
	Test(const int paramV1 = 10, const int paramV2 = 20) : m_v2(paramV2 + 100)
	{
		m_v1 = m_v2 + paramV1;
	}
	/**
	 * @return ·µ»Øv1µÄÖµ 
	 */
	int get_v1() const
	{
		return m_v1;
	}
	int get_v2() const
	{
		return m_v2;
	}

	int s_Add() const
	{
		return this->add();
	}

private:
	int add() const
	{
		return this->get_v1() + this->get_v2();
	}
};
int main(int argc, char* argv[]) {

	test2017();

	constexpr int a = 9990'9909;
	constexpr int b = 999'999;

	cout << "hello world for C++ 20" << endl;
	cout << a << endl;
	cout << "-------------------------------- test concept" << endl;

	cout << "-------------------------------- test concept" << b <<endl;

	return 0;
}