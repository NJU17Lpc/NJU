#include<iostream>
using namespace std;

class Array3D {
public:
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
	Array3D(int n1, int n2, int n3) {
		for (int i = 0; i < n3; i++) {
			//array2d+i = new Array2D(n1, n2);
		//Î´Íê³É
		}
	}
private:

	int num1, num2, num3;
	Array2D *array2d;
};

//int main() {
//
//	return 0;
//}