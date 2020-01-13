#include<iostream>
using namespace std;

class Array2D {
public:
	class Array1D {
	public:
		Array1D(int *p) { this->p = p; }
		int& operator[](int index) {
			return p[index];
		}
		const int& operator[](int index) const {
			return p[index];
		}
	private:
		int *p;
	};
	Array2D(int n1, int n2) {
		p = new int[n1*n2];
		num1 = n1;
		num2 = n2;
	}
	virtual ~Array2D() { delete[]p; }
	Array1D operator[](int index) {
		return p + index * num2;
	}
	const Array1D operator[](int index) const {
		return p + index * num2;
	}

private:
	int *p;
	int num1, num2;
};

//int main() {
//	Array2D array(3, 4);
//	array[1][3] = 19;
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 4; j++) {
//			cout << array[i][j] << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}