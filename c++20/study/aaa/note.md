# C++ 20 学习笔记
## enum class
### 旧版enum存在的问题
- 1	向整形的隐式转换(Implicit conversion to an integer)
- 2	无法指定底层所使用的数据类型(Inability to specify underlying type)
3	enum的作用域(Scope)
4	不同编译器解决该问题的方法不统一


旧版enum存在的问题
问题	描述
1	向整形的隐式转换(Implicit conversion to an integer)
2	无法指定底层所使用的数据类型(Inability to specify underlying type)
3	enum的作用域(Scope)
4	不同编译器解决该问题的方法不统一
1.1 问题1：向整形的隐式转换
在开始这个问题之前，我们需要知道什么是整形提升

查看之前的博文：C\C++中的整形提升

在看完什么是整形提升之后，我们开始这个问题：

旧版enum其实并不具有非常完全的类型安全（当然它也体现了一定的类型安全：1.禁止不同枚举体之间的赋值 2.禁止整形向枚举体的隐式转换等），也就是面对整形提升，旧版enum是没有抗拒力的。

例如：

#include <iostream>

enum colorA{redA,greenA,grayA};
enum colorB {redB,greenB,yellowB};

void test(int data) {
    std::cout << "test called" << std::endl;
}

int main() {
    colorA ca(redA);
    colorB cb(greenB);

    //ca = cb; ERROR , 无法从“colorB”转换为“colorA”
    //ca = 2;  ERROR , 无法从“int”转换为“colorA”

    bool res(ca < cb); //OK
    std::cout << std::boolalpha << res << std::endl;

    test(ca); //OK

    std::cin.get();
    return 0;
}
 

运行结果：

true 
test called

就像上面的代码：我们仍然可以比较两个不同枚举体的大小，用枚举体调用参数为int的函数。显然此时的枚举体发生了 整形提升 。

在无法使用C++11新版enum的情况下，机制的程序员想到了：将enum封装到类的内部的方法。

#include <iostream>

class Color {
private:
    enum _color { _red, _blue, _yellow, _black };
public:
    explicit Color(const _color & other) {
        value = value;
    }
    explicit Color(const Color & other) {
        value = other.value;
    }
    const Color& operator=(const Color& other) {
        value = other.value;
        return *this;
    }
    static const Color red, blue, yellow, black;
    _color value;
    //operators
    bool operator <(const Color & other) { return value < other.value; }
    bool operator >(const Color & other) { return value > other.value; }
    bool operator <=(const Color & other) { return value <= other.value; }
    bool operator >=(const Color & other) { return value >= other.value; }
    bool operator ==(const Color & other) { return value == other.value; }
    //...

    //conversion
    int toint() { return value; }
};
//init static const Color obj
const Color Color::red(Color::_color::_red);
const Color Color::blue(Color::_color::_blue);
const Color Color::yellow(Color::_color::_yellow);
const Color Color::black(Color::_color::_black);

void test(int data) {
    std::cout << "called" << std::endl;
}

int main() {
    Color ca(Color::blue);
    std::cout << ca.toint() << std::endl;

    //ca = 2; ERROR, 没有找到接受“int”类型的右操作数的运算符(或没有可接受的转换)
    //test(ca); ERROR, 无法将参数 1 从“Color”转换为“int”
    //bool res(ca > 2); ERROR,没有找到接受“int”类型的右操作数的运算符(或没有可接受的转换)

    std::cin.get();
    return 0;
}
 

的确，封装在类中的enum能够抵抗整形提升。但是这种enum不同于POD(plain old data)，无法放入寄存器当中，这会带来额外的开销。

1.2 问题2：无法指定底层所使用的数据类型
A. 首先，无法指定数据类型，导致我们无法明确枚举类型所占的内存大小。这种麻烦在结构体当中尤为突出，特别是当我们需要内存对齐和填充处理的时候。

#include <iostream>

enum Version { Ver1 = 1, Ver2, Ver3 };

struct MyStruct {
    MyStruct(Version ver) { this->Ver = ver; }
    Version Ver;
    //Ohters...
};

int main() {
    MyStruct m(Version::Ver1);
    std::cin.get();
    return 0;
}
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
此时我们的解决办法还是：不使用enum

#include <iostream>

enum Version { Ver1 = 1, Ver2, Ver3 };

struct MyStruct {
    MyStruct(Version ver) { this->Ver = ver; }
    unsigned char Ver;//将enum Version转为unsigned char类型
    //Ohters...
};

int main() {
    MyStruct m(Version::Ver1);
    std::cin.get();
    return 0;
}
 

B. 其次，当我们使用enum时，我们无法决定编译器底层是如何对待enum的（比如：signed和unsigned）。

#include <iostream>

enum MyEnum { num1 = 1, num2 = 2, numn = 0xFFFFFF00U };

int main() {
    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    std::cout << numn << std::endl;
    std::cin.get();
    return 0;
}
 

VS2015运行结果：

1 
2 
-256

CodeBlocks运行结果：

1 
2 
4294967040

在 numn=0xFFFFFF00U；中，我们希望0xFFFFFF00表现为unsigned。但是不同的编译器其标准也不同。这就给我们的程序带来了许多的不确定性。

在文档n2347中的例子：不同编译器对0xFFFFFFF0U的表现。

#include <iostream>
using namespace std;
enum E { E1 = 1, E2 = 2, Ebig = 0xFFFFFFF0U };
int main() {
    cout << sizeof(E) << endl;
    cout << "Ebig = " << Ebig << endl;
    cout << "E1 ? -1 =\t" << (E1 < -1 ? "less" : E1 > -1 ? "greater" : "equal") << endl;
    cout << "Ebig ? -1 =\t" << (Ebig < -1 ? "less" : Ebig > -1 ? "greater" : "equal") << endl;
}
 

这里写图片描述

1.3 问题3：enum的作用域
enum的中的 ” { } ” 大括号并没有将枚举成员的可见域限制在大括号内，导致enum成员曝露到了上一级作用域(块语句)中。

例如：

#include <iostream>
enum color{red,blue};//定义拥有两个成员的enum，red和blue在enum的大括号外部可以直接访问，而不需要使用域运算符。
int main() {
    std::cout << blue << std::endl;
    std::cin.get();
    return 0;
}
 

 

运行结果：

1

-

就如上面的代码，我们可以在blue的大括号之外访问它，color的成员被泄露到了该文件的全局作用域中（虽然它尚不具备外部链接性）。可以直接访问，而不需要域运算符的帮助。

但是这不是关键，有时我们反而觉得非常方便。下面才是问题所在：

问题：无法定义同名的枚举成员
enum color { red, blue };
//enum MyEnum { red, yellow }; ERROR, 重定义；以前的定义是“枚举数”
 

如上面的代码所示：我们无法重复使用red这个标识符。因为它在color中已经被用过了。但是，它们明明就是不同的枚举类型，如果可以使用相同的成员名称，然后通过域运算符来访问的话，该有多好！就像下面这样：

color::red

但是这是旧版的enum无法做到的。

解决上述问题：利用命名空间
#include <iostream>

namespace spaceA {
    enum color { red, blue };
}
namespace spaceB {
    enum colorX { red, blue };
}
int main() {
    std::cout << spaceA::red << std::endl;
    std::cout << spaceB::blue << std::endl;
    std::cout << std::boolalpha << (spaceA::red > spaceB::blue) << std::endl;
    std::cin.get();
    return 0;
}
 

运行结果：

0 
1 
false

-

是的，只要利用命名空间我们就能解决枚举体的成员重定义问题，但是添加了多余的一层命名空间，未免显得麻烦