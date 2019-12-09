#include <iostream>
#include <string>
using namespace std;
/*
现在有很多大学生找房子租，但是自己去找挺难找的，然后就去找各种黑中介啊啊啊
所以现在需要三方对象：租房的人，黑中介，有房的大佬
租房的人和有房的大佬之间只要互相传送信息就好了

*/


/*
这个中介者模式好像是说，中介者使得各个对象不需要显式相互引用
原来每个对象都要知道其他所有对象，才可以进行相互通讯，于是整个系统就成了一个整体
因此加了一个中介者进行良好的通讯，结构清晰

优点：
减少子类生成
将各个对象解耦，可以独立改变和复用各个mediator和colleague类
简化对象协议，关注交互

缺点：
控制集中，使得中介者复杂度很高，可能难维护
*/

/*
写中介者时要注意
中介者持有甲方乙方的接口，需要进行注册，以及转发判断发给谁
甲方乙方需要持有中介者的接口，也要进行注册，发信息直接发给中介者
*/

/*
碰到一个奇怪的事情，这个超前引用出问题
之前我是
class Mediator;
class Person{ 
protected: 
	Mediator m_mediator;
}
class Mediator{...}
这样就说我这个Mediator没定义

现在我就是改成Person在前面
然后Mediator里面就把person当一个参数用
就没有超前引用的错误
回去看一下
*/

class Person;//超前引用

class Mediator {
public:
	//mediator就让他协调AB双方吧
	virtual void setA(Person* p) { m_A = p; }
	virtual void setB(Person* p) { m_B = p; }
	//这个setA,setB其实也就是register操作
	virtual void Send(string msg, Person* person) = 0;
	Mediator() {}
protected:
	Person* m_A;
	Person* m_B;
};

class Person {
protected:
	//房东和租房者都需要一个中介
	Mediator* m_mediator;
public:
	void setMediator(Mediator* mediator) { m_mediator = mediator; }
	virtual void SendMsg(string msg) = 0;
	virtual void GetMsg(string msg) = 0;

};

class Renter :public Person {
public:
	void SendMsg(string msg){
		cout << "租客发出信息：" << msg << endl;
		m_mediator->Send(msg, this);
	}
	void GetMsg(string msg){
		cout << "租客收到消息：" << msg << endl;
	}
};

class DaLao :public Person {//有房子的大佬就是不一样
public:
	void SendMsg(string msg) {
		cout << "房东大佬发出信息：" << msg << endl;
		m_mediator->Send(msg, this);
	}
	void GetMsg(string msg) {
		cout << "房东大佬收到消息：" << msg << endl;
	}
};



class blackHouseMediator:public Mediator {
public:
	void setA(Person* p) { m_A = p; }
	void setB(Person* p) { m_B = p; }


	void Send(string msg, Person* person) {
		cout << "中介转发消息" << endl;
		//这个if else一看就很丑，于是也是这个中介者模式的缺点
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
//	//中介和学生的注册是双方的，中介和房东注册也是双方的
//	student->setMediator(stupidMediator);
//	owner->setMediator(stupidMediator);
//	stupidMediator->setA(student);
//	stupidMediator->setB(owner);
//	student->SendMsg("老子要一套海景别墅，一个月房租两位数以内那种。");
//	owner->SendMsg("我有一个公共厕所，一个月两千，住不住");
//	student->SendMsg("卧槽无情");
//	owner->SendMsg("奥里给");
//	return 0;
//}