#include <iostream>
using namespace std;

/*
�������⣺
������������������
1���Ի��๹�캯��/���������ĵ��ô���
2���Ի������ݳ�Ա�Ĵ洢���ţ�Ŀ�������Ҫ��������йأ�
*/


//���μ��ɣ��Գ�ͻ�Ĳ��֣�Ҫ����ָ��
//��ͻ�Ĺ������֣���ÿ�������б���һ�ݸ���
class A {
public:
	A() {
		cout << "A()" << endl;
	}
protected:
	int m_a;
};

class B :public A {
public:
	B() {
		cout << "B()" << endl;
	}
protected:
	int m_b;
};

class C :public A {
public:
	C() {
		cout << "C()" << endl;
	}
protected:
	int m_c;
};

//A()�ṹ�����Σ����Ի���������ͬ��A���󸱱����̳�
class D :public C, public B {
public:
	D() {
		cout << "D()" << endl;
	}

	void setA(int a) {
		//m_a = a;//������ͻ����������ȷ
		B::m_a = a;
		C::m_a = a;
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};


/*
Ϊ�˽����̳е�������ͻ���������ݵ����⣬ʹ����̳У�
��������������ֻ����  һ��  ��ӻ���ĳ�Ա

������Ŀ��
1����ĳ����������������ŵԸ�⹲�����Ļ���
2�����������Ļ���ͳ�Ϊ����࣬�����VA���������
3����������£���������࣬�ڼ̳���ϵ�г����˶��ٴ�
���������У���ֻ����һ�������ĳ�Ա

*/

class VA {
public:
	VA() {
		cout << "VA()" << endl;
	}
protected:
	int m_a;
};

class VB :virtual public VA {//��̳�
public:
	VB() {
		cout << "VB()" << endl;
	}
protected:
	int m_b;
};

class VC :virtual public VA {//��̳�
public:
	VC() {
		cout << "VC()" << endl;
	}
protected:
	int m_c;
};


//�̳�ʱ������˳�򣬾����˹��������õ�˳��
//���������˳�����: VA, VC, VB, VD
//VAֻ����һ��
class VD :public VC, public VB {
public:
	VD() {
		cout << "VD()" << endl;
	}
	void setA(int a) {
		m_a = a;//���ʱ��Ͳ����г�ͻ�������û�б���
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};

/*
ppt�ϵ�ע�� ��
1�������Ĺ��캯������������������Ĺ��캯������
����˵���Ǹ������ȱ��̳У���ô����������������๹�캯��
2�������Ĺ��캯�������ڷ������Ĺ��캯��ִ��
����˵����ʹ�Ƿ�������ȱ��̳У���ôҲ���ȹ��������Ķ���
���������˳�����: VA,VC,A,VB,VE
*/

class VE :public VC, public A, public VB {
public:
	VE() {
		cout << "VE()" << endl;
	}
	void setA(int a) {
		VC::m_a = a;//���ʱ��Ͳ����г�ͻ�������û�б���
	}
	void setB(int b) {
		m_b = b;
	}
	void setC(int c) {
		m_c = c;
	}
	void setD(int d) {
		m_d = d;
	}

private:
	int m_d;
};

//int main() {
//	D d; 
//	cout << endl;
//	VD vd;
//	cout << endl;
//	VE ve;
//	return 0;
//}