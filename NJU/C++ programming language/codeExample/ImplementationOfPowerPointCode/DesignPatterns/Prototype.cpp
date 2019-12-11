#include <iostream>
#include <string>
using namespace std;

/*
今年下半年，中美合拍，六爷，猴子，拔毛，自我复制，懂了吧hh

*/

/*
动机：
1、想要克隆出多个和原型一模一样的对象
2、有些对象创建过程很复杂，原型模式给出一个原型对象指明需要创建对象的类型，然后复制这个对象，从而创建出很多同类型的对象
就是拷贝自己，实现创建，不用了解创建细节

应用：
邮件复制----浅拷贝
ctrl c+v 获得两个类型相同但是内存地址不同的对象
Spring中，用户采用原型模式，创建新的bean实例，每次获取克隆的新实例。修改时对原有实例不造成任何影响

优点：
1、创建新对象实例很复杂时，原型模式可以简化对象的创建过程
通过已有实例提高新实例创建效率
2、可以动态增加或减少产品类
3、提供简化的创建结构
4、可以用深克隆，保存对象状态

缺点：
1、需要为每一个类配备一个克隆方法，对原有的类进行改造，其实违背了开闭原则
2、深克隆会需要编写较为复杂的代码

适用环境：
1、创建新对象成本较大，直接复制原来的对象，只需要对属性稍微修改就好了
2、如果系统要保存对象的状态，同时对象状态变化很小，可以原型+备忘录模式；如果对象状态变化很大，状态模式更好
3、需要避免使用分层次的工厂类来创建分层次的对象，并且类的实例对象只有一个或者很少几个组合状态，这时候复制比构造方便

扩展：
相似对象的复制：
	原型模式获得相同对象后，可以对属性进行修改，从而获取需要的对象
	必须许多学生，专业、学校等很多信息都一样，只是性别、姓名、年龄不同

*/
/*
写的时候注意
1、在一个已有对象里面，将通过拷贝自己（一般是拷贝构造函数），返回new之后的结果，来实现创建的过程
2、抽象原型类有Clone()接口，具体原型类实现具体Clone()方法
3、客户类只要直接实例化或者工厂创建，再通过调用实例的Clone()获得很多相同的对象
4、实现深克隆比较复杂
*/
class Monkey {
public:
	Monkey(){}
	virtual ~Monkey(){}
	virtual Monkey* Clone() = 0;
	//战术后仰
	virtual void tacticalBack() = 0;
};

//六爷类
class SixLittleAgeChild :public Monkey {
public:
	SixLittleAgeChild(string name) { m_strName = name; }
	~SixLittleAgeChild()
	{
		cout << "delete : " << m_strName << endl;
	}

	SixLittleAgeChild(const SixLittleAgeChild& other) {
		m_strName = other.m_strName;
	}

	SixLittleAgeChild* Clone() override {
		return new SixLittleAgeChild(*this);
	}

	void tacticalBack() override {
		cout << m_strName << "说：“什么叫国际影星啊”" << endl;
	}

private:
	string m_strName;
};

int main() {
	Monkey* monkey = new SixLittleAgeChild("六小龄童");
	Monkey* monkey1 = monkey->Clone();
	Monkey* monkey2 = monkey1->Clone();

	monkey->tacticalBack();
	monkey1->tacticalBack();
	monkey2->tacticalBack();


	return 0;
}