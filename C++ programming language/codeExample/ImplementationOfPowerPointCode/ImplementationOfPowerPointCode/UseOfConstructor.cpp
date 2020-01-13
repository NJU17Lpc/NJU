#include <iostream>
#include <string>
using namespace std;
/*
在构造函数中使用成员初始化表取代赋值动作，效率比较高
以下几个类型必须使用：const/reference/对象成员/父类Private

但是数据成员太多时，这么做就会降低可维护性
*/


//看构造函数的自动调用
class A {
public:
	A() { cout << "normal" << endl; }
	A(int i) { cout << "int " << i << endl; }
	A(const char* p) { cout << "char* p " << p << endl; }
};

//看成员初始化表
//成员初始化列表，是在定义数据的同时赋值；构造函数是先定义后赋值
//有些场景必须要成员初始化列表
//成员初始化列表，按照数据成员的!!!声明顺序!!!(注意和构造器中初始化顺序无关)，安排在构造函数所有代码之前进行
//因此不要用次序在后面的成员来初始化次序在前面的成员
/*
需要使用初始化成员列表的情形
1、要初始化的数据成员是对象
2、要初始化const修饰类成员
3、初始化引用成员函数
4、子类初始化父类私有成员
*/

//情形1，初始化对象，对象有无默认构造器很重要
class TempC {
public:
	TempC(int, int) {
		cout << "this is TempC" << endl;
	}
	TempC() {
		cout << "this is TempC default" << endl;
	}
private:
	int a;
	int b;
};


class B {
public:
	B(int) {
		//这种情况，编译器调用TempC默认构造函数
		//如果把TempC里面手写的那个默认构造函数去掉，就会保存
		cout << "this is B without tempc init" << endl;
	}
	B() : tempc(1, 1) {
		//在初始化成员列表的时候 tempc 优先被初始化
		cout << "this is B" << endl;
	}
private:
	TempC tempc;//这是声明
};

//情形2/3,初始化const和&引用
class D {
public:
	//这个构造器错误，因为引用和const类型的数据必须要放在初始化成员列表中
	/*D(){
		a = 3; b = 4;
	}*/

	//这个构造器就没事了
	//顺便提一下，给int&赋值不能是常数参数，但给const int&赋值，常数和变量参数都可以
	D(int e):a(1),b(e),c(e),d(1){
		cout << a << " " << b << " " << c << " " << d << endl;
	}

private:
	const int a;
	int& b;
	const int c;
	const int d;
};

//情形3，子类初始化父类私有成员
class E {
public:
	E(int x) { m_x = x; cout << "this is E with x:" << x << endl; }
private:
	int m_x;
};

class E_son :E {
public:
	E_son(int x):E(x) {
		//不能在构造函数内部调用父类构造器，来初始化父类私有成员
		//E(x);
	}
};

//int main() {
//
//	//这几个调用A(int i)
//	A a11 = A(1);
//	A a12(1);
//	A a13 = 1;
//	A a14 = a13;//默认拷贝构造函数
//	cout << endl;
//	//这几个调用A()
//	A a21 = A();
//	A a22;
//	A a23();//ppt 说不能这样，但实际上没事
//	cout << endl;
//	//这几个调用A(char*)//ppt有问题，构造器应该写成A(const char* p)
//	A a31 = A("abcd");
//	A a32("abcd");
//	A a33 = "abcd";
//	cout << endl;
//	//这个调用四次A()
//	A a4[4];
//	cout << endl;
//	//这个按照括号内容调用
//	A a5[5] = { A(), A(1), A("abcd"), 2, "xyz" };
//	cout << endl;
//
//	//测试成员初始化表
//	B b1;
//	cout << endl;
//	B b2(1);
//	cout << endl;
//	D d = 2;
//	cout << endl;
//	E e = 7;
//	cout << endl;
//	return 0;
//}