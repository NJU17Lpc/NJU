#include <iostream>
using namespace std;

/*
�о�����м���
1���麯������override
2��final����override
3��override�������Ͳ�����Ҫƥ�䣬����const����ҲҪƥ��
*/
class B {
public:
	virtual void f1(int) const;
	virtual void f2();
	void f3();
	virtual void f5(int) final;
};

class D :public B {
public:
	void f1(int) const override;//OK,������f1����ƥ�䣬ע����Ҫ��const��ǣ��Ƚ�const�ǿ����������غ�����
	//void f2(int) override;//�Ҳ�������f2(int)�Ļ��ຯ��
	//void f3() override;//f3�����麯����ע�ⲻ�ܸ����麯��
	//void f4() override;//����û�н�f4�ĺ���
	//void f5(int);//�����У�f5�Ѿ�����Ϊfinal������override
};