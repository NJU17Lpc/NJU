#include <iostream>
#include <string>
using namespace std;

/*
之前的工厂方法模式，创建的产品是同一个大类型的，只不过是委派不同的工厂去做不同的衍生产品
现在宝马公司不仅能做汽车，还能做自行车，自然不能只用工厂方法模式
现在工厂中的每个方法负责生产一种类型的产品，一个工厂多个方法在一起，生产一族的产品

当时写的时候，好像在父类里面的静态方法中，生成子类对象返回时，出了点问题，就是调用了子对象构造器之前，还没有定义子类
但是我在类中写声明，具体定义移到子类定义好之后再写，就没事了
需要看一下C++的初始化顺序

其实我抄的这个例子里面，我感觉他这个static方法来返回子类对象有点奇怪，作为demo直接动态绑定不就行了？？？
*/

/*
动机：
1、一般情况下，工厂方法够用，因为一个具体工厂对应一个具体产品
2、有时候，我们需要一个工厂，可以提供多个产品对象，而不是单一产品对象

产品等级结构：
1、就是产品的继承结构，抽象父类，具体子类
2、父类冰箱，子类海尔冰箱
产品族
1、同一个工厂生产的，位于 不同产品等级结构 中的一组产品
2、海尔工厂中，电视机、冰箱不是一个等级结构，于是在一个产品族

区别：
1、抽象工厂是各种工厂模式中，最为抽象和一般的形态
2、工厂方法针对同一个产品等级结构，抽象工厂面对多个产品等级结构

定义：
1、提供一个创建一系列相关或者相互依赖对象的接口，不需要指定具体的类
2、又叫Kit模式
3、对象创建型模式

实例：
1、海尔工厂
2、自定义数据库连接对象connection 和语句对象statement
factory里面就是createConntection(),createStatement()

优点：
1、隔离了具体类的生成，于是更换一个具体工厂比较容易，只要改变具体工厂的实例
2、高内聚，低耦合
3、有的系统软件需要根据当前环境决定其行为，因此，一个产品族多个对象需要一起工作时
抽象工厂可以保障客户端在使用同一个产品族中的对象
4、增加新的具体工厂和产品族很方便，不需要修改已有系统
符合开闭原则

缺点：
1、增加新的产品对象时，很难扩展抽象工厂来生产新种类的产品
这样需要涉及对抽象工厂所有子类的修改，不方便
2、开闭原则倾斜性：
增加新的工厂和产品族容易（注意，我理解的，增加产品族比如，将海尔大电视机换成小电视机）
增加新的产品等级结构麻烦

适用：
1、一个系统不应该依赖于产品类实例如何被创建、组合和表达的细节
2、系统中有许多产品族，每次只是用一个产品族
3、属于同一个产品族的产品在一起使用，这一点必须在设计的上下文体现出来
4、系统提供一个产品类的库，所有产品同样接口，于是客户端不依赖于具体实现

开闭原则的倾斜性：
1、增加新的产品族，只需要增加一个新的具体工厂就行，不需要修改已有代码
2、增加新的产品等级结构，需要修改所有工厂角色，包括抽象工厂类
	增加等级结构，理解为原来只需要生产电视和冰箱，现在又要增加空调

退化：
1、如果只存在一个产品等级结构，抽象工厂退化成工厂方法
2、工厂方法中，抽象工厂和具体工厂合并，提供一个统一的工厂来创建产品
并将创建对象的工厂方法设计为静态时
退化成简单工厂

*/

class ICar {
public:
	virtual string Name() = 0;
};

class IBike {
public:
	virtual string Name() = 0;
};

//////////////////汽车
class BenzCar :public ICar {
public:
	string Name() override{
		return "Benz Car";
	}
};

class BMWCar :public ICar {
public:
	string Name() override {
		return "BMW Car";
	}
};

class AudiCar :public ICar {
public:
	string Name() override {
		return "Audi Car";
	}
};

//////////////////自行车
class BenzBike :public IBike {
public:
	string Name() override {
		return "Benz Bike";
	}
};

class BMWBike :public IBike {
public:
	string Name() override {
		return "BMW Bike";
	}
};

class AudiBike :public IBike {
public:
	string Name() override {
		return "Audi Bike";
	}
};

///////////////////////////////工厂


class AbstractFactory {
public:
	enum Factory_type
	{
		BENZ_FACTORY,
		BMW_FACTORY,
		AUDI_FACTORY
	};

	virtual ICar* CreateCar() = 0;
	virtual IBike* CreateBike() = 0;
	static AbstractFactory* CreateFactory(Factory_type fac_type);
};

class BenzFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new BenzCar();
	}
	IBike* CreateBike() {
		return new BenzBike();
	}
};

class BMWFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new BMWCar();
	}
	IBike* CreateBike() {
		return new BMWBike();
	}
};

class AudiFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new AudiCar();
	}
	IBike* CreateBike() {
		return new AudiBike();
	}
};

AbstractFactory* AbstractFactory::CreateFactory(Factory_type fac_type) {
	AbstractFactory* pFactory = NULL;
	switch (fac_type)
	{
	case AbstractFactory::Factory_type::BENZ_FACTORY:
		pFactory = new BenzFactory();
		break;
	case AbstractFactory::Factory_type::BMW_FACTORY:
		pFactory = new BMWFactory();
		break;
	case AbstractFactory::Factory_type::AUDI_FACTORY:
		pFactory = new AudiFactory();
		break;
	default:
		break;
	}
	return pFactory;
}

//int main() {
//	AbstractFactory* pFactory = AbstractFactory::CreateFactory(AbstractFactory::Factory_type::BENZ_FACTORY);
//	ICar* pCar = pFactory->CreateCar();
//	IBike* pBike = pFactory->CreateBike();
//
//	cout << "创建了汽车:" << pCar->Name();
//	cout << endl;
//	cout << "创建了自行车:" << pBike->Name();
//
//
//	return 0;
//}