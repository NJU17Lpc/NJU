#include <iostream>
using namespace std;


/*
C++ ���������ڹ���
1�������������ƣ����͵������
2��Ҫ�������ڼ̳ж��������ƣ�������Ϊ���Ʋ��ҵ�ʱ��������벻������Ϊ

�Ƚ�һ���麯���ͷ��麯��
1��һ���麯��
	�������̳к����ӿ�
	���Լ̳�ȱʡʵ��
2�����麯��
	����ͬʱ�̳нӿں�ʵ�ִ���
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
//	d.mf1();//D:mf1() ûʲô����
//	//d.mf1(x);//����D:mf1()������B:mf1(int)
//	d.mf2();//B:mf2() ûʲô���⣬�Ͼ�Dû�и���
//	d.mf3();//D:mf3() ûʲô���⣬D�и�����mf3()
//
//	//����������ӣ���ʾ��Derived�еĺ��������������ڸ����Ͳ�ͬ��Base����
//	//d.mf3(x);//������ΪD:mf3()�ڸ���B:mf3(double)����Ϊ���Ʋ��ң��ҵ���ֹͣ�ˣ�û��ȥȷ�ϲ����Ƿ�ƥ�䣬
//	//��ô��Ƶ�ԭ���ǣ�Ϊ�˷�ֹ�Ӻ�Զ��base class �̳����غ���
//	
//	//���������ܻ���취�Ʒ�������Ϊ
//	//������D�м���using Base::mf3;using Base::mf1;
//	//��������ע�͵������䶼��������ʹ����
//
//	//��ʵusingҲ���Ǻܺã������ת������
//	//�������������ע����ֻ��ע�͹�
//	//virtual void mf1() {
//	//	Base::mf1();
//	//}
//	return 0;
//}