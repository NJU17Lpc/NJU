#include<iostream>
using namespace std;

/*
const出现在星号左边，表示被指物是常量
const出现在星号右边，表示指针自身是常量
const出现在星号两边，表示都是常量
const与类型的顺序无关：const int* a;  int const* a;一样
const函数可以用作重载
*/

class myNumber {
private:
	int num1;
	int num2;
	char* info;
public:
	myNumber(int n1, int n2) :num1(n1), num2(n2) {
		info = new char[5]{ 0 };
	}
	void testConstFunc1(int newNum1, int newNum2) const {
		//const类型函数不能修改成员
		//比如下面两句不能编译
		/*num1 = newNum1;
		num2 = newNum2;*/
		//也不可以调用非静态函数
		//testConstFunc2(newNum1, newNum2);

		//但是如果数据成员是指针，const成员函数也是可以修改指针指向的对象的
		//	这是不好的风格，但不是错误的
		for (int i = 0; i < 3; i++) {
			info[i] = 'a';
		}
		cout << "testConstFunc1 with const" << endl;
	}

	//const函数可以作为重载
	//声明对象的常量性决定调用哪个版本
	//常量对象只能调用常量函数
	//非常量对象都可以调用
	void testConstFunc1(int newNum1, int newNum2) {
		cout << "testConstFunc1 without const" << endl;
	}

	void testConstFunc2(int newNum1, int newNum2) {
		num1 = newNum1;
		num2 = newNum2;
		cout << "testConstFunc2 without const" << endl;
	}
	friend const myNumber operator*(myNumber m1, myNumber m2);
	friend ostream& operator<<(ostream& out, myNumber n);
};
ostream& operator<<(ostream& out, myNumber n) {
	out << n.num1 << " " << n.num2;
	return out;
}

/*
这个返回的const往往可以降低客户错误造成的意外，提高安全性
比如if(a*b=c)本来应该是==，但写错了

*/
const myNumber operator*(myNumber m1, myNumber m2) {
	myNumber n(m1.num1*m2.num1, m2.num2*m2.num2);
	return n;
}

//int main() {
//	myNumber n1(2, 3);
//	myNumber n2(2, 3);
//	myNumber n3 = n1 * n2;
//	const myNumber n4(1, 1);
//	//const类对象只能调用const成员函数
//	//同时优先调用的是const版本的重载
//	//n4.testConstFunc2(3, 4);
//	n4.testConstFunc1(3, 4);
//
//	//非const对象重载函数优先调用非const版本
//	//非const对象可以调用const和非const函数
//	n1.testConstFunc1(2, 3);
//	n1.testConstFunc2(2, 3);
//
//	cout << n1 << endl << n2 << endl << n3 << endl;
//	return 0;
//}