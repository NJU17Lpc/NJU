#include <iostream>
using namespace std;

/*
测试，继承关系背景下， a = b 赋值操作，在什么情况下是合法的
*/

/*
前期绑定特点
1、编译时期
2、依据对象的静态类型
3、效率高、灵活性差

动态绑定
1、运行时刻
2、依据对象的实际类型
3、灵活性高、效率低

因此C++为了效率
1、默认是前期绑定
2、如果是用后期绑定，需要用virtual显式指出

虚函数：
1、基类中定义为虚成员函数，则派生类中重定义的成员函数均为虚函数
2、限制
	a 类的成员函数才可以是虚函数
	b 静态成员函数不能是虚函数
	c 内联成员函数不能是虚函数（估计是编译器行为，记住就好
	d 构造函数不能是虚函数
	e 析构函数可以（往往）是虚函数

*/

class A {
public:
	void f() {
		cout << "A f()" << endl;
	}
	virtual void k() {
		cout << "A k()" << endl;
	}
private:
	int m_x;
	int m_y;
};

class B:public A {
public:
	B(){}
	void f() {
		cout << "B f()" << endl;
	}
	void g() {
		cout << "B g()" << endl;
	}
	virtual void k() override{
		cout << "B k()" << endl;
	}
private:
	int m_z;
};

//int main() {
//
//	//直接把派生类对象赋值给基类对象
//	A a;
//	B b;
//	a = b; // 父类=子类 OK
//	//b = a; // 子类=父类 ERROR
//	a.f(); //A::f()
//
//	//基类的引用，引用派生类对象!!!
//	//基类的指针，指向派生类对象!!!
//	A &r_a = b; //OK
//	A *p_a = &b; //OK
//
//	//B &r_b = a; //ERROR
//	//B *p_b = &a; //ERROR
//
//	//下面查看普通方法调用，因为不是virtual方法，所以调用的是父类版本
//	r_a.f(); //A::f()
//	p_a->f(); //A::f()
//	//p_a->g(); //无法调用
//
//	//下面查看虚方法调用
//	r_a.k(); //引用是调用子类的虚方法 B::k()
//	p_a->k(); //指针也是调用子类的虚方法 B::k()
//
//	return 0;
//}