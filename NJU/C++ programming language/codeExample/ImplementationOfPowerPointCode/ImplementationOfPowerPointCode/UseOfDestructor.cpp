#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

/*
��������ʲô��
1���Աȹ��캯������ʼ����static��Ա+��������
2���������ͷŶ���ʹ�õ���Դ�����ٷ�static���ݳ�Ա
˳��
1�����캯���У���Ա��ʼ�����ڹ��캯��������
2����������ִ�к����壬Ȼ�����ٳ�Ա�������������

��ָ��һ����������û���ָ���뿪������ʱ��������������ִ��

����
1����Ҫ��������Ҳ��Ҫ�����͸�ֵ����
2����Ҫ������������Ҳ��Ҫ��ֵ��������֮һ����������һ���У�

*/
/*
C++Ĭ�ϰ������Զ��ϳɵ����������������ʱ����Ժܺõع���
����һЩʱ����Ҫ�����Լ�ȥд����
׼�򣺵����ж������������������ҹ��캯����ʹ����ϵͳ��Դ���ڴ����롢�ļ��򿪵ȣ�������Ҫ�Զ�����������
����������ʱ��ϵͳ�Զ�����
*/

class String {
private:
	char* m_str;
public:
	String() { m_str = NULL; }
	String(const char* p) {
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}
	~String() {
		cout << "����String����:" << m_str << endl;
		delete[] m_str;
	}
	int length() { return strlen(m_str); }
	char get_char(int i) { return m_str[i]; }
	void set_char(int i, char c) { m_str[i] = c; }
	char* my_strcpy(char* p) {
		delete[] m_str;
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}
	String& my_strcpy(String& s) {
		delete[] m_str;
		m_str = new char[strlen(s.m_str) + 1];
		strcpy(m_str, s.m_str);
		return *this;
	}
};
/*
һ����˵��һ��������������麯������ý���������Ҳ������麯��

ע�����ȵ�������������������ٵ��ø������������
�����캯���෴�����캯���ȸ��࣬������
*/
class B {
public:
	virtual ~B() {
		cout << "base destructor" << endl;
	}
};

class D :public B {
public:
	~D() {
		cout << "derived destructor" << endl;
	}
};
//int main() {
//	//String s("asuka saito");
//	B* b1;
//	D d1;
//	b1 = &d1;
//
//	//���ú�ָ��һ����̬����
//	//��Ϊ���õı��ʾ��ǽ����ò��������Ա����Ϻ�ָ��һ��ʹ��
//	D d2;
//	B& b2 = d2;
//	return 0;
//}