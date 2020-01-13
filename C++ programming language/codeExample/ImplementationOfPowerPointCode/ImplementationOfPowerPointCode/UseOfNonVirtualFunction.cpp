#include <iostream>
using namespace std;


/*
C++ 的名称遮掩规则
1、就是遮掩名称，类型倒是其次
2、要避免遮掩继承而来的名称，就是因为名称查找的时候会有意想不到的行为

比较一般虚函数和非虚函数
1、一般虚函数
	子类必须继承函数接口
	可以继承缺省实现
2、非虚函数
	必须同时继承接口和实现代码
*/
class B {
public:
	virtual void mf1() {
		cout << "B:mf1()" << endl;
	}
	virtual void mf1(int i) {
		cout << "B:mf1(int)" << endl;
	}
	virtual void mf2() {
		cout << "B:mf2()" << endl;
	}
	void mf3() {
		cout << "B:mf3()" << endl;
	}
	void mf3(double i) {
		cout << "B:mf3(double)" << endl;
	}
};

class D :public B {
public:
	//using B::mf1;
	//using B::mf3;
	virtual void mf1() {
		cout << "D:mf1()" << endl;
	}

	void mf3() {
		cout << "D:mf3()" << endl;
	}
	void mf4() {
		cout << "D:mf4()" << endl;
	}
};

//int main() {
//	D d;
//	int x=0;
//
//	d.mf1();//D:mf1() 没什么问题
//	//d.mf1(x);//错误，D:mf1()遮掩了B:mf1(int)
//	d.mf2();//B:mf2() 没什么问题，毕竟D没有覆盖
//	d.mf3();//D:mf3() 没什么问题，D中覆盖了mf3()
//
//	//下面这个例子，显示了Derived中的函数名甚至可以遮盖类型不同的Base函数
//	//d.mf3(x);//错误，因为D:mf3()遮盖了B:mf3(double)，因为名称查找，找到就停止了，没有去确认参数是否匹配，
//	//这么设计的原因是：为了防止从很远的base class 继承重载函数
//	
//	//但是我们总会想办法推翻这种行为
//	//可以在D中加入using Base::mf3;using Base::mf1;
//	//那样上面注释掉的两句都可以正常使用了
//
//	//其实using也不是很好，最好用转交函数
//	//就是下面这个，注意这只是注释哈
//	//virtual void mf1() {
//	//	Base::mf1();
//	//}
//	return 0;
//}