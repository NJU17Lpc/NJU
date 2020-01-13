#include <iostream>
#include <string>
using namespace std;
/*
�����кܶ��ѧ���ҷ����⣬�����Լ�ȥ��ͦ���ҵģ�Ȼ���ȥ�Ҹ��ֺ��н鰡����
����������Ҫ���������ⷿ���ˣ����н飬�з��Ĵ���
�ⷿ���˺��з��Ĵ���֮��ֻҪ���ഫ����Ϣ�ͺ���

���������ģʽ�Ķ�������
ϵͳ�ṹ���ӣ�һ����������������ܶ�������һ������仯����Ҫ���ٺܶ����
����������Բ�
ϵͳ��չ�Ե�

����������ʹ�ö���ֻ����һְ��
Ϊ�˼��ٶ�������֮�临�����ù�ϵ������ϣ�������Ҫ�н���

*/


/*
����н���ģʽ������˵���н���ʹ�ø���������Ҫ��ʽ�໥����
ԭ��ÿ������Ҫ֪���������ж��󣬲ſ��Խ����໥ͨѶ����������ϵͳ�ͳ���һ������
��˼���һ���н��߽������õ�ͨѶ���ṹ����

�ŵ㣺
������������
���������������Զ����ı�͸��ø���mediator��colleague��
�򻯶���Э�飬��ע����

ȱ�㣺
���Ƽ��У�ʹ���н��߸��ӶȺܸߣ�������ά��

���ã�
ϵͳ�ж���֮����ڸ������ù�ϵ
һ��������Ҫ�������õĶ���ֱ��ͨ�ţ���Ϊͨ����˫���ģ�������Ϊ������Ϊģʽ��observerģʽ��������observerֻҪһ��֪ͨ
��Ҫһ���м����װ��������Ϊ���ֲ������̫������

Ӧ�ã�
GUI֮��Ľ���ͨ��
MVC�п�����controller��Ϊ�н��ߣ�����view��model֮��Ľ���
*/

/*
д�н���ʱҪע��
�н��߳��м׷��ҷ��Ľӿڣ���Ҫ����ע�ᣬ�Լ�ת���жϷ���˭
�׷��ҷ���Ҫ�����н��ߵĽӿڣ�ҲҪ����ע�ᣬ����Ϣֱ�ӷ����н���
���������໥����

��ʵע�᲻һ��ֻ�м���˫����������һ����List��������Ҫһ������������member����
����һ�������ң�����һ���û�����sendText(to, content), receiveText(from, content)
�����Ҿ���һ���н飬������register,sendText(from, to, content)
�߼����û������и߼���sendText
*/

/*
����һ����ֵ����飬�����ǰ���ó�����
֮ǰ����
class Mediator;
class Person{ 
protected: 
	Mediator m_mediator;
}
class Mediator{...}
������˵�����Mediatorû����

�����Ҿ��Ǹĳ�Person��ǰ��
Ȼ��Mediator����Ͱ�person��һ��������
��û�г�ǰ���õĴ���
��ȥ��һ��
*/

class Person;//��ǰ����

class Mediator {
public:
	//mediator������Э��AB˫����
	virtual void setA(Person* p) { m_A = p; }
	virtual void setB(Person* p) { m_B = p; }
	//���setA,setB��ʵҲ����register����
	virtual void Send(string msg, Person* person) = 0;
	Mediator() {}
protected:
	Person* m_A;
	Person* m_B;
};

class Person {
protected:
	//�������ⷿ�߶���Ҫһ���н�
	Mediator* m_mediator;
public:
	void setMediator(Mediator* mediator) { m_mediator = mediator; }
	virtual void SendMsg(string msg) = 0;
	virtual void GetMsg(string msg) = 0;

};

class Renter :public Person {
public:
	void SendMsg(string msg){
		cout << "��ͷ�����Ϣ��" << msg << endl;
		m_mediator->Send(msg, this);
	}
	void GetMsg(string msg){
		cout << "����յ���Ϣ��" << msg << endl;
	}
};

class DaLao :public Person {//�з��ӵĴ��о��ǲ�һ��
public:
	void SendMsg(string msg) {
		cout << "�������з�����Ϣ��" << msg << endl;
		m_mediator->Send(msg, this);
	}
	void GetMsg(string msg) {
		cout << "���������յ���Ϣ��" << msg << endl;
	}
};



class blackHouseMediator:public Mediator {
public:
	void setA(Person* p) { m_A = p; }
	void setB(Person* p) { m_B = p; }


	void Send(string msg, Person* person) {
		cout << "�н�ת����Ϣ" << endl;
		//���if elseһ���ͺܳ�����Ҳ������н���ģʽ��ȱ��
		if (person == m_A) {
			m_B->GetMsg(msg);
		}
		else {
			m_A->GetMsg(msg);
		}
	}
};
//int main() {
//	Person* student = new Renter();
//	Person* owner = new DaLao();
//	Mediator* stupidMediator = new blackHouseMediator();
//	//�н��ѧ����ע����˫���ģ��н�ͷ���ע��Ҳ��˫����
//	student->setMediator(stupidMediator);
//	owner->setMediator(stupidMediator);
//	stupidMediator->setA(student);
//	stupidMediator->setB(owner);
//	student->SendMsg("����Ҫһ�׺���������һ���·�����λ���������֡�");
//	owner->SendMsg("����һ������������һ������ǧ��ס��ס");
//	student->SendMsg("�Բ�����");
//	owner->SendMsg("�����");
//	return 0;
//}