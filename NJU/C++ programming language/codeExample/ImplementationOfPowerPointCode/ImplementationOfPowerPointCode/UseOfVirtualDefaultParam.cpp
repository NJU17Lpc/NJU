#include <iostream>
using namespace std;

/*
绝对不要重新定义继承而来的缺省参数值
*/
class A {
public:
	virtual void f(int x = 0) = 0;
};

class B :public A {
public:
	virtual void f(int x = 1) {
		cout << x;
	}
};

class C :public A {
public:
	virtual void f(int x) { cout << x; }
};

int main() {
	A* p_a;
	B b;
	p_a = &b;
	//我明明在class B 的f(int x=1)里面设置好了默认值，然后打印结果还是0
	//因为B对象中，只记录虚函数的入口地址，不记录默认参数
	p_a->f();

	cout << endl;

	A* p_a1;
	C c;
	p_a1 = &c;
	p_a1->f();

	/*
	刚才的p_a p_a1 ，不管他们指向的是什么对象，他们的静态类型还是A
	virtual 函数自然是动态绑定的
	而缺省参数值也是静态绑定的，所以传入的是父类A的缺省参数值

	为什么这样设计C++？
	如果缺省值动态绑定，会更慢更复杂，为了速度和实现上的简易性，最终这样做
	
	*/

	return 0;
}