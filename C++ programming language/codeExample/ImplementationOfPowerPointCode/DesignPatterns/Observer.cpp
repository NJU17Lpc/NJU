#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
������һ����Ҫ�ĳ���A����һ�����仯����Ҫ֪ͨӦ���������ĳ���
������Ӧ�ó����ֲ���һֱ�����ؿ��������Ҫ����A�����Լ������黹æ����������Ҫ�鷳CPU�л��߳�/����

��Ҫһ�ѹ۲��ߣ�������Ҫ���ӳ���A��״��
Ҳ��Ҫһ��Ŀ�꣬���Ŀ���ǹ۲��߹�ע�Ķ�����Ҫ�ܹ�����֪ͨ��Щ�۲���

*/

/*
�۲���ģʽ��һ�ֶ�����Ϊ��ģʽ
ÿ��һ������״̬�����ı�ʱ������������󶼵õ�֪ͨ�����Զ�����

д���ģʽ��ע��SubjectҪ��һ��observers����Ҫʵ��attach, detach, notify
	Observerֻ��Ҫʵ��update�ӿ�
��ʵ���庯�����Բ�ͬ������è���У���response����update����ͬ�Ķ����в�ͬ����response

�ŵ㣺
ʵ�ֱ�ʾ��������߼���ķ���
�۲�Ŀ��͹۲���֮�佨��һ����������
֧�ֹ㲥ͨ��
���Ͽ���ԭ��

ȱ�㣺
���һ���۲�Ŀ���кܶ�ֱ�ӻ��߼�ӵĹ۲��ߣ�ȫ��֪ͨ��Ҫ���ܶ�ʱ��
�۲��ߺ͹۲�Ŀ��֮����ܻ�ѭ������������
�۲���ֻ֪���仯�ˣ�����֪����ô�仯��

���ã�
һ������ģ���У�һ��������������һ�����棬һ������ı�������ܶ����ı䣬ȴ��֪���ж��ٶ���Ҫ�ı�
����֪ͨ�������󣬵�����֪��������˭������һ��������

���ã�
�¼�����ģ��
	subject:event source    observer:event listener    notify����Ϣ:event object
�ܶ��漰һ��һ����һ�Զ�Ķ��󽻻�������������ʹ�ù۲���ģʽ

���ģʽ������չ���Ϳ�����MVCģʽ
	subject:model	observer:view	controller:�н���
*/

class IObserver {
public:
	virtual void Update(double price) = 0;
};

class ConcreteObserver :public IObserver {
public:
	void Update(double new_price) {
		price = new_price;
		cout << m_name << " has known the price has changed to : " << to_string(price) << endl;
	}
	ConcreteObserver(string name):m_name(name){}
private:
	string m_name;
	double price;
};


class ISubject {
public:
	virtual void Attach(IObserver*) = 0;
	virtual void Detach(IObserver*) = 0;
	virtual void Notify() = 0;

};

class ConcreteSubject:public ISubject {
public:
	ConcreteSubject():m_price(10){}
	void setPrice(double price) { m_price = price; }
	void Attach(IObserver* observer){
		m_observer.push_back(observer);
	}
	void Detach(IObserver* observer) {
		auto it = m_observer.begin();
		for (; it != m_observer.end();) {
			if ((*it) == observer) {
				//ɾ����ʱ��Ҫע��Ҫ�����������ظ�ֵ
				it = m_observer.erase(it);
			}
			else {
				++it;
			}
		}
	}
	void Notify() {
		for (auto it = m_observer.begin(); it != m_observer.end(); ++it) {
			(*it)->Update(m_price);
		}
	}
private:
	vector<IObserver*> m_observer;
	double m_price;
};

//int main() {
//	IObserver* lpc = new ConcreteObserver("������");
//	IObserver* asuka = new ConcreteObserver("ի�ٷ���");
//	IObserver* erika = new ConcreteObserver("������滨");
//	IObserver* kaki = new ConcreteObserver("��ϲң��");
//	ConcreteSubject* priceChangeSubject = new ConcreteSubject();
//	priceChangeSubject->Attach(lpc);
//	priceChangeSubject->Attach(asuka);
//	priceChangeSubject->Attach(erika);
//	priceChangeSubject->Attach(kaki);
//	priceChangeSubject->setPrice(20);
//	priceChangeSubject->Notify();
//	cout << endl;
//	priceChangeSubject->Detach(lpc);
//	priceChangeSubject->setPrice(30);
//	priceChangeSubject->Notify();
//	return 0;
//}