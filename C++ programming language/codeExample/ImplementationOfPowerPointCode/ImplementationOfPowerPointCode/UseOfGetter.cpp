#include <iostream>
#include <string>
using namespace std;
/*
用于测试继承时，虚方法和非虚方法调用时，动态绑定和静态绑定的结果
*/

class Base
{
public:
	string getA() {
		string name = "Base:";
		return name + to_string(a);
	}
	virtual string getB() {
		string name = "Base:";
		return name + to_string(b);
	}
	Base(int a, int b) :a(a), b(b) {}
protected:
	int a;
	int b;
};
class Derived :public Base
{
public:
	string getA() {
		string name = "Derived:";
		return name + to_string(a);
	}
	virtual string getB() {
		string name = "Derived:";
		return name + to_string(b);
	}
	Derived(int a, int b) :Base(a, b) {}
};

//int main() {
//	Base *b1 = new Derived(1, 1);
//	//非虚方法：int getA()，最后调用基类方法，没能动态绑定
//	//虚方法：virtual int getB()，最后调用子类方法，实现了动态绑定
//	cout << "b1: " << b1->getA() << " " << b1->getB() << endl;
//	Base b2(2, 2);
//	//不去动态声明的话，最后都是调用声明类的方法
//	cout << "b2: " << b2.getA() << " " << b2.getB() << endl;
//	Derived b3(3, 3);
//	cout << "b3: " << b3.getA() << " " << b3.getB() << endl;
//
//	return 0;
//}