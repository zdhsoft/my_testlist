#include <iostream>
#include <string>
#include <cstddef>
#include <concepts>
#include "module01.h";
using namespace std;

// 1 ����demo����΢�����:
// https://devblogs.microsoft.com/cppblog/c20-concepts-are-here-in-visual-studio-2019
//-version-16-3/?utm_source=vs_developer_news&utm_medium=referral
// This concept tests whether 'T::type' is a valid type
template<typename T>
concept has_type_member = requires { typename T::type; };

struct S1 {};
struct S2 { using type = int; };

static_assert(!has_type_member<S1>);
static_assert(has_type_member<S2>);

// Currently, MSVC doesn't support requires-expressions everywhere; they only work in concept definitions and in requires-clauses
//template <class T> constexpr bool has_type_member_f(T) { return requires{ typename T::type; }; }
template <class T> constexpr bool has_type_member_f(T) { return has_type_member<T>; }

static_assert(!has_type_member_f(S1{}));
static_assert(has_type_member_f(S2{}));

// This concept tests whether 'T::value' is a valid expression which can be implicitly converted to bool
// 'std::convertible_to' is a concept defined in <concepts>
template<typename T>
concept has_bool_value_member = requires { { T::value }->std::convertible_to<bool>; };

struct S3 {};
struct S4 { static constexpr bool value = true; };
struct S5 { static constexpr S3 value{}; };

static_assert(!has_bool_value_member<S3>);
static_assert(has_bool_value_member<S4>);
static_assert(!has_bool_value_member<S5>);

// The function is only a viable candidate if 'T::value' is a valid expression which can be implicitly converted to bool
template<has_bool_value_member T>
bool get_value()
{
	return T::value;
}

// This concept tests whether 't + u' is a valid expression
template<typename T, typename U>
concept can_add = requires(T t, U u) { t + u; };

// The function is only a viable candidate if 't + u' is a valid expression
template<typename T, typename U> requires can_add<T, U>
	auto add(T t, U u)
	{
		return t + u;
	}

	// 2 ����demo����https://blog.csdn.net/oLuoJinFanHua12/article/details/101319056

	//std::enable_ifʵ��
	template <typename T>
	void print_int0(std::enable_if_t<std::is_same_v<int, std::decay_t<T>>, T> v)
	{
		std::cout << v << std::endl;
	}
	void print_int0()
	{
		//print_int0(1);			// error C2660: ��print_int0��: ���������� 1 ������
		print_int0<int>(1);
		//print_int0<double>(1.0);    // error C2672: ��print_int0��: δ�ҵ�ƥ������غ���
	}

	// 2.1.����ֻ�ܴ�ӡint����
	template <class T>
	concept IntLimit = std::is_same_v<int, std::decay_t<T>>; //��ԼT���ݺ�����ͱ�����int��ͬ

	template <IntLimit T>
	void print_int(T v)
	{
		std::cout << v << std::endl;
	}

	void concept_test01()
	{
		print_int(1);
		//print_int(1.0); //error C2672: ��print_int��: δ�ҵ�ƥ������غ���/error C7602: ��print_int��: δ�������Լ��
	}

	// 2.2 2.require�ؼ���
	// �޶�ֻ�ܵ��ô���name��Ա��������
	class A
	{
	public:
		std::string_view name() const { return "A"; }
	};

	class B
	{
	public:
		std::string_view class_name() const { return "B"; }
	};

	template <typename T>
	concept NameLimit = requires(T a)
	{
		a.name();	// ��ԼT��ʵ��a����Ҫ��name��Ա����
	};

	template <NameLimit T>
	void print_name(T a)
	{
		std::cout << a.name() << std::endl;
	}

	void concept_requires()
	{
		A a;
		print_name(a);
		//B b;
		//print_name(b); // error C2672 : ��print_name��: δ�ҵ�ƥ������غ���/error C7602: ��print_name��: δ�������Լ��
	}

	// �޶�ֻ�ܵ��÷���ֵ����ת��Ϊstd::string�ĺ���
	template <typename T>
	concept ReturnLimit = requires(T t)
	{
		{t()}->std::convertible_to<std::string>;	// ��������ֵ�������ת��Ϊstd::string
		std::is_function<T>;						// T����Ϊ����
	};

	template <ReturnLimit T>
	void print_string(T func)
	{
		std::cout << func() << std::endl;
	}

	std::string str1()
	{
		return "123";
	}

	constexpr const char* str2()
	{
		return "str2";
	}

	std::basic_string<char8_t> str3()
	{
		return u8"str3";
	}

	void concept_requires_string()
	{
		std::string t;
		t = std::string_view("213");
		print_string(&str1);
		print_string(&str2);
		//print_string(&str3); // error C2672: ��print_string��: δ�ҵ�ƥ������غ���
	}

	// 2.3 concept���Ժ�if constexpr���ʹ��
	class A3
	{
	public:
		constexpr std::string_view name() const { return "A3"; }
	};

	class B3
	{
	public:
		constexpr std::string_view class_name() const { return "B3"; }
	};

	template <typename T>
	concept CA = requires(T a)
	{
		a.name();
	};

	template <typename T>
	concept CB = requires(T b)
	{
		b.class_name();
	};

	template <typename T>
	void print_class(const T& t)
	{
		if constexpr (CA<T>)
		{
			std::cout << t.name() << std::endl;
		}
		else if constexpr (CB<T>)
			std::cout << t.class_name() << std::endl;
	}

	void concepts_constexpr()
	{
		A3 a;
		B3 b;
		print_class(a);
		print_class(b);
	}


	int testConcept() {

		std::cout << add(5, 7.0) << std::endl;

		print_int0();
		concept_test01();
		concept_requires();
		concept_requires_string();
		concepts_constexpr();

		return 0;
	}
