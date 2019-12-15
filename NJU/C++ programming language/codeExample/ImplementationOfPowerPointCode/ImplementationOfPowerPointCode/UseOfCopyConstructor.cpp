#include <iostream>
#include <string>
using namespace std;

/*
1、如果一个构造函数的第一个参数是对 自身类 类型的 引用 ，且额外参数都有默认值
那么这个构造函数是拷贝构造函数
2、合成拷贝构造函数，一般会将参数的成员逐个拷贝到正在创建的对象中
3、拷贝初始化发生的情形
使用=定义变量
将一个变量作为实参，传给一个非引用类型的形参
从一个返回类型为非引用的函数返回一个对象
用花括号列表初始化一个数组或一个聚合类的成员

*/
class A {
private:
	int x;
	int y;
public:
	A():x(0), y(0) {}
	void inc() { x++; y++; }
	void print() {
		cout << "x:" << x << " y:" << y;
	}
};

class B {
private:
	int z;
	A a;
public:
	B() { z = 0; }
	//深拷贝，需要连着成员对象再拷贝一份
	B(const B& b) :a(b.a) {
		//拷贝构造函数内部可以调用参数的私有变量
		z = b.z;
	}
	void inc() {
		z++;
		a.inc();
	}
	void print() {
		a.print();
		cout << " z:" << z << endl;
	}
};

//int main() {
//
//	B b1;
//	b1.print();
//	b1.inc();
//	b1.print();
//	return 0;
//}