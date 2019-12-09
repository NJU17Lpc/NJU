#include<iostream>
#include<vector>
#include<exception>
#include<string>
#include<fstream>
using namespace std;

class DrinkOverflowException:public exception {
public:

	const char* what() const {
		return "DrinkOverflow";
	}
};

class DrinkNotFoundException :public exception {
protected:
	string msg;
public:
	DrinkNotFoundException(int type){
		string temp = "";
		switch(type) {
		case 1:
			temp = "coffee";
			break;
		case 2:
			temp = "milk";
			break;
		case 3:
			temp = "tea";
			break;
		case 4:
			temp = "beer";
			break;
		default:
			break;
		}
		temp = temp + " is not found";
		msg = temp;
	}

	const char* what() const {
		return msg.c_str();
	}
};

class Drink {

public:
	virtual void buy() = 0;
	virtual int getType() = 0;
	virtual string getName() = 0;
};

class coffee : public Drink {
private:
	int type = 1;
	string name = "coffee";
	int price = 5;
public:

	int getType() { return type; }
	string getName() { return name; }
	void buy() {
		cout << name << ":" << price << endl;
	}
};

class milk : public Drink {
private:
	int type = 2;
	string name = "milk";
	int price = 4;

public:
	int getType() { return type; }
	string getName() { return name; }

	void buy() {
		cout << name << ":" << price <<endl;
	}
};

class tea : public Drink {
private:
	int type = 3;
	string name = "tea";
	int price = 3;

public:
	int getType() { return type; }
	string getName() { return name; }

	void buy() {
		cout << name << ":" << price << endl;
	}
};

class beer : public Drink {
private:
	int type = 4;
	string name = "beer";
	int price = 6;

public:
	int getType() { return type; }
	string getName() { return name; }

	void buy() {
		cout << name << ":" << price << endl;
	}
};

class drinkFactory {
public:
	Drink* getDrink(int type) {
		switch (type) {
		case 1:
			return new coffee();
			break;
		case 2:
			return new milk();
			break;
		case 3:
			return new tea();
			break;
		case 4:
			return new beer();
			break;
		default:
			break;
		}
	}

};

class Warehouse {
private:
	Warehouse(int num) :product_num(num) {}
	Warehouse(){}
	static Warehouse* house;
	vector<Drink*> drinks;
	drinkFactory factory;
	int product_num;

public:

	static Warehouse* getInstance() {
		if (house == NULL) {
			house = new Warehouse(10);
		}
		return house;
	}

	void addDrink(int type, int num){
		for (int i = 0; i < num; i++) {
			Drink* tempDrink = factory.getDrink(type);
			drinks.push_back(tempDrink);
			if (drinks.size() > product_num) {

				DrinkOverflowException e;
				throw e;
			}
		}
	}

	void buyDrink(int type) {
		bool hasDrink = false;
		for (int i = 0; i < drinks.size(); i++) {
			if (drinks[i]->getType() == type) {
				hasDrink = true;
				drinks[i]->buy();
				drinks.erase(drinks.begin()+i);
				break;
			}
		}
		if (!hasDrink) {
			DrinkNotFoundException e(type);
			throw e;
		}
	}
};
Warehouse* Warehouse::house = NULL;

int main() {
	//string s;
	//
	//while (true) {
	//	getline(cin, s);
	//	ofstream outfile("E:\\input.txt", ios::app);
	//	outfile << s << endl;
	////	if (s == "3") {
	//		outfile << endl << endl;
	//		break; }
	//}

	Warehouse* warehouse = Warehouse::getInstance();
	int op_type = 0;
	while (cin >> op_type) {
		if (op_type == 1) {
			int drink_type = 0, drink_num = 0;
			cin >> drink_type >> drink_num;
			try {
				warehouse->addDrink(drink_type, drink_num);
			}
			catch (DrinkOverflowException& e) {
				cout << e.what() << endl;
			}
		}
		else if (op_type == 2) {
			int drink_type = 0;
			cin >> drink_type;

			try {
				warehouse->buyDrink(drink_type);
			}
			catch (DrinkNotFoundException& e) {
				cout << e.what() << endl;
			}
		}
		else {
			break;
		}
	}
	return 0;
}