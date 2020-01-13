#include<iostream>
using namespace std;

//模板对于编译器来说就是纯文本，不分配空间。于是C++中模板的定义是在头文件里面。
//也因为他是纯文本，编译器可以处理重复模板的问题，于是不会有重复定义的问题，可以放心写在头文件里面
template<class T>
class Stack {
private:
	T buffer[100];
	int sp;
public:
	Stack():sp(-1){}
	void push(T x) {
		buffer[++sp] = x;
	}
	T pop();
	void print() {
		for (int i = 0; i <= sp; i++) {
			cout << buffer[i] << " ";
		}
	}
};
template<class T>
T Stack<T>::pop() {
	if (sp >= 0) {
		return buffer[sp--];
	}
	else {
		throw exception("no more element");
	}
}

//int main() {
//	//必须制定好具体的类型
//	Stack<double> myStack;
//	for (int i = 0; i < 5; i++) {
//		myStack.push(i);
//	}
//	myStack.print();
//	cout << endl;
//	for (int i = 0; i < 4; i++) {
//		cout << myStack.pop() << ",";
//	}
//	cout << myStack.pop();
//	cout << endl;
//	try {
//		myStack.pop();
//	}
//	catch (exception e) {
//		cout << e.what() << endl;
//	}
//	return 0;
//}