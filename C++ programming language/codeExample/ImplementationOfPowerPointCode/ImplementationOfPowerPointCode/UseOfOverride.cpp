#include <iostream>
using namespace std;

/*
感觉大概有几点
1、虚函数才能override
2、final不能override
3、override函数名和参数需要匹配，包括const这种也要匹配
*/
class B {
public:
	virtual void f1(int) const;
	virtual void f2();
	void f3();
	virtual void f5(int) final;
};

class D :public B {
public:
	void f1(int) const override;//OK,与基类的f1类型匹配，注意需要有const标记，比较const是可以区分重载函数的
	//void f2(int) override;//找不到形如f2(int)的基类函数
	//void f3() override;//f3不是虚函数，注意不能覆盖虚函数
	//void f4() override;//基类没有叫f4的函数
	//void f5(int);//基类中，f5已经声明为final，不能override
};