#include<iostream>
#include<string>
using namespace std;

/*
���װ����д�ú������Ī���������ĸо�hhh
��ɲ��ֺ�װ�������̳���ͬһ�����࣬������DrinkComponent
�����Ϳ��Ա��Base* base = new XXX(new XXX(new XXX()));

Ҫע�����decorator��������һ��component����Ҫ�̳�һ��component

��һ���ֶ�����component
��Ϊ���ϵĴ�ײ���
�����ǿ��ȡ��̲�ʲô�ģ�û��ѩ������
*/
class DrinkComponent {//��ͨ��ԭʼ����
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
�ڶ����ֵ����װ��������һ��simple�汾�ľ���ʲôҲ����
������̲裬�ͷ����̲�����ֺͼ�Ǯ

����Ķ��Ǽ�������С�ϵ�
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

//�����Ħ��
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
//	//�ڿ��Ȼ�����
//	DrinkComponent* basicCoffeDrink = new BlackCoffee();
//	cout << basicCoffeDrink->Name() << ": " << basicCoffeDrink->Cost() << endl;
//
//	//�̲�
//	DrinkComponent* basicTeaDrink = new GreenTea();
//	cout << basicTeaDrink->Name() << ": " << basicTeaDrink->Cost() << endl;
//	
//	//�̲��ѩ��
//	SimpleDrinkDecorator* IceCreamDecTea = new IceCream(basicTeaDrink);
//	cout << IceCreamDecTea->Name() << ": " << IceCreamDecTea->Cost() << endl;
//
//	//ħ��汾���ڿ��ȼ�����ѩ����Ħ��
//	//������ֳ�SimpleDrinkDecorator��Ϊͬһ����ĺô��ˣ�����Ҫ����ת��
//	SimpleDrinkDecorator* wtf = new Mocha(new IceCream(new IceCream(basicTeaDrink)));
//	cout << wtf->Name() << ": " << wtf->Cost() << endl;
//}