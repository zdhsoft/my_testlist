# C++ 20 ѧϰ�ʼ�
## enum class
### �ɰ�enum���ڵ�����
- 1	�����ε���ʽת��(Implicit conversion to an integer)
- 2	�޷�ָ���ײ���ʹ�õ���������(Inability to specify underlying type)
3	enum��������(Scope)
4	��ͬ���������������ķ�����ͳһ


�ɰ�enum���ڵ�����
����	����
1	�����ε���ʽת��(Implicit conversion to an integer)
2	�޷�ָ���ײ���ʹ�õ���������(Inability to specify underlying type)
3	enum��������(Scope)
4	��ͬ���������������ķ�����ͳһ
1.1 ����1�������ε���ʽת��
�ڿ�ʼ�������֮ǰ��������Ҫ֪��ʲô����������

�鿴֮ǰ�Ĳ��ģ�C\C++�е���������

�ڿ���ʲô����������֮�����ǿ�ʼ������⣺

�ɰ�enum��ʵ�������зǳ���ȫ�����Ͱ�ȫ����Ȼ��Ҳ������һ�������Ͱ�ȫ��1.��ֹ��ͬö����֮��ĸ�ֵ 2.��ֹ������ö�������ʽת���ȣ���Ҳ������������������ɰ�enum��û�п������ġ�

���磺

#include <iostream>

enum colorA{redA,greenA,grayA};
enum colorB {redB,greenB,yellowB};

void test(int data) {
    std::cout << "test called" << std::endl;
}

int main() {
    colorA ca(redA);
    colorB cb(greenB);

    //ca = cb; ERROR , �޷��ӡ�colorB��ת��Ϊ��colorA��
    //ca = 2;  ERROR , �޷��ӡ�int��ת��Ϊ��colorA��

    bool res(ca < cb); //OK
    std::cout << std::boolalpha << res << std::endl;

    test(ca); //OK

    std::cin.get();
    return 0;
}
 

���н����

true 
test called

��������Ĵ��룺������Ȼ���ԱȽ�������ͬö����Ĵ�С����ö������ò���Ϊint�ĺ�������Ȼ��ʱ��ö���巢���� �������� ��

���޷�ʹ��C++11�°�enum������£����Ƶĳ���Ա�뵽�ˣ���enum��װ������ڲ��ķ�����

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

    //ca = 2; ERROR, û���ҵ����ܡ�int�����͵��Ҳ������������(��û�пɽ��ܵ�ת��)
    //test(ca); ERROR, �޷������� 1 �ӡ�Color��ת��Ϊ��int��
    //bool res(ca > 2); ERROR,û���ҵ����ܡ�int�����͵��Ҳ������������(��û�пɽ��ܵ�ת��)

    std::cin.get();
    return 0;
}
 

��ȷ����װ�����е�enum�ܹ��ֿ�������������������enum��ͬ��POD(plain old data)���޷�����Ĵ������У�����������Ŀ�����

1.2 ����2���޷�ָ���ײ���ʹ�õ���������
A. ���ȣ��޷�ָ���������ͣ����������޷���ȷö��������ռ���ڴ��С�������鷳�ڽṹ�嵱����Ϊͻ�����ر��ǵ�������Ҫ�ڴ�������䴦���ʱ��

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
��ʱ���ǵĽ���취���ǣ���ʹ��enum

#include <iostream>

enum Version { Ver1 = 1, Ver2, Ver3 };

struct MyStruct {
    MyStruct(Version ver) { this->Ver = ver; }
    unsigned char Ver;//��enum VersionתΪunsigned char����
    //Ohters...
};

int main() {
    MyStruct m(Version::Ver1);
    std::cin.get();
    return 0;
}
 

B. ��Σ�������ʹ��enumʱ�������޷������������ײ�����ζԴ�enum�ģ����磺signed��unsigned����

#include <iostream>

enum MyEnum { num1 = 1, num2 = 2, numn = 0xFFFFFF00U };

int main() {
    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;
    std::cout << numn << std::endl;
    std::cin.get();
    return 0;
}
 

VS2015���н����

1 
2 
-256

CodeBlocks���н����

1 
2 
4294967040

�� numn=0xFFFFFF00U���У�����ϣ��0xFFFFFF00����Ϊunsigned�����ǲ�ͬ�ı��������׼Ҳ��ͬ����͸����ǵĳ�����������Ĳ�ȷ���ԡ�

���ĵ�n2347�е����ӣ���ͬ��������0xFFFFFFF0U�ı��֡�

#include <iostream>
using namespace std;
enum E { E1 = 1, E2 = 2, Ebig = 0xFFFFFFF0U };
int main() {
    cout << sizeof(E) << endl;
    cout << "Ebig = " << Ebig << endl;
    cout << "E1 ? -1 =\t" << (E1 < -1 ? "less" : E1 > -1 ? "greater" : "equal") << endl;
    cout << "Ebig ? -1 =\t" << (Ebig < -1 ? "less" : Ebig > -1 ? "greater" : "equal") << endl;
}
 

����дͼƬ����

1.3 ����3��enum��������
enum���е� �� { } �� �����Ų�û�н�ö�ٳ�Ա�Ŀɼ��������ڴ������ڣ�����enum��Ա��¶������һ��������(�����)�С�

���磺

#include <iostream>
enum color{red,blue};//����ӵ��������Ա��enum��red��blue��enum�Ĵ������ⲿ����ֱ�ӷ��ʣ�������Ҫʹ�����������
int main() {
    std::cout << blue << std::endl;
    std::cin.get();
    return 0;
}
 

 

���н����

1

-

��������Ĵ��룬���ǿ�����blue�Ĵ�����֮���������color�ĳ�Ա��й¶���˸��ļ���ȫ���������У���Ȼ���в��߱��ⲿ�����ԣ�������ֱ�ӷ��ʣ�������Ҫ��������İ�����

�����ⲻ�ǹؼ�����ʱ���Ƿ������÷ǳ����㡣��������������ڣ�

���⣺�޷�����ͬ����ö�ٳ�Ա
enum color { red, blue };
//enum MyEnum { red, yellow }; ERROR, �ض��壻��ǰ�Ķ����ǡ�ö������
 

������Ĵ�����ʾ�������޷��ظ�ʹ��red�����ʶ������Ϊ����color���Ѿ����ù��ˡ����ǣ������������ǲ�ͬ��ö�����ͣ��������ʹ����ͬ�ĳ�Ա���ƣ�Ȼ��ͨ��������������ʵĻ������ж�ã���������������

color::red

�������Ǿɰ��enum�޷������ġ�

����������⣺���������ռ�
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
 

���н����

0 
1 
false

-

�ǵģ�ֻҪ���������ռ����Ǿ��ܽ��ö����ĳ�Ա�ض������⣬��������˶����һ�������ռ䣬δ���Ե��鷳