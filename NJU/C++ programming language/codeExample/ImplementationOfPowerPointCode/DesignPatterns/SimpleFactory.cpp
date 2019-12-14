#include <iostream>
#include <string>
using namespace std;

/*
������Ҫ��һ��֧�����������ò�ͬ��֧����ʽ��ʵ��
*/

/*
���壺
1���򵥹���ģʽ ���� ��̬����ģʽ
2���ഴ����ģʽ
3�����ݲ�ͬ�������ز�ͬʵ����ʵ������ͬ�ĸ���

����
1�������󴴽��Ͷ�����ҵ����룬����ϵͳ��϶�
2�����������Ǿ�̬��������ͨ������ֱ�ӵ���
�����п��԰Ѳ�������XML���棬�޸�����ʱ�Ͳ���Ҫ�޸Ĵ���
3������Ҫ֪��������ϸ��
4���������ְ�����

�ŵ㣺
1�������ฺ���жϣ��ͻ���ֻ��Ҫ���Ѳ����Ķ���
�������εõ��ָ�
2���ͻ��˲���Ҫ֪������������ֻ��Ҫ֪������
3�����������ļ��������ڲ��޸Ŀͻ��˴����ʱ���������������µĲ�Ʒ��

ȱ�㣺
1���������в�Ʒ�����߼���һ������������⣬����ϵͳ�ܵ�Ӱ��
2������ϵͳ����ĸ��������Ӹ��Ӷ�
3��ϵͳ��Ȼ�޸Ĳ������ף�������չ���ѣ�һ�������µĲ�Ʒ�ͱ����޸Ĺ����߼�
��Ʒ���ͺܶ��ʱ�򣬹����߼�����ڸ���
4����̬������ʹ�ù����޷��γɼ̳еĽṹ����չ�Բ�����

���ã�
1�����������������
2���ͻ���ֻ��Ҫ֪�������Ͷ������Ͷ�Ӧ��ϵ�������Ĵ���ϸ�ڣ�����������������Ͷ�����Ҫ֪��

Ӧ�ã�
1��JDK��java.text.DataFormat::getDataInstance()�������Բ�ͬ����ȡ��ͬ���͵Ľ��
2��Java���ܣ�����������ͬ�����㷨

��չ��
���԰ѹ����ľ�̬�������ŵ���Ʒ��ĳ������У��򻯹���ģʽ

���㣺
1��Υ������ԭ��
ϵͳ�����²�Ʒʱ��Ҫ�޸Ĺ����࣬���봦���߼�
�����Ʒ�͹�������Ϲ���
2�����Ի��ɹ�������ģʽ
*/

class IPayMethod {
public:
	virtual void pay() = 0;
};

class AliPay:public IPayMethod
{
public:
	void pay() override {
		cout << "use AliPay" << endl;
	}
};

class WeCharPay :public IPayMethod {
public:
	void pay() override {
		cout << "use WeChatPay" << endl;
	}
};

class CreditCardPay :public IPayMethod {
public:
	void pay() override {
		cout << "use CreditCardPay" << endl;
	}
};

class PayFactory {
public:
	static IPayMethod* getPayMethod(string method) {
		if (method == "ali") {
			return new AliPay();
		}
		else if (method == "wc") {
			return new WeCharPay();
		}
		else if (method == "cc") {
			return new CreditCardPay();
		}
		else {
			cout << "not a valid pay type" << endl;
			return NULL;
		}
	}
};

//int main() {
//	IPayMethod* method1 = PayFactory::getPayMethod("ali");
//	IPayMethod* method2 = PayFactory::getPayMethod("wc");
//	IPayMethod* method3 = PayFactory::getPayMethod("cc");
//	IPayMethod* method4 = PayFactory::getPayMethod("lpc");
//
//	method1->pay();
//	method2->pay();
//	method3->pay();
//	//method4->pay();
//
//
//	return 0;
//}