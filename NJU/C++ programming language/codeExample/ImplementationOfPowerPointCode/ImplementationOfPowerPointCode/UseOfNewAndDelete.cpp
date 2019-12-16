#include <iostream>
#include <string>
using namespace std;

/*
为什么有了malloc()还需要free()
1、对非内部数据的对象来说，只用malloc/free 无法满足动态对象的要求
2、malloc/free 是库函数，不是运算符，不在编译器控制权限
3、现在需要保证对象创建的时候自动执行构造函数，消亡前自动执行析构函数
4、于是new 能完成动态内存分配 和初始化
delete 能完成清理与释放内存

new 和delete 时发生了什么
demo: A *p, *q; p = new A; delete p;
1、new 先空间，再赋值
	a 在程序heap申请大小为sizeof(A)的内存
	b 调用A的默认构造函数，对这个空间上的对象初始化
	c 返回创建对象的 地址 ，并赋值给p

2、delete 先析构，再空间
	a 调用p所指向对象的析构函数
	b 释放对象空间
	此时指针为NULL

new/delete 可以重载

注意动态对象数组的创建与销毁
1、A* p = new A[100];这个情况相应的类必须有默认构造函数
2、delete[]p;数组的时候，这里的[]不能省去

下面的demo是演示动态2D数组的新建与删除
！！！！！！！！！要注意new和delete的顺序
*/
void demoPrint(char** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void demo(int rows, int cols) {
	char** chArray;
	chArray = new char*[rows];
	char temp[] = "lpc";
	for (int i = 0; i < rows; i++) {
		chArray[i] = new char[cols];
		for (int j = 0; j < cols; j++) {
			chArray[i][j] = temp[i % 3];
		}
	}
	demoPrint(chArray, rows, cols);
	cout << endl;

	//delete 操作是new 操作反过来，先对里面delete，在对外面delete
	for (int i = 0; i < rows; i++) {
		delete[] chArray[i];
		chArray[i] = NULL;
	}
	delete[] chArray;
	chArray = NULL;
	cout << sizeof(chArray) << endl;
}

//int main() {
//	demo(3, 4);
//	return 0;
//}