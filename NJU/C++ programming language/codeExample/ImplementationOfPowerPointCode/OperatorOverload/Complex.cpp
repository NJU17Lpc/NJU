#include<iostream>
using namespace std;
// ::  .*  .  ?: ���ĸ�ȷ����������
//�����������صĲ���������ѭһЩԭ��
//��ΪҪ��ѭ���в��������﷨����Ŀ/˫Ŀ ���ȼ� ����ԣ� && || & | ��Щ��Ҫȥ����
//��ΪҪ��ѭ���в����������壺��ȡ��ַ����&�����ú��壬  &�ͣ���ЩҲ��Ҫ����
//����=  �������������ض����Լ̳�
//= () []������Ϊȫ�ֺ������أ��Ͼ�ȫ�ֺ����������������
class Complex {
private:
	double real;
	double imag;
public:
	Complex() :real(0), imag(0) {}
	Complex(double r, double i) :real(r), imag(i) {}
	//�ӷ�������ֵ����Ҫ�������ã��ں���������������ں���������ͻ�����
	Complex operator+(const Complex& x) {
		Complex temp;
		temp.real = real + x.real;
		temp.imag = imag + x.imag;
		return temp;
	}
	//Ҳ����֧������friend����
	//+-���ֶԳ��ԵĲ��������أ��������friend�ǳ�Ա����
	friend Complex operator-(const Complex& c1, const Complex& c2);

	//������������������
	//������Ū��friend�ǳ�Ա��������Ȼ������������c<<cout����������cout
	//���һ�㲻��ı�������ͣ�������Ϊconst
	//��ʱ������ᴦ�������������⣬Ҫ�����ʱ�����Ҫ��λ��Ԥ��״̬�����Լ���if(in) xxx else xxx
	ostream& operator<<(ostream& out) {
		out << "real:" << real << " " << "imag:" << imag;
		return out;
	}
	friend istream& operator>> (istream& in, Complex& c);

	//���ֻ�����ͱ��ʽ������int double���ã���ö��ǳ�Ա����
	friend Complex operator+(int real, const Complex& c);
	friend Complex operator+(const Complex& c, int real);

	//a++ vs ++a
	//++a��һ��dummy argument����a++���ֿ�
	//�����£����dummy argument���Ϳ���random
	Complex& operator++() {//++a
		real++;
		return *this;//���ظı��Ķ���
	}
	//a++��ͬ��++a����һ�㣬a++���ؿ�������������
	Complex operator++(int) {//a++
		Complex temp = *this;//�����ı�ǰ�Ķ���
		imag++;
		return temp;//���ظı�ǰ�Ķ��󿽱�
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