#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

/*
我们想要移动对象，而不是拷贝，来提升性能
考察左值和右值
1、左值：有持久状态
2、右值：要么是字面常量，要么是求值过程中的临时对象
	所引用的对象，要么将要被销毁，要么没有其他用户
	于是右值不能绑定到左值:int&& rr = i;错误
		但是int&& rr = i*40;正确
	因此右值引用的代码可以自由接管所引用对象的资源
3、我们也可以显式（强行）获得绑定在左值上的右值引用
	int &&rr = std::move(rr1);
	但这样做要承诺：除了赋值或者销毁rr1，我们不再使用它

移动构造函数
1、构造函数的第一个参数是该类类型的一个引用，而且是右值引用
并且任何额外的参数都有默认实参
2、一旦移动完成，被移动的资源的所有权，不再是源对象所有

拷贝构造函数中，有额外的资源申请和释放的操作
移动构造函数中，直接使用临时对象已经申请的资源，如果不是临时对象（是个非临时变量），需要进行转换

右值还可以做精确传递perfect forwarding，目测不用深入看
参考 https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
*/
class String {
private:
	char* m_str;
public:
	String() {
		cout << "普通无参构造函数" << endl;
		m_str = NULL; 
	}
	String(const char* p) {
		cout << "普通带参构造函数" << endl;
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}

	String(const String& str) {
		cout << "拷贝构造函数" << endl;
		m_str = new char[strlen(str.m_str) + 1];
		strcpy(m_str, str.m_str);
	}

	String(String&& str)noexcept {
		cout << "移动构造函数" << endl;
		m_str = str.m_str;
		str.m_str = NULL;//这个必须要有
	}
	~String() {

		if (m_str != NULL) {
			cout << "销毁String对象:" << m_str << endl;
			delete[] m_str;
		}
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

String getStr(const char* p) {
	String temp(p);
	return temp;
}
//这里涉及的东西比较复杂，最好确认一下考不考
//int main() {
//	String s1("saito asuka");
//	String s2 = s1;
//	String s3(s2);
//
//	//将已命名对象，即左值引用，当做右值来使用
//	//编译器可以区分开
//	String s4(std::move(s2));//使用move来调用移动构造函数
//
//	//下面是利用临时对象已经申请的资源的例子
//	String s5 = getStr("erika");//这个就是移动构造函数，函数内部是一个普通带参构造函数
//	return 0;
//}