#include <iostream>
using namespace std;

/*
这属于template function 的宏实现
缺陷
1、只能实现简单的功能
2、没有类型检查

对比函数指针
函数指针缺点
1、需要定义额外参数
2、大量指针运算
3、实现起来复杂
4、可读性差
*/
#define max(a,b) ((a)>(b)?(a):(b))

//模板可带有多个参数，里面可以有普通参数，用逗号分隔
//模板中的static成员属于实例化之后的类
template<class T, int size>
class MyStack {
public:
	void push(T x);
	T pop();
private:
	T buffer[size];
};

template<class T, int size>
void MyStack<T, size>::push(T x)
{
	cout << "push" << endl;
}

template<class T, int size>
T MyStack<T, size>::pop()
{
	cout << "pop" << endl;
	//T b<double, 20>;
	return NULL;
}


//模板元编程，其实就是更复杂点的模板
//就是将递归、分支等编程时才有的概念，加入到模板，自动生成代码
/*
这种元编程的好处
1、当极致追求性能，一般的C++代码也满足不了你的时候
2、要么使用汇编
3、但如果既要性能，又要更大的自由度和代码复用
4、不惜用好多倍的编译时间，来换取性能提升，可以用模板元
*/
template<int N>
class Fib {
public:
	enum{value=Fib<N-1>::value + Fib<N-2>::value};
};
template<>
class Fib<0> {
public:
	enum { value = 1 };
};
template<>
class Fib<1> {
public:
	enum { value = 1 };
};


//int main() {
//	MyStack<double, 200> st1;
//	st1.push(3);
//	st1.pop();
//
//	cout << max(4, 2) << endl;
//	cout << Fib<45>::value << endl;
//	return 0;
//}