#include <iostream>
using namespace std;

/*
���Բ�Ҫ���¶���̳ж�����ȱʡ����ֵ
*/
class A {
public:
	virtual void f(int x = 0) = 0;
};

class B :public A {
public:
	virtual void f(int x = 1) {
		cout << x;
	}
};

class C :public A {
public:
	virtual void f(int x) { cout << x; }
};

int main() {
	A* p_a;
	B b;
	p_a = &b;
	//��������class B ��f(int x=1)�������ú���Ĭ��ֵ��Ȼ���ӡ�������0
	//��ΪB�����У�ֻ��¼�麯������ڵ�ַ������¼Ĭ�ϲ���
	p_a->f();

	cout << endl;

	A* p_a1;
	C c;
	p_a1 = &c;
	p_a1->f();

	/*
	�ղŵ�p_a p_a1 ����������ָ�����ʲô�������ǵľ�̬���ͻ���A
	virtual ������Ȼ�Ƕ�̬�󶨵�
	��ȱʡ����ֵҲ�Ǿ�̬�󶨵ģ����Դ�����Ǹ���A��ȱʡ����ֵ

	Ϊʲô�������C++��
	���ȱʡֵ��̬�󶨣�����������ӣ�Ϊ���ٶȺ�ʵ���ϵļ����ԣ�����������
	
	*/

	return 0;
}