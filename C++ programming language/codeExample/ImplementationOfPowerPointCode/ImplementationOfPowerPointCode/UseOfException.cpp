#include <iostream>
#include <exception>
using namespace std;

/*
catch ���Բ���
1�����ͣ��쳣�����ͣ�ƥ�����ͺ�������һ��
2���������洢�쳣���󣬿���ʡ��
һ��try������Ը����catch�����ڲ���ͬ���͵��쳣������

����׳����쳣�����ڵ�������û�б���������ϵͳabort����

�����ϳ��˻�����������ת����catch����ȷƥ�䣬��������ʽת��
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

//�����쳣�����Ƕ��
//����ƥ��ʱ���ڲ��Ȳ����쳣
void g(int i) {
	try {
		throwFunc(i);
	}
	catch (int) {
		//����޲���throw���Ὣ���񵽵��쳣�����׳�ȥ��������f�����ٴ���һ��
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




//�Զ����쳣�࣬ʹ������������
//�м̳й�ϵʱ��˳�����Ҫ�ˣ���Ϊ�л�����������ת��
class  MyExceptionBase{};

class MyExceptionDerived:public MyExceptionBase{};

void myExceptionThrow(MyExceptionBase& e) {
	//���������catch˳��
	//�������Base�쳣��catch��Ҳ��base
	//�������Derived�쳣��catch�ľ���derived
	//��Ϊthrow���õ���!!!!��������!!!!���������̬���;���catch����
	throw e;
}

void myExceptionCatch() {
	MyExceptionDerived e;
	try {
		myExceptionThrow(e);
	}
	catch (MyExceptionDerived& e) {//��������쳣Ӧ��Ҫ����ǰ�沶��
		cout << "MyExceptionDerived" << endl;
	}
	catch (MyExceptionBase& e) {
		cout << "MyExceptionBase" << endl;
	}
	catch (...) {
		cout << "Normal catch" << endl;
	}

}

//�����쳣������exception
class myException1 :public exception {
public:
	//ע��һ��Ҫ�к����const
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