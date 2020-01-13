#include <iostream>
using namespace std;

class Base {
public:
	int getPrice() { return price; }
	int getTick() { return tick; }

	friend istream& operator>>(istream& in, Base& base);
	friend ostream& operator<<(ostream& out, Base& base);

private:
	int price;
	int tick;
};

istream& operator>>(istream& in, Base& base) {
	in >> base.price >> base.tick;
	return in;
}

ostream& operator<<(ostream& out, Base& base) {
	out << base.price << " " << base.tick << endl;
	return out;
}

//int main() {
//	Base base;
//	cin >> base;
//	cout << endl;
//	cout << base;
//
//
//}