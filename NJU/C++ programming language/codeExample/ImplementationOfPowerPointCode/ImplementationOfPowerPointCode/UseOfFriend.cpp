#include <iostream>
#include <exception>
using namespace std;

/*
��Ԫ���Էֳ����֣���ͬ����д��ʽ
1����Ԫ����  friend void func()
2����Ԫ��  friend class B
3����Ԫ���Ա����  friend void C::f()

����
1����߳�����������
2�����ݱ����Ͷ����ݴ�ȡЧ��֮���һ�� ���з���

����
1����Ԫ���ܱ��̳�
һ������������Ϊ���࣬���Ե��ø����˽�г�Ա���ڸ���������Ϊfriend
��������������������Ϊ�������������������û������Ϊfriend����ô���ܷ���˽�г�Ա
2����Ԫ��ϵ�ǵ���ģ������н�����
3����Ԫ��ϵ���߱�������
���磺B��A����Ԫ��B���Է���A��˽�в��֣�C��B����Ԫ��C���Է���B��˽�в���
����C���ܷ���A��˽�в���

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
	//��Ԫ���ܱ��̳�
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

	//��Ҫ����˽�б�����ʱ�򣬾�Ҫ����friend
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

	//���ܸ�����������friend�����ǲ�����������࣬���ಢ����Ĭ��friend���������������Ҫ����������friend
	//����Ԫ���߱�������
	for (int i = 0; i < lin1; i++) {
		for (int j = 0; j < col1; j++) {
			//ͬʱ��Ҫע�⣬�������Ӧ�ĳ�Ա������Ӧ��Ϊprotected
			*(res.m_pData + i * col1 + j) = m1.element(i, j) + m2.element(i, j);
		}
	}

}


//��һ������
class Base {
protected:
	int prot_mem;
};

class Sneaky :public Base {

	friend void clobber(Sneaky&);
	friend void clobber(Base&);

	//Ĭ��ΪPrivate
	int j;
};

void clobber(Sneaky& s) {
	//��ȷ��Sneaky������������Ԫ�����Լ��̳е����Ը����protected��Ա��Ȼ���Է���
	//�Ͼ��Ը���̳е�protected������Sneaky& s�������ã�������Base& b��
	s.j = s.prot_mem = 0;
}

void clobber(Base& b) {
	//����Base����û��������clobber(Base&)����Ԫ�����ܷ���protected member
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