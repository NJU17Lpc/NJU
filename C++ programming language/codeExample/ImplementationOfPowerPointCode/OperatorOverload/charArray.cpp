#include<iostream>
#include<initializer_list>
#pragma warning(disable:4996)
using namespace std;

class CharArray {
private:
	char* p;
public:
	CharArray(const char* p1) {
		p = new char[strlen(p1) + 1];
		strcpy(p, p1);
	}
	virtual ~CharArray() { delete[] p; }

	//���һ��������±��������ͨ���ᶨ�������汾
	//һ��������ͨ���ã���һ������ĳ�����Ա�������س������ã�������const

	//���ֻ����ͨ���ð汾����ô��const CharArray c, ���޷�����c[0]
	char& operator[](int i) {
		return p[i];
	}
	//����ڶ���const�����У���Ϊ���ܽ������շ�������const�������غ���
	//���ֻ��const�汾�����Ի�����ݣ�����ʹ�Ƿ�const������Ҳ����ͨ��[]�޸ĳ�Ա����
	//��ֻ��const�汾ʱ��CharArray c("abcd");c[0] = 'm';����
	const char& operator[](int i) const {
		return p[i];
	}
	friend ostream& operator<<(ostream& out, const CharArray& c);

	//����ʱɾ�������洢�����ݣ���������ݣ��������������
	//һ���=��ָ�������ֻ����ָ�뱾���������ĳ�����������ˣ���ô����Ĳ��ֱ�ɾ��
	//��������£�����idle pointer
	//�б�Ҫʹ��һ������ָ������ü���
	CharArray& operator=(CharArray& c) {
		if (this == &c) {
			//�������û������ж������õ�ʱ����Ҫ���� a=a �������Ҹ�ֵ������if��û����
			return *this;
		}

		delete[]p;
		p = new char[strlen(c.p) + 1];
		strcpy(p, c.p);
		return *this;
	}
};

ostream& operator<<(ostream& out, const CharArray& c) {
	out << c.p;
	return out;
}
//int main() {
//	CharArray c("abcd");
//	c[0] = 'm';
//	cout << c[0] << endl;
//	cout << c << endl;
//	CharArray a("lpc");
//	cout << a << endl;
//	a = c;
//	cout << a << endl;
//	return 0;
//}