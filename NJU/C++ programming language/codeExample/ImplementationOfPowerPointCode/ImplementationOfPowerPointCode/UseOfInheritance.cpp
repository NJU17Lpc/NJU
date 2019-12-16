#include<iostream>
#include <string>
using namespace std;

/*
继承方式
1、public继承
保持原有状态
2、private继承
基类所有public成员和protected成员都是派生类的private成员
派生类的子类不能访问派生类的成员
3、protected继承
基类所有public成员和protected成员都是派生类的protected成员
只能被派生类成员函数或者友元访问
（4、原来是private的还是private

1、public inheritance才是真正意义的is_a关系
2、注意不要定义域继承而来的，非虚成员函数 同名的 成员函数

private Inheritance
1、需要明智运用
2、设计层面没有意义，只用于实现层面
3、意味着“子类根据基类的实现而得到”:implemented-in-term-of
4、就是将一个类（基类），作为另一个类（子类）的一部分实现内容，即用基类实现子类
	有一点像复合关系，即一个类包含另一个成员类

一般什么时候使用private Inheritance  比较 private 继承和复合，二者怎么选
1、需要使用Base class 中的protected 成员，或者重载virtual function
2、不希望一个Base class 被client使用
*/

class Person {
public:
	Person(string name) :m_name(name) {

	}
	string getName() {
		return m_name;
	}
protected:
	string m_name;
};

class Student:private Person{
public:
	Student(string name):Person(name){}
};

void eat(Person& p) {
	cout << p.getName() << " is eating" << endl;
}
//int main() {
//	Person a("normal person");
//	Student b("a student");
//	eat(a);//OK
//	//eat(b);//ERROR
//	return 0;
//}