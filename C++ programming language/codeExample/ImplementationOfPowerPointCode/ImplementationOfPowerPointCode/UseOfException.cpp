#include <iostream>
#include <exception>
using namespace std;

/*
catch 可以捕获
1、类型：异常的类型，匹配规则和函数重载一样
2、变量：存储异常对象，可以省略
一个try后面可以跟多个catch，用于捕获不同类型的异常来处理

如果抛出的异常对象在调用链上没有被捕获，则由系统abort处理

基本上除了基类和派生类的转换，catch都精确匹配，不允许隐式转换
*/

void throwFunc(int type) {
	switch (type)
	{
	case 1:
		cout << "throw 1: ";
		throw 1;
		break;
	case 2:
		cout << "throw 1.0: ";
		throw 1.0;
		break;
	case 3:
		cout << "throw abcd: ";
		throw "abcd";
		break;
	default:
		break;;
	}
}

void catchFunc(int i) {
	try
	{
		throwFunc(i);
	}
	catch (int)
	{
		cout << "catch int" << endl;
	}
	catch (double)
	{
		cout << "catch double" << endl;
	}
	catch (const char*)
	{
		cout << "catch const char*" << endl;
	}

}

//考察异常处理的嵌套
//参数匹配时，内部先捕获异常
void g(int i) {
	try {
		throwFunc(i);
	}
	catch (int) {
		//这个无参数throw，会将捕获到的异常重新抛出去，就是在f里面再处理一遍
		cout << "g catch int";
		cout << ", and then throw again: ";
		throw;
	}
}

void f(int i) {
	try
	{
		g(i);
	}
	catch (int)
	{
		cout << "f catch int" << endl;
	}
	catch (const char*) {
		cout << "f catch const char*" << endl;
	}
	catch (...) {
		cout << "f default exception handler" << endl;
	}
}




//自定义异常类，使用引用来捕获
//有继承关系时，顺序很重要了，因为有基类和派生类的转换
class  MyExceptionBase{};

class MyExceptionDerived:public MyExceptionBase{};

void myExceptionThrow(MyExceptionBase& e) {
	//按照下面的catch顺序
	//如果传入Base异常，catch的也是base
	//如果传入Derived异常，catch的就是derived
	//因为throw调用的是!!!!拷贝构造!!!!，则参数静态类型决定catch类型
	throw e;
}

void myExceptionCatch() {
	MyExceptionDerived e;
	try {
		myExceptionThrow(e);
	}
	catch (MyExceptionDerived& e) {//更具体的异常应该要放在前面捕获
		cout << "MyExceptionDerived" << endl;
	}
	catch (MyExceptionBase& e) {
		cout << "MyExceptionBase" << endl;
	}
	catch (...) {
		cout << "Normal catch" << endl;
	}

}

//测试异常处理类exception
class myException1 :public exception {
public:
	//注意一定要有后面的const
	const char* what() const{
		return "my exception1";
	}
};
class myException2 :public exception {
public:
	const char* what() const{
		return "my exception2";
	}
};

void myInnerFunc() {
	myException1 e1;
	myException2 e2;
	throw e1;
}

void myOutterFunc() {
	try
	{
		myInnerFunc();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}
//
//int main() {
//	catchFunc(1);
//	catchFunc(2);
//	catchFunc(3);
//	cout << endl;
//	myExceptionCatch();
//	cout << endl;
//	f(1);
//	f(2);
//	f(3);
//	cout << endl;
//	myOutterFunc();
//	return 0;
//}