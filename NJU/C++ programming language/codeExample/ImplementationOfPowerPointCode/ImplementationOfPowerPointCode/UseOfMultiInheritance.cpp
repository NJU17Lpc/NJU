#include <iostream>
using namespace std;

/*
次序问题：
基类的声明次序决定：
1、对基类构造函数/析构函数的调用次序
2、对基类数据成员的存储安排（目测这个主要和虚基类有关）
*/


//菱形集成，对冲突的部分，要具体指定
//冲突的公共部分，在每个子类中保存一份副本
class A {
public:
	A() {
		cout << "A()" << endl;
	}
protected:
	int m_a;
};

class B :public A {
public:
	B() {
		cout << "B()" << endl;
	}
protected:
	int m_b;
};

class C :public A {
public:
	C() {
		cout << "C()" << endl;
	}
protected:
	int m_c;
};

//A()会构造两次，所以会有两个不同的A对象副本被继承
class D :public C, public B {
public:
	D() {
		cout << "D()" << endl;
	}

	void setA(int a) {
		//m_a = a;//命名冲突，报错：不明确
		B::m_a = a;
		C::m_a = a;
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};


/*
为了解决多继承的命名冲突和冗余数据的问题，使用虚继承，
于是在派生类中只保留  一份  间接基类的成员

虚基类的目的
1、让某个类做出声明，承诺愿意共享它的基类
2、这个被共享的基类就称为虚基类，这里的VA就是虚基类
3、这种情况下，不管虚基类，在继承体系中出现了多少次
在派生类中，都只包含一份虚基类的成员

*/

class VA {
public:
	VA() {
		cout << "VA()" << endl;
	}
protected:
	int m_a;
};

class VB :virtual public VA {//虚继承
public:
	VB() {
		cout << "VB()" << endl;
	}
protected:
	int m_b;
};

class VC :virtual public VA {//虚继承
public:
	VC() {
		cout << "VC()" << endl;
	}
protected:
	int m_c;
};


//继承时声明的顺序，决定了构造器调用的顺序
//比如下面的顺序就是: VA, VC, VB, VD
//VA只构造一次
class VD :public VC, public VB {
public:
	VD() {
		cout << "VD()" << endl;
	}
	void setA(int a) {
		m_a = a;//这个时候就不会有冲突，这里就没有报错
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};

/*
ppt上的注意 ：
1、虚基类的构造函数由最新派生出的类的构造函数调用
就是说，那个子类先被继承，那么就由他来调用虚基类构造函数
2、虚基类的构造函数，优于非虚基类的构造函数执行
就是说，即使是非虚基类先被继承，那么也会先构造虚基类的对象
比如下面的顺序就是: VA,VC,A,VB,VE
*/

class VE :public VC, public A, public VB {
public:
	VE() {
		cout << "VE()" << endl;
	}
	void setA(int a) {
		VC::m_a = a;//这个时候就不会有冲突，这里就没有报错
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};

//int main() {
//	D d; 
//	cout << endl;
//	VD vd;
//	cout << endl;
//	VE ve;
//	return 0;
//}