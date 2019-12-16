#include <iostream>
#include <string>
using namespace std;

/*
Ϊʲô����malloc()����Ҫfree()
1���Է��ڲ����ݵĶ�����˵��ֻ��malloc/free �޷����㶯̬�����Ҫ��
2��malloc/free �ǿ⺯������������������ڱ���������Ȩ��
3��������Ҫ��֤���󴴽���ʱ���Զ�ִ�й��캯��������ǰ�Զ�ִ����������
4������new ����ɶ�̬�ڴ���� �ͳ�ʼ��
delete ������������ͷ��ڴ�

new ��delete ʱ������ʲô
demo: A *p, *q; p = new A; delete p;
1��new �ȿռ䣬�ٸ�ֵ
	a �ڳ���heap�����СΪsizeof(A)���ڴ�
	b ����A��Ĭ�Ϲ��캯����������ռ��ϵĶ����ʼ��
	c ���ش�������� ��ַ ������ֵ��p

2��delete ���������ٿռ�
	a ����p��ָ��������������
	b �ͷŶ���ռ�
	��ʱָ��ΪNULL

new/delete ��������

ע�⶯̬��������Ĵ���������
1��A* p = new A[100];��������Ӧ���������Ĭ�Ϲ��캯��
2��delete[]p;�����ʱ�������[]����ʡȥ

�����demo����ʾ��̬2D������½���ɾ��
������������������Ҫע��new��delete��˳��
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

	//delete ������new �������������ȶ�����delete���ڶ�����delete
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