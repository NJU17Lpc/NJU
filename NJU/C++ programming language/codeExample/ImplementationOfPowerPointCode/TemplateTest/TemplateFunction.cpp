#include <iostream>
using namespace std;

/*
������template function �ĺ�ʵ��
ȱ��
1��ֻ��ʵ�ּ򵥵Ĺ���
2��û�����ͼ��

�ԱȺ���ָ��
����ָ��ȱ��
1����Ҫ����������
2������ָ������
3��ʵ����������
4���ɶ��Բ�
*/
#define max(a,b) ((a)>(b)?(a):(b))

//ģ��ɴ��ж�������������������ͨ�������ö��ŷָ�
//ģ���е�static��Ա����ʵ����֮�����
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


//ģ��Ԫ��̣���ʵ���Ǹ����ӵ��ģ��
//���ǽ��ݹ顢��֧�ȱ��ʱ���еĸ�����뵽ģ�壬�Զ����ɴ���
/*
����Ԫ��̵ĺô�
1��������׷�����ܣ�һ���C++����Ҳ���㲻�����ʱ��
2��Ҫôʹ�û��
3���������Ҫ���ܣ���Ҫ��������ɶȺʹ��븴��
4����ϧ�úö౶�ı���ʱ�䣬����ȡ����������������ģ��Ԫ
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