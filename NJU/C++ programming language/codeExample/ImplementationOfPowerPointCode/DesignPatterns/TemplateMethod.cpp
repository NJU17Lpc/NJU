#include <iostream>
#include <string>
using namespace std;

/*
现在需要参加阿里和腾讯校招，校招流程都差不多：宣讲会--简历--面试--发offer

模板方法动机：
我们想要抽象类中，用具体的方法实现部分逻辑；然后声明一些抽象方法，便于子类实现剩余的逻辑，因此不同的子类有不同的实现
从而相同的代码在父类，不同的代码在子类，这就是基于继承的代码复用

分析：
只有类的继承，没有对象关联，于是他是类的行为型模式，不是对象的
通常开发中，一个设计师给出算法轮廓，其他设计师负责实现算法各个逻辑
模板方法鼓励继承，是体现继承优势的模式

优点：
在一个类中抽象定义算法，另一个类中实现细节处理
是一种代码复用的基本技术
会导致一种反向的控制结构，通过父类调用其子类的操作，符合开闭原则

缺点：
每个不同的实现都需要定义一个子类，类的个数增加
	但这一点另一面更符合单一职责，类内聚性更好了

适用：
实现算法不变部分，将可变行为留给子类实现
各个子类中公共行为需要提取出来，集中到公共父类，来避免代码重复
对复杂算法进行分割，不变的部分设计为模板方法和父类具体方法
控制子类扩展

应用：
框架设计，确保父类控制处理流程的逻辑顺序，比如框架初始化

扩展：
好莱坞原则：
子类不调用父类方法，而是通过覆盖父类，实现具体业务
	don't call us, we'll call you
	体现在：子类不需要父类，而通过父类来调用子类，父类控制整个过程

钩子方法：
用于让子类控制父类的行为
可以在钩子方法中定义默认的实现，如果子类不覆盖钩子，则执行父类的默认实现
复杂一点的钩子方法可以返回bool类型，来判断是否执行某一个方法
（自己理解）
钩子经常是一些Bool判断方法，子类可以动态覆盖，从而影响父类的判断：本来父类默认的bool是这种判定方式，子类改成了另一种判定方式
于是钩子一般得虚函数
*/

/*
写的时候注意
需要有模板方法，固定流程
要有基本方法：具体方法（虚和非虚好像都行），抽象方法（纯虚），钩子方法（好像很多都是bool判断，不太清楚）
*/

class Company {

public:
	virtual ~Company(){}

	//校园招聘
	void Recurit() {
		cout << "-----开始校招-----" << endl;
		CareerTalk();
		ReceiveResume();
		Interview();
		Offer();
		cout << "-----结束校招-----" << endl;
	}

	//宣讲会
	void CareerTalk() {
		cout << "公司开始校招宣讲会" << endl;
	}
	//接收简历
	void ReceiveResume() {
		cout << "公司开始接收简历" << endl;
	}
	//面试
	virtual void Interview() = 0;
	//发放offer
	virtual void Offer() = 0;
};

class Alibaba :public Company {
public:
	virtual void Interview() override {
		cout << "阿里巴巴：一面，二面，三面" << endl;
	}
	void Offer() override {
		cout << "阿里巴巴：白菜价offer：30W" << endl;
	}
};

class Tencent :public Company {
public:
	virtual void Interview() override {
		cout << "腾讯：一面，二面" << endl;
	}
	void Offer() override {
		cout << "腾讯：白菜价offer：25W" << endl;
	}
};

//int main() {
//	Company* company1 = new Alibaba();
//	company1->Recurit();
//	Company* company2 = new Tencent();
//	company2->Recurit();
//	return 0;
//}