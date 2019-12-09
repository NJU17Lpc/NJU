#include<iostream>
using namespace std;

class virtualCake {
protected:
	int price;
public:
	virtualCake(int p):price(p){}
	virtual int getPrice() = 0;
};

class beefCake :public virtualCake {
public:
	int getPrice() {
		return price;
	}
	beefCake():virtualCake(10){}
};

class porkCake :public virtualCake {
public:
	int getPrice() {
		return price;
	}
	porkCake() :virtualCake(8) {}
};

class chickenCake :public virtualCake {
public:
	int getPrice() {
		return price;
	}
	chickenCake() :virtualCake(7) {}
};

class virtualVegetable {
protected:
	int price;
public:
	virtualVegetable(int p) :price(p) {}
	virtual int getPrice() = 0;
};

class lettuce :public virtualVegetable {
public:
	int getPrice() {
		return price;
	}
	lettuce() :virtualVegetable(4) {}
};

class tomato :public virtualVegetable {
public:
	int getPrice() {
		return price;
	}
	tomato() :virtualVegetable(3) {}
};

class Ham {
private:
	virtualCake* cake;
	virtualVegetable* vege;
	int cake_num;
	int vege_num;
public:
	Ham(int cake_type, int vege_type, int cakeNum, int vegeNum):cake_num(cakeNum), vege_num(vegeNum) {
		switch (cake_type) {
		case 1:
			cake = new beefCake();
			break;
		case 2:
			cake = new porkCake();
			break;
		case 3:
			cake = new chickenCake();
			break;
		default:
			break;
		}
		switch (vege_type)
		{
		case 1:
			vege = new lettuce();
			break;
		case 2:
			vege = new tomato();
			break;
		default:
			break;
		}
	}
	int getPrice() {
		return cake->getPrice()*cake_num + vege->getPrice()*vege_num;
}
};

int main() {
	int cakeType = 0, cakeNum = 0;
	int vegeType = 0, vegeNum = 0;
	cin >> cakeType >> cakeNum >> vegeType >> vegeNum;
	Ham h(cakeType, vegeType, cakeNum, vegeNum);
	cout << h.getPrice();
	return 0;
}