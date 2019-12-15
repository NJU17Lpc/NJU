#include <iostream>
#include <string>
using namespace std;
/*
�ڹ��캯����ʹ�ó�Ա��ʼ����ȡ����ֵ������Ч�ʱȽϸ�
���¼������ͱ���ʹ�ã�const/reference/�����Ա/����Private

�������ݳ�Ա̫��ʱ����ô���ͻή�Ϳ�ά����
*/


//�����캯�����Զ�����
class A {
public:
	A() { cout << "normal" << endl; }
	A(int i) { cout << "int " << i << endl; }
	A(const char* p) { cout << "char* p " << p << endl; }
};

//����Ա��ʼ����
//��Ա��ʼ���б����ڶ������ݵ�ͬʱ��ֵ�����캯�����ȶ����ֵ
//��Щ��������Ҫ��Ա��ʼ���б�
//��Ա��ʼ���б��������ݳ�Ա��!!!����˳��!!!(ע��͹������г�ʼ��˳���޹�)�������ڹ��캯�����д���֮ǰ����
//��˲�Ҫ�ô����ں���ĳ�Ա����ʼ��������ǰ��ĳ�Ա
/*
��Ҫʹ�ó�ʼ����Ա�б������
1��Ҫ��ʼ�������ݳ�Ա�Ƕ���
2��Ҫ��ʼ��const�������Ա
3����ʼ�����ó�Ա����
4�������ʼ������˽�г�Ա
*/

//����1����ʼ�����󣬶�������Ĭ�Ϲ���������Ҫ
class TempC {
public:
	TempC(int, int) {
		cout << "this is TempC" << endl;
	}
	TempC() {
		cout << "this is TempC default" << endl;
	}
private:
	int a;
	int b;
};


class B {
public:
	B(int) {
		//�������������������TempCĬ�Ϲ��캯��
		//�����TempC������д���Ǹ�Ĭ�Ϲ��캯��ȥ�����ͻᱣ��
		cout << "this is B without tempc init" << endl;
	}
	B() : tempc(1, 1) {
		//�ڳ�ʼ����Ա�б��ʱ�� tempc ���ȱ���ʼ��
		cout << "this is B" << endl;
	}
private:
	TempC tempc;//��������
};

//����2/3,��ʼ��const��&����
class D {
public:
	//���������������Ϊ���ú�const���͵����ݱ���Ҫ���ڳ�ʼ����Ա�б���
	/*D(){
		a = 3; b = 4;
	}*/

	//�����������û����
	//˳����һ�£���int&��ֵ�����ǳ�������������const int&��ֵ�������ͱ�������������
	D(int e):a(1),b(e),c(e),d(1){
		cout << a << " " << b << " " << c << " " << d << endl;
	}

private:
	const int a;
	int& b;
	const int c;
	const int d;
};

//����3�������ʼ������˽�г�Ա
class E {
public:
	E(int x) { m_x = x; cout << "this is E with x:" << x << endl; }
private:
	int m_x;
};

class E_son :E {
public:
	E_son(int x):E(x) {
		//�����ڹ��캯���ڲ����ø��๹����������ʼ������˽�г�Ա
		//E(x);
	}
};

//int main() {
//
//	//�⼸������A(int i)
//	A a11 = A(1);
//	A a12(1);
//	A a13 = 1;
//	A a14 = a13;//Ĭ�Ͽ������캯��
//	cout << endl;
//	//�⼸������A()
//	A a21 = A();
//	A a22;
//	A a23();//ppt ˵������������ʵ����û��
//	cout << endl;
//	//�⼸������A(char*)//ppt�����⣬������Ӧ��д��A(const char* p)
//	A a31 = A("abcd");
//	A a32("abcd");
//	A a33 = "abcd";
//	cout << endl;
//	//��������Ĵ�A()
//	A a4[4];
//	cout << endl;
//	//��������������ݵ���
//	A a5[5] = { A(), A(1), A("abcd"), 2, "xyz" };
//	cout << endl;
//
//	//���Գ�Ա��ʼ����
//	B b1;
//	cout << endl;
//	B b2(1);
//	cout << endl;
//	D d = 2;
//	cout << endl;
//	E e = 7;
//	cout << endl;
//	return 0;
//}