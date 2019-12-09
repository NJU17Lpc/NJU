#include <iostream>
#include <string>
using namespace std;
/*
���ڲ��Լ̳�ʱ���鷽���ͷ��鷽������ʱ����̬�󶨺;�̬�󶨵Ľ��
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
//	//���鷽����int getA()�������û��෽����û�ܶ�̬��
//	//�鷽����virtual int getB()�����������෽����ʵ���˶�̬��
//	cout << "b1: " << b1->getA() << " " << b1->getB() << endl;
//	Base b2(2, 2);
//	//��ȥ��̬�����Ļ�������ǵ���������ķ���
//	cout << "b2: " << b2.getA() << " " << b2.getB() << endl;
//	Derived b3(3, 3);
//	cout << "b3: " << b3.getA() << " " << b3.getB() << endl;
//
//	return 0;
//}