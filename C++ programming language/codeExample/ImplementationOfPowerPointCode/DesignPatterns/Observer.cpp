#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
现在有一段重要的程序A，他一发生变化就需要通知应用中其他的程序
其他的应用程序又不能一直主动地看着这个重要程序A，他自己的事情还忙不过来，又要麻烦CPU切换线程/进程

需要一堆观察者，他们想要监视程序A的状况
也需要一个目标，这个目标是观察者关注的对象，需要能够自行通知这些观察者

*/

/*
观察者模式是一种对象行为型模式
每当一个对象状态发生改变时，相关依赖对象都得到通知并被自动更新

写这个模式，注意Subject要有一堆observers，需要实现attach, detach, notify
	Observer只需要实现update接口
其实具体函数可以不同，比如猫鼠狗中，用response代替update，不同的动物有不同样的response

优点：
实现表示层和数据逻辑层的分离
观察目标和观察者之间建立一个抽象的耦合
支持广播通信
符合开闭原则

缺点：
如果一个观察目标有很多直接或者间接的观察者，全部通知到要花很多时间
观察者和观察目标之间可能会循环依赖，崩溃
观察者只知道变化了，而不知道怎么变化的

适用：
一个抽象模型中，一个方面依赖于另一个方面，一个对象改变会引发很多对象改变，却不知道有多少对象要改变
必须通知其他对象，但不必知道对象是谁；创建一个触发链

常用：
事件处理模型
	subject:event source    observer:event listener    notify的信息:event object
很多涉及一对一或者一对多的对象交互场景，都可以使用观察者模式

这个模式向外扩展，就可以做MVC模式
	subject:model	observer:view	controller:中介者
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
				//删除的时候要注意要给迭代器返回赋值
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
//	IObserver* lpc = new ConcreteObserver("刘鹏程");
//	IObserver* asuka = new ConcreteObserver("斋藤飞鸟");
//	IObserver* erika = new ConcreteObserver("生田绘梨花");
//	IObserver* kaki = new ConcreteObserver("贺喜遥香");
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