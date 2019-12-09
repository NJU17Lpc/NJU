#include<iostream>
#include<initializer_list>
#pragma warning(disable:4996)
using namespace std;

class CharArray {
private:
	char* p;
public:
	CharArray(const char* p1) {
		p = new char[strlen(p1) + 1];
		strcpy(p, p1);
	}
	virtual ~CharArray() { delete[] p; }

	//如果一个类包含下标运算符，通常会定义两个版本
	//一个返回普通引用，另一个是类的常量成员，并返回常量引用，即两个const

	//如果只有普通引用版本，那么对const CharArray c, 就无法调用c[0]
	char& operator[](int i) {
		return p[i];
	}
	//这个第二个const必须有，因为不能仅仅按照返回类型const区分重载函数
	//如果只有const版本，可以获得数据，但即使是非const声明，也不能通过[]修改成员数据
	//即只有const版本时候，CharArray c("abcd");c[0] = 'm';报错
	const char& operator[](int i) const {
		return p[i];
	}
	friend ostream& operator<<(ostream& out, const CharArray& c);

	//复制时删除本来存储的数据，添加新数据，返回自身的引用
	//一般的=对指针变量，只复制指针本身。这样如果某个对象被析构了，那么共享的部分被删除
	//这种情况下，会有idle pointer
	//有必要使用一种智能指针对引用计数
	CharArray& operator=(CharArray& c) {
		if (this == &c) {
			//另外如果没有这个判定，调用的时候需要避免 a=a 这种自我赋值。加上if就没事了
			return *this;
		}

		delete[]p;
		p = new char[strlen(c.p) + 1];
		strcpy(p, c.p);
		return *this;
	}
};

ostream& operator<<(ostream& out, const CharArray& c) {
	out << c.p;
	return out;
}
//int main() {
//	CharArray c("abcd");
//	c[0] = 'm';
//	cout << c[0] << endl;
//	cout << c << endl;
//	CharArray a("lpc");
//	cout << a << endl;
//	a = c;
//	cout << a << endl;
//	return 0;
//}