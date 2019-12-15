#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

/*
������Ҫ�ƶ����󣬶����ǿ���������������
������ֵ����ֵ
1����ֵ���г־�״̬
2����ֵ��Ҫô�����泣����Ҫô����ֵ�����е���ʱ����
	�����õĶ���Ҫô��Ҫ�����٣�Ҫôû�������û�
	������ֵ���ܰ󶨵���ֵ:int&& rr = i;����
		����int&& rr = i*40;��ȷ
	�����ֵ���õĴ���������ɽӹ������ö������Դ
3������Ҳ������ʽ��ǿ�У���ð�����ֵ�ϵ���ֵ����
	int &&rr = std::move(rr1);
	��������Ҫ��ŵ�����˸�ֵ��������rr1�����ǲ���ʹ����

�ƶ����캯��
1�����캯���ĵ�һ�������Ǹ������͵�һ�����ã���������ֵ����
�����κζ���Ĳ�������Ĭ��ʵ��
2��һ���ƶ���ɣ����ƶ�����Դ������Ȩ��������Դ��������

�������캯���У��ж������Դ������ͷŵĲ���
�ƶ����캯���У�ֱ��ʹ����ʱ�����Ѿ��������Դ�����������ʱ�����Ǹ�����ʱ����������Ҫ����ת��

��ֵ����������ȷ����perfect forwarding��Ŀ�ⲻ�����뿴
�ο� https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
*/
class String {
private:
	char* m_str;
public:
	String() {
		cout << "��ͨ�޲ι��캯��" << endl;
		m_str = NULL; 
	}
	String(const char* p) {
		cout << "��ͨ���ι��캯��" << endl;
		m_str = new char[strlen(p) + 1];
		strcpy(m_str, p);
	}

	String(const String& str) {
		cout << "�������캯��" << endl;
		m_str = new char[strlen(str.m_str) + 1];
		strcpy(m_str, str.m_str);
	}

	String(String&& str)noexcept {
		cout << "�ƶ����캯��" << endl;
		m_str = str.m_str;
		str.m_str = NULL;//�������Ҫ��
	}
	~String() {

		if (m_str != NULL) {
			cout << "����String����:" << m_str << endl;
			delete[] m_str;
		}
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

String getStr(const char* p) {
	String temp(p);
	return temp;
}
//�����漰�Ķ����Ƚϸ��ӣ����ȷ��һ�¿�����
//int main() {
//	String s1("saito asuka");
//	String s2 = s1;
//	String s3(s2);
//
//	//�����������󣬼���ֵ���ã�������ֵ��ʹ��
//	//�������������ֿ�
//	String s4(std::move(s2));//ʹ��move�������ƶ����캯��
//
//	//������������ʱ�����Ѿ��������Դ������
//	String s5 = getStr("erika");//��������ƶ����캯���������ڲ���һ����ͨ���ι��캯��
//	return 0;
//}