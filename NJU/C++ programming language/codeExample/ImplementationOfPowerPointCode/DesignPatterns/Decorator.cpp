#include<iostream>
#include<string>
using namespace std;

/*
这个装饰器写好后就有种莫名其妙鬼畜的感觉hhh
组成部分和装饰器都继承自同一个父类，这里是DrinkComponent
这样就可以变成Base* base = new XXX(new XXX(new XXX()));

要注意的是decorator不仅持有一个component，还要继承一个component

第一部分都属于component
作为饮料的打底材料
可以是咖啡、绿茶什么的，没加雪顶那种
*/
class DrinkComponent {//普通的原始饮料
public:
	virtual string Name() = 0;
	virtual double Cost() = 0;
};

class BlackCoffee: public DrinkComponent {
public:
	string Name() {
		return "BlackCoffee";
	}
	double Cost() {
		return 30.0;
	}
};

class GreenTea : public DrinkComponent {
public:
	string Name() {
		return "GreenTea";
	}
	double Cost() {
		return 25.0;
	}
};

/*
第二部分的这个装饰器，第一个simple版本的就是什么也不加
如果是绿茶，就返回绿茶的名字和价钱

后面的都是加了其他小料的
*/
class SimpleDrinkDecorator:public DrinkComponent {
public:
	SimpleDrinkDecorator(DrinkComponent* drinkComponent):drinkComponent(drinkComponent){}
	string Name() {
		return drinkComponent->Name();
	}
	double Cost() {
		return drinkComponent->Cost();
	}
protected:
	DrinkComponent* drinkComponent;
};

class IceCream :public SimpleDrinkDecorator {
public:
	IceCream(DrinkComponent* drinkComponent):SimpleDrinkDecorator(drinkComponent){}
	string Name() {
		return drinkComponent->Name() + " with IceCream";
	}
	double Cost() {
		return drinkComponent->Cost() + 3;
	}
};

//上面加摩卡
class Mocha:public SimpleDrinkDecorator {
public:
	Mocha(DrinkComponent* drinkComponent) :SimpleDrinkDecorator(drinkComponent) {}
	string Name() {
		return drinkComponent->Name() + " with Mocha";
	}
	double Cost() {
		return drinkComponent->Cost() + 2.5;
	}
};

//int main() {
//	//黑咖啡基本款
//	DrinkComponent* basicCoffeDrink = new BlackCoffee();
//	cout << basicCoffeDrink->Name() << ": " << basicCoffeDrink->Cost() << endl;
//
//	//绿茶
//	DrinkComponent* basicTeaDrink = new GreenTea();
//	cout << basicTeaDrink->Name() << ": " << basicTeaDrink->Cost() << endl;
//	
//	//绿茶加雪顶
//	SimpleDrinkDecorator* IceCreamDecTea = new IceCream(basicTeaDrink);
//	cout << IceCreamDecTea->Name() << ": " << IceCreamDecTea->Cost() << endl;
//
//	//魔鬼版本，黑咖啡加两层雪顶加摩卡
//	//这就体现出SimpleDrinkDecorator作为同一父类的好处了，不需要额外转换
//	SimpleDrinkDecorator* wtf = new Mocha(new IceCream(new IceCream(basicTeaDrink)));
//	cout << wtf->Name() << ": " << wtf->Cost() << endl;
//}