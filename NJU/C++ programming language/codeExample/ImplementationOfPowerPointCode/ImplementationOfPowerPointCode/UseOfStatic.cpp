#include<iostream>
using namespace std;
/*
static���ݳ�Ա������������ǲ��͸��ඨ��Ķ������κι�ϵ
static���εĶ������ڶ�����ڣ���˱���Ҫ�������ʼ��

static��Ա�����ڶ����в�ռ�ڴ棬���ھ�̬�洢���������������������һ��staticͦ��ʡ�ռ��

static���ε����Ա�����ڶ������static��Ա����û��thisָ��
	����static���Ա�������ܷ��ʷ�static��Ա

*/

class A {
private:
	static int obj_count;
public:
	A() { obj_count++; }
	~A() { obj_count--; }
	static int get_num_of_obj() {
		return obj_count;
	}
	static int get_num_of_obj_test();
};

//��̬��Ա���ݱ��������ⶨ�壬ǰ�������˵��int�Ǳ����
int A::obj_count = 0;

//��̬��Ա�����������ڶ����ԣ���ǰ���int����Ҳ�Ǳ���
int A::get_num_of_obj_test() {
	return obj_count;
}

class mySingleton {
private:
	//ͨ����ʵ������Ϊstatic�ģ��������ж��󶼹���һ��ʵ��
	static mySingleton* m_instance;
	static int obj_counter;
	int nonStaticNum;
	mySingleton() { obj_counter++; }
public:
	//���getInstance��������Ϊstatic�ģ���Ϊ��������ͨ������������
	static mySingleton* getInstance() {
		//���static�������ʵľ���static��Ա����static��newûʲô��ϵ

		//����Ǿ�̬��Ա���ݾͲ��ܷ�����
		//nonStaticNum++;
		return m_instance == NULL ? m_instance = new mySingleton() : m_instance;
	}

	//���ʾ�̬��Ա���ݣ���Ա�����Ƿ�Ϊstatic������
	int get_obj_counter() {
		return obj_counter;
	}
};
mySingleton* mySingleton::m_instance = NULL;
int mySingleton::obj_counter = 0;

//int main() {
//	A a;
//	A b;
//	A c;
//	cout << A::get_num_of_obj() << endl;
//	cout << a.get_num_of_obj() << endl;
//	cout << c.get_num_of_obj_test() << endl;
//	//���ʹ�����Ҫ��ѭ��
//	//cout << A::obj_count << endl;
//
//	mySingleton* m = mySingleton::getInstance();
//	mySingleton* n = mySingleton::getInstance();
//	cout << m->get_obj_counter() << endl;
//	//cout << mySingleton::get_obj_counter() << endl;
//	cout << n->get_obj_counter() << endl;
//
//	return 0;
//}