export module mo.test.cpp;
import hello;

export int testadd(int a, int b) {
	return a + b + mo::test::hello::hello();
}