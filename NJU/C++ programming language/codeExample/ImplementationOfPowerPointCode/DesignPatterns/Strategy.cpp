#include <iostream>
#include <string>
using namespace std;

/*
选择不同的旅游交通工具

*/

class IStrategy {
public:
	virtual void Travel() = 0;
	IStrategy(string strategy):m_vehicle(strategy){}
protected:
	string m_vehicle;
};

class BikeStrategy :public IStrategy {
public:
	BikeStrategy():IStrategy("bike"){}
	virtual void Travel() override {
		cout << "travel by:" << m_vehicle << endl;
	}
};

class CarStrategy :public IStrategy {
public:
	CarStrategy():IStrategy("car"){}
	virtual void Travel() override {
		cout << "travel by:" << m_vehicle << endl;
	}
};

class PlaneStrategy :public IStrategy {
public:
	PlaneStrategy() :IStrategy("plane") {}
	virtual void Travel() override {
		cout << "travel by:" << m_vehicle << endl;
	}
};

class Context {
public:
	Context(IStrategy* strategy):strategy(strategy){}
	void go() { strategy->Travel(); }

private:
	IStrategy* strategy;
};
int main(){
	Context context1(new PlaneStrategy());
	context1.go();

	Context context2(new CarStrategy());
	context2.go();

	Context context3(new BikeStrategy());
	context3.go();
	return 0;
}