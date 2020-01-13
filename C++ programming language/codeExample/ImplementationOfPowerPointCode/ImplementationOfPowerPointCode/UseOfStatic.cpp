#include<iostream>
using namespace std;
/*
static数据成员与类关联，但是不和该类定义的对象有任何关系
static修饰的对象先于对象存在，因此必须要在类外初始化

static成员变量在对象中不占内存，它在静态存储区。于是如果大量对象共享一个static挺节省空间的

static修饰的类成员不属于对象，因此static成员函数没有this指针
	于是static类成员函数不能访问非static成员

*/

class A {
private:
	static int obj_count;
public:
	A() { obj_count++; }
	~A() { obj_count--; }
	static int get_num_of_obj() {
		return obj_count;
	}
	static int get_num_of_obj_test();
};

//静态成员数据必须在类外定义，前面的类型说明int是必须的
int A::obj_count = 0;

//静态成员函数类外类内都可以，但前面的int类型也是必须
int A::get_num_of_obj_test() {
	return obj_count;
}

class mySingleton {
private:
	//通过把实例声明为static的，那样所有对象都共享一个实例
	static mySingleton* m_instance;
	static int obj_counter;
	int nonStaticNum;
	mySingleton() { obj_counter++; }
public:
	//这个getInstance方法必须为static的，因为这样才能通过类名来访问
	static mySingleton* getInstance() {
		//这个static方法访问的就是static成员对象，static和new没什么关系

		//这个非静态成员数据就不能访问了
		//nonStaticNum++;
		return m_instance == NULL ? m_instance = new mySingleton() : m_instance;
	}

	//访问静态成员数据，成员函数是非为static都可以
	int get_obj_counter() {
		return obj_counter;
	}
};
mySingleton* mySingleton::m_instance = NULL;
int mySingleton::obj_counter = 0;

//int main() {
//	A a;
//	A b;
//	A c;
//	cout << A::get_num_of_obj() << endl;
//	cout << a.get_num_of_obj() << endl;
//	cout << c.get_num_of_obj_test() << endl;
//	//访问规则还是要遵循的
//	//cout << A::obj_count << endl;
//
//	mySingleton* m = mySingleton::getInstance();
//	mySingleton* n = mySingleton::getInstance();
//	cout << m->get_obj_counter() << endl;
//	//cout << mySingleton::get_obj_counter() << endl;
//	cout << n->get_obj_counter() << endl;
//
//	return 0;
//}