#include<iostream>
using namespace std;

/*
const�������Ǻ���ߣ���ʾ��ָ���ǳ���
const�������Ǻ��ұߣ���ʾָ�������ǳ���
const�������Ǻ����ߣ���ʾ���ǳ���
const�����͵�˳���޹أ�const int* a;  int const* a;һ��
const����������������
*/

class myNumber {
private:
	int num1;
	int num2;
	char* info;
public:
	myNumber(int n1, int n2) :num1(n1), num2(n2) {
		info = new char[5]{ 0 };
	}
	void testConstFunc1(int newNum1, int newNum2) const {
		//const���ͺ��������޸ĳ�Ա
		//�����������䲻�ܱ���
		/*num1 = newNum1;
		num2 = newNum2;*/
		//Ҳ�����Ե��÷Ǿ�̬����
		//testConstFunc2(newNum1, newNum2);

		//����������ݳ�Ա��ָ�룬const��Ա����Ҳ�ǿ����޸�ָ��ָ��Ķ����
		//	���ǲ��õķ�񣬵����Ǵ����
		for (int i = 0; i < 3; i++) {
			info[i] = 'a';
		}
		cout << "testConstFunc1 with const" << endl;
	}

	//const����������Ϊ����
	//��������ĳ����Ծ��������ĸ��汾
	//��������ֻ�ܵ��ó�������
	//�ǳ������󶼿��Ե���
	void testConstFunc1(int newNum1, int newNum2) {
		cout << "testConstFunc1 without const" << endl;
	}

	void testConstFunc2(int newNum1, int newNum2) {
		num1 = newNum1;
		num2 = newNum2;
		cout << "testConstFunc2 without const" << endl;
	}
	friend const myNumber operator*(myNumber m1, myNumber m2);
	friend ostream& operator<<(ostream& out, myNumber n);
};
ostream& operator<<(ostream& out, myNumber n) {
	out << n.num1 << " " << n.num2;
	return out;
}

/*
������ص�const�������Խ��Ϳͻ�������ɵ����⣬��߰�ȫ��
����if(a*b=c)����Ӧ����==����д����

*/
const myNumber operator*(myNumber m1, myNumber m2) {
	myNumber n(m1.num1*m2.num1, m2.num2*m2.num2);
	return n;
}

//int main() {
//	myNumber n1(2, 3);
//	myNumber n2(2, 3);
//	myNumber n3 = n1 * n2;
//	const myNumber n4(1, 1);
//	//const�����ֻ�ܵ���const��Ա����
//	//ͬʱ���ȵ��õ���const�汾������
//	//n4.testConstFunc2(3, 4);
//	n4.testConstFunc1(3, 4);
//
//	//��const�������غ������ȵ��÷�const�汾
//	//��const������Ե���const�ͷ�const����
//	n1.testConstFunc1(2, 3);
//	n1.testConstFunc2(2, 3);
//
//	cout << n1 << endl << n2 << endl << n3 << endl;
//	return 0;
//}