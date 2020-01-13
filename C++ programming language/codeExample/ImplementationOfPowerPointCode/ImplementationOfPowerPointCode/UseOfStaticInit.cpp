#include <iostream>
using namespace std;

class A {
public:
	A() {
		cout << "A construct" << endl;
	}

};

class B {
public:
	B() {
		cout << "B construct" << endl;
	}

private:
	static A a;
};
A a = A();

int main() {
	B b;
	return 0;
}