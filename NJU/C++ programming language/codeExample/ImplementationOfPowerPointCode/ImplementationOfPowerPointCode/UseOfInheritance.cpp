#include<iostream>
#include <string>
using namespace std;

/*
�̳з�ʽ
1��public�̳�
����ԭ��״̬
2��private�̳�
��������public��Ա��protected��Ա�����������private��Ա
����������಻�ܷ���������ĳ�Ա
3��protected�̳�
��������public��Ա��protected��Ա�����������protected��Ա
ֻ�ܱ��������Ա����������Ԫ����
��4��ԭ����private�Ļ���private

1��public inheritance�������������is_a��ϵ
2��ע�ⲻҪ������̳ж����ģ������Ա���� ͬ���� ��Ա����

private Inheritance
1����Ҫ��������
2����Ʋ���û�����壬ֻ����ʵ�ֲ���
3����ζ�š�������ݻ����ʵ�ֶ��õ���:implemented-in-term-of
4�����ǽ�һ���ࣨ���ࣩ����Ϊ��һ���ࣨ���ࣩ��һ����ʵ�����ݣ����û���ʵ������
	��һ���񸴺Ϲ�ϵ����һ���������һ����Ա��

һ��ʲôʱ��ʹ��private Inheritance  �Ƚ� private �̳к͸��ϣ�������ôѡ
1����Ҫʹ��Base class �е�protected ��Ա����������virtual function
2����ϣ��һ��Base class ��clientʹ��
*/

class Person {
public:
	Person(string name) :m_name(name) {

	}
	string getName() {
		return m_name;
	}
protected:
	string m_name;
};

class Student:private Person{
public:
	Student(string name):Person(name){}
};

void eat(Person& p) {
	cout << p.getName() << " is eating" << endl;
}
//int main() {
//	Person a("normal person");
//	Student b("a student");
//	eat(a);//OK
//	//eat(b);//ERROR
//	return 0;
//}