#include<iostream>
using namespace std;

//必须重载操作符>
//一定情况下，需要重载操作符=,还有copy constructor
template<typename T>
void sort(T A[], unsigned int num) {
	for (int i = 1; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (A[j] > A[j + 1]) {
				//这个操作符>有必要重载
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

//int x,y,z; double a,b,c; max(x,y), max(a,b)都没问题，但是max(x,a)怎么办----定义一个重载函数
template<typename T>
T max(T a, T b) {
	return a > b ? a : b;
}
//编译器类型匹配有优先级，所以可以配合使用重载函数和模板函数
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