#include <iostream>
#include <list>
using namespace std;


class NLComponent {//newsletter component

public:
	virtual void getType() = 0;
	virtual NLComponent* clone() const = 0;
};

class TextBlock :public NLComponent {
public:
	virtual void getType() override {
		cout << "this is TextBlock" << endl;
	}
	//为什么后面拷贝构造需要调用这个clone呢？？
	//我感觉是因为，我在拷贝的时候，是把一堆父类型的指针拷贝进来
	//于是使用这个返回子类型指针的clone方法，可以再动态地将子类型指针加到list里面
	//好像具体的行为由编译器决定，我就不追究了
	virtual TextBlock* clone() const {
		return new TextBlock(*this);
	}
};


class Graphic :public NLComponent {
public:
	virtual void getType() override {
		cout << "this is Graphic" << endl;
	}
	virtual Graphic* clone() const {
		return new Graphic(*this);
	}
};

class NewsLetter {
public:
	//这个行为与构造函数相似
	//能根据输入数据不同，建立不同类型的对象，称为虚拟构造函数
	NewsLetter(istream& str) {
		while (str) {
			components.push_back(readComponent(str));
		}
	}

	//这个是虚拟拷贝构造函数
	NewsLetter(const NewsLetter& rhs) {
		for (auto it = rhs.components.begin(); it != rhs.components.end(); ++it) {
			components.push_back((*it)->clone());
		}
	}

	//目测静态非静态都没啥关系？
	//我就不实现了，给个样子就好
	static NLComponent* readComponent(istream& str);
private:
	list<NLComponent*> components;
};

/*
never treats array polymorphically
绝对不要用多态的方式处理数组

*/
class Base{
public:
	friend ostream& operator<<(ostream& out, const Base &b) {
		out << "Base ";
	}
};
class Derived:public Base{
	//friend ostream& operator<<(ostream& out, const Base &d) {
	//	out << "Derived ";
	//}
};

/*
解析
1、由于array[i]实际上就是*(array+i)，就是移动i个单元，再解引用
2、于是编译器需要知道移动了多少个字节
3、方法声明的时候为父类数组，移动的字节就是 i*sizeof(Base)
4、当传过去一个子类对象的时候，子类往往比父类大，造成的结果不可预期
5、同样，传过去一个 Base array[] ，要去delete[] array ， 结果也是不可预期
因此绝对不要以多态方式处理数组
*/
//void Print(ostream& s, const Base array[], int size) {
//	for (int i = 0; i < size; i++) {
//		s << array[i];
//	}
//}

	//这里我们不做上面的的实例化了


