#include<iostream>
using namespace std;

//�������ز�����>
//һ������£���Ҫ���ز�����=,����copy constructor
template<typename T>
void sort(T A[], unsigned int num) {
	for (int i = 1; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (A[j] > A[j + 1]) {
				//���������>�б�Ҫ����
				T temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
			}
		}
	}
}

template<typename T>
void printArray(T A[], unsigned int num) {
	for (int i = 0; i < num; i++) {
		cout << A[i] << " ";
	}
}

//int x,y,z; double a,b,c; max(x,y), max(a,b)��û���⣬����max(x,a)��ô��----����һ�����غ���
template<typename T>
T max(T a, T b) {
	return a > b ? a : b;
}
//����������ƥ�������ȼ������Կ������ʹ�����غ�����ģ�庯��
double max(int a, double b) {
	return a > b ? a : b;
}

//int main() {
//	double a[10]{ 0 };
//	for (int i = 0; i < 10; i++) {
//		a[i] = i % 3;
//	}
//	printArray(a, 10);
//	sort(a, 10);
//	cout << endl;
//	printArray(a, 10);
//}