#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

/*
析构做了什么：
1、对比构造函数：初始化非static成员+其他工作
2、析构：释放对象使用的资源，销毁非static数据成员
顺序
1、构造函数中：成员初始化先于构造函数函数体
2、析构：先执行函数体，然后销毁成员（是上面的逆序）

当指向一个对象的引用或者指针离开作用域时，析构函数不会执行

法则：
1、需要析构的类也需要拷贝和赋值操作
2、需要拷贝操作的类也需要赋值操作，反之一样（析构不一定有）

*/
/*
C++默认帮我们自动合成的析构函数，大多数时候可以很好地工作
但又一些时候需要我们自己去写析构
准则：当类中定义了析构函数，并且构造函数中使用了系统资源（内存申请、文件打开等），则需要自定义析构函数
对象消亡的时候，系统自动调用
*/

class String {
private:
	char* m_str;
public:
	String() { m_str = NULL; }
	String(const char* p) {
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}
	~String() {
		cout << "销毁String对象:" << m_str << endl;
		delete[] m_str;
	}
	int length() { return strlen(m_str); }
	char get_char(int i) { return m_str[i]; }
	void set_char(int i, char c) { m_str[i] = c; }
	char* my_strcpy(char* p) {
		delete[] m_str;
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}
	String& my_strcpy(String& s) {
		delete[] m_str;
		m_str = new char[strlen(s.m_str) + 1];
		strcpy(m_str, s.m_str);
		return *this;
	}
};
/*
一般来说，一个类如果定义了虚函数，最好将析构函数也定义成虚函数

注意是先调用子类的析构函数，再调用父类的析构函数
而构造函数相反，构造函数先父类，再子类
*/
class B {
public:
	virtual ~B() {
		cout << "base destructor" << endl;
	}
};

class D :public B {
public:
	~D() {
		cout << "derived destructor" << endl;
	}
};
//int main() {
//	//String s("asuka saito");
//	B* b1;
//	D d1;
//	b1 = &d1;
//
//	//引用和指针一样动态调用
//	//因为引用的本质就是解引用操作，所以本质上和指针一样使用
//	D d2;
//	B& b2 = d2;
//	return 0;
//}