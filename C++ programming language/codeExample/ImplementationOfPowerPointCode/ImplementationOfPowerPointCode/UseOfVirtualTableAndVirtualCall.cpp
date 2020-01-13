#include <iostream>
using namespace std;

/*
1�������麯�����ú��麯����Ĳ鿴
2�����Դ������麯������麯��֮����໥����
*/
class A {
public:
	//!!!!!!!!!!��Ҫ
	//A ����������û�ж�̬���ã���Ϊ���캯�����֮�󣬲�������ʹ�ö���
	//�����ڹ������ھ�̬����
	A() {
		cout << "A() constructor, call virtual f():";
		f(); 
	}
	virtual void f() {
		cout << "A f()" << endl;
	}
	virtual void g() {
		cout << "A g()" << endl;
	}

	//���麯��h()���ڲ������麯��ʱ��̬���ã����÷��麯��ʱ��̬����
	//�о����Ӧ��������״̬����������ͨ����������飬����ͷ���
	void h() {
		cout << "non-virtual A h(), call virtual f(), non-virtual k()  " << endl;
		f();
		k();
	}
	void k() {
		cout << "A k()" << endl;
	}
	virtual void m() {
		cout << "A m()" << endl;
	}
private:
	int m_x;
	int m_y;
};

class B :public A {
public:
	B() {}
	virtual void f() {
		cout << "B f()" << endl;
	}
	void h() {
		cout << "B k()" << endl;
	}
	void k() {
		cout << "B k()" << endl;
	}

	//!!!!!!!!!!����Ƚ���Ҫ
	//�麯��m()�����÷��麯�������õ��������Լ���k()�������Ǹ����k()
	//��Ϊ����麯������������һ��B* const this
	//���Լ�ʹ�ǵ��÷��麯����Ҳ�ǵ���this->k()
	virtual void m() {
		cout << "virtual B m(), call non_virtual k()" << endl;;
		k();
	}
private:
	int m_z;
};

//int main() {
//
//	A a;
//	B b;
//	A* p;
//	//p ָ����󣬶� ���� ���ڴ�ռ���ָ�룬ָ���麯����
//	//������debugģʽ�²鿴_vfptr��Ӧ���麯����
//
//	//����麯��������ΪA::f  A::g��A::h�����麯���������麯������
//	p = &a;
//	p->f();//A f()
//
//	//����麯��������ΪB::f A::g
//	//��Ϊf()��B�������أ���g()û�����أ�ʹ�õ��Ǹ����g()
//	p = &b;
//	p->f();//B f()
//	p->g();//A g()
//	p->h();
//	cout << endl;
//
//	p->m();
//	cout << endl;
//
//	return 0;
//}