#include <iostream>
using namespace std;

/*
1、测试虚函数调用和虚函数表的查看
2、测试从类中虚函数与非虚函数之间的相互调用
*/
class A {
public:
	//!!!!!!!!!!重要
	//A 构造器，并没有多态调用，因为构造函数完成之后，才能正常使用对象
	//所以在构造器内静态调用
	A() {
		cout << "A() constructor, call virtual f():";
		f(); 
	}
	virtual void f() {
		cout << "A f()" << endl;
	}
	virtual void g() {
		cout << "A g()" << endl;
	}

	//非虚函数h()，内部调用虚函数时动态调用，调用非虚函数时静态调用
	//感觉这个应该是正常状态，即这种普通函数，虚就虚，非虚就非虚
	void h() {
		cout << "non-virtual A h(), call virtual f(), non-virtual k()  " << endl;
		f();
		k();
	}
	void k() {
		cout << "A k()" << endl;
	}
	virtual void m() {
		cout << "A m()" << endl;
	}
private:
	int m_x;
	int m_y;
};

class B :public A {
public:
	B() {}
	virtual void f() {
		cout << "B f()" << endl;
	}
	void h() {
		cout << "B k()" << endl;
	}
	void k() {
		cout << "B k()" << endl;
	}

	//!!!!!!!!!!这个比较重要
	//虚函数m()，调用非虚函数，调用的是子类自己的k()，而不是父类的k()
	//因为这个虚函数里面内置了一个B* const this
	//所以即使是调用非虚函数，也是调用this->k()
	virtual void m() {
		cout << "virtual B m(), call non_virtual k()" << endl;;
		k();
	}
private:
	int m_z;
};

//int main() {
//
//	A a;
//	B b;
//	A* p;
//	//p 指向对象，而 对象 的内存空间有指针，指向虚函数表
//	//可以在debug模式下查看_vfptr对应的虚函数表
//
//	//这个虚函数表内容为A::f  A::g，A::h不是虚函数，不在虚函数表中
//	p = &a;
//	p->f();//A f()
//
//	//这个虚函数表内容为B::f A::g
//	//因为f()在B中有重载，而g()没有重载，使用的是父类的g()
//	p = &b;
//	p->f();//B f()
//	p->g();//A g()
//	p->h();
//	cout << endl;
//
//	p->m();
//	cout << endl;
//
//	return 0;
//}