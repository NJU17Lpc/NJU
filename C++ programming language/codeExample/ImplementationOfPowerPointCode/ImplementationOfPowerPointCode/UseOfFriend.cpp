#include <iostream>
#include <exception>
using namespace std;

/*
友元可以分成三种，不同的书写方式
1、友元函数  friend void func()
2、友元类  friend class B
3、友元类成员函数  friend void C::f()

作用
1、提高程序设计灵活性
2、数据保护和对数据存取效率之间的一个 折中方案

限制
1、友元不能被继承
一个方法，参数为父类，可以调用父类的私有成员，在父类中声明为friend
但是如果这个方法，重载为子类参数，但是子类中没有声明为friend，那么不能访问私有成员
2、友元关系是单向的，不具有交换性
3、友元关系不具备传递性
比如：B是A的友元，B可以访问A的私有部分；C是B的友元，C可以访问B的私有部分
但是C不能访问A的私有部分

*/

class Matrix {
public:
	Matrix(int l, int c) :line(l), col(c) {
		m_pData = new int[line*col];
		int* q = m_pData;
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < col; j++) {
				*q = line;
				q++;
			}
		}
	}
	~Matrix() {
		delete[] m_pData;
	}
	int& element(int i, int j) {
		return *(m_pData + i * col + j);
	}
	void dimension(int& l, int& c) {
		l = line;
		c = col;
	}
	void display() {
		int* p = m_pData;
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < col; j++) {
				cout << *p << " ";
				p++;
			}
			cout << endl;
		}
	}
	friend void addMatrix(Matrix& m1, Matrix& m2, Matrix& res);
protected:
	int* m_pData;
	int line;
	int col;
};

class MatrixSon :public Matrix {
	//友元不能被继承
	friend void addMatrix(MatrixSon& m1, MatrixSon& m2, MatrixSon& res);
public:
	MatrixSon(int i, int j):Matrix(i, j){}
};


void addMatrix(Matrix& m1, Matrix& m2, Matrix& res) {
	int lin1, col1, lin2, col2, lin3, col3;
	m1.dimension(lin1, col1);
	m2.dimension(lin2, col2);
	res.dimension(lin3, col3);

	if (lin1 != lin2 || col1 != col2 || lin1 != lin3 || col1 != col3) {
		return;
	}

	//for (int i = 0; i < lin1; i++) {
	//	for (int j = 0; j < col1; j++) {
	//		res.element(i, j) = m1.element(i, j) + m2.element(i, j);
	//	}
	//}

	//想要访问私有变量的时候，就要加入friend
	for (int i = 0; i < lin1; i++) {
		for (int j = 0; j < col1; j++) {
			*(res.m_pData + i * col1 + j) = m1.element(i, j) + m2.element(i, j);
		}
	}

}
void addMatrix(MatrixSon& m1, MatrixSon& m2, MatrixSon& res) {
	int lin1, col1, lin2, col2, lin3, col3;
	m1.dimension(lin1, col1);
	m2.dimension(lin2, col2);
	res.dimension(lin3, col3);

	if (lin1 != lin2 || col1 != col2 || lin1 != lin3 || col1 != col3) {
		return;
	}

	//尽管父类对这个方法friend，但是参数变成了子类，子类并不会默认friend这个方法，还是需要在子类声明friend
	//即友元不具备传递性
	for (int i = 0; i < lin1; i++) {
		for (int j = 0; j < col1; j++) {
			//同时还要注意，父类相对应的成员变量还应该为protected
			*(res.m_pData + i * col1 + j) = m1.element(i, j) + m2.element(i, j);
		}
	}

}


//另一个样例
class Base {
protected:
	int prot_mem;
};

class Sneaky :public Base {

	friend void clobber(Sneaky&);
	friend void clobber(Base&);

	//默认为Private
	int j;
};

void clobber(Sneaky& s) {
	//正确，Sneaky里面声明了友元，而自己继承的来自父类的protected成员自然可以访问
	//毕竟对父类继承的protected，是在Sneaky& s上做调用，而不是Base& b上
	s.j = s.prot_mem = 0;
}

void clobber(Base& b) {
	//错误，Base里面没有声明对clobber(Base&)的友元，不能访问protected member
	//b.prot_mem = 0;
}

//int main() {
//	//Matrix m1(3, 4);
//	//Matrix m2(3, 4);
//	//Matrix res(3, 4);
//
//	MatrixSon m1(3, 4);
//	MatrixSon m2(3, 4);
//	MatrixSon res(3, 4);
//
//	addMatrix(m1, m2, res);
//
//	res.display();
//
//	return 0;
//}