#include<iostream>
using namespace std;
// ::  .*  .  ?: 这四个确定不能重载
//其他不能重载的操作符是遵循一些原则
//因为要遵循已有操作符的语法：单目/双目 优先级 结合性， && || & | 这些不要去重载
//因为要遵循已有操作符的语义：如取地址就是&的内置含义，  &和，这些也不要重载
//除了=  其他操作符重载都可以继承
//= () []不能作为全局函数重载，毕竟全局函数必须给两个参数
class Complex {
private:
	double real;
	double imag;
public:
	Complex() :real(0), imag(0) {}
	Complex(double r, double i) :real(r), imag(i) {}
	//加法产生新值，不要返回引用，在函数域里面的引用在函数结束后就会销毁
	Complex operator+(const Complex& x) {
		Complex temp;
		temp.real = real + x.real;
		temp.imag = imag + x.imag;
		return temp;
	}
	//也可以支持这种friend重载
	//+-这种对称性的操作符重载，最好是用friend非成员函数
	friend Complex operator-(const Complex& c1, const Complex& c2);

	//输入输出运算符重载中
	//都尽量弄成friend非成员函数，不然就像下面这样c<<cout，不能连续cout
	//输出一般不想改变参数类型，参数设为const
	//有时候输入会处理输入错误的问题，要求这个时候对象要复位到预定状态，可以加上if(in) xxx else xxx
	ostream& operator<<(ostream& out) {
		out << "real:" << real << " " << "imag:" << imag;
		return out;
	}
	friend istream& operator>> (istream& in, Complex& c);

	//这种混合类型表达式，比如int double混用，最好都非成员函数
	friend Complex operator+(int real, const Complex& c);
	friend Complex operator+(const Complex& c, int real);

	//a++ vs ++a
	//++a用一个dummy argument来和a++区分开
	//查了下，这个dummy argument类型可以random
	Complex& operator++() {//++a
		real++;
		return *this;//返回改变后的对象
	}
	//a++不同于++a还有一点，a++返回拷贝而不是引用
	Complex operator++(int) {//a++
		Complex temp = *this;//拷贝改变前的对象
		imag++;
		return temp;//返回改变前的对象拷贝
	}
};

Complex operator-(const Complex& c1, const Complex& c2) {
	Complex temp;
	temp.real = c1.real + c2.real;
	temp.imag = c1.imag + c2.imag;
	return temp;
}
istream& operator>> (istream& in, Complex& c) {
	in >> c.imag >> c.real;
	return in;
}

Complex operator+(int real, const Complex& c) {
	Complex temp = c;
	temp.real = real + c.real;
	return temp;
}
Complex operator+(const Complex& c, int real) {
	return real + c;
}

//int main() {
//	Complex a(1, 2), b(3, 4), c;
//	cin >> a >> b;
//	c = a + b;
//	a = c.operator+(b);
//	c << cout;
//	cout << endl;
//	a << cout;
//	cout << endl;
//	a = 1 + a;
//	a << cout;
//	cout << endl;
//	a = a + 1;
//	a << cout;
//	cout << endl;
//	a++ << cout;
//	cout << endl;
//	++a << cout;
//	getchar();
//	return 0;
//}