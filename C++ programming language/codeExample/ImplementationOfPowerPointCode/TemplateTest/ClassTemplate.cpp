#include<iostream>
using namespace std;

//ģ����ڱ�������˵���Ǵ��ı���������ռ䡣����C++��ģ��Ķ�������ͷ�ļ����档
//Ҳ��Ϊ���Ǵ��ı������������Դ����ظ�ģ������⣬���ǲ������ظ���������⣬���Է���д��ͷ�ļ�����
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
//	//�����ƶ��þ��������
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