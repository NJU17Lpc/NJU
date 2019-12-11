#include <iostream>
#include <string>
using namespace std;

/*
�����°��꣬�������ģ���ү�����ӣ���ë�����Ҹ��ƣ����˰�hh

*/

/*
������
1����Ҫ��¡�������ԭ��һģһ���Ķ���
2����Щ���󴴽����̺ܸ��ӣ�ԭ��ģʽ����һ��ԭ�Ͷ���ָ����Ҫ������������ͣ�Ȼ����������󣬴Ӷ��������ܶ�ͬ���͵Ķ���
���ǿ����Լ���ʵ�ִ����������˽ⴴ��ϸ��

Ӧ�ã�
�ʼ�����----ǳ����
ctrl c+v �������������ͬ�����ڴ��ַ��ͬ�Ķ���
Spring�У��û�����ԭ��ģʽ�������µ�beanʵ����ÿ�λ�ȡ��¡����ʵ�����޸�ʱ��ԭ��ʵ��������κ�Ӱ��

�ŵ㣺
1�������¶���ʵ���ܸ���ʱ��ԭ��ģʽ���Լ򻯶���Ĵ�������
ͨ������ʵ�������ʵ������Ч��
2�����Զ�̬���ӻ���ٲ�Ʒ��
3���ṩ�򻯵Ĵ����ṹ
4�����������¡���������״̬

ȱ�㣺
1����ҪΪÿһ�����䱸һ����¡��������ԭ�е�����и��죬��ʵΥ���˿���ԭ��
2�����¡����Ҫ��д��Ϊ���ӵĴ���

���û�����
1�������¶���ɱ��ϴ�ֱ�Ӹ���ԭ���Ķ���ֻ��Ҫ��������΢�޸ľͺ���
2�����ϵͳҪ��������״̬��ͬʱ����״̬�仯��С������ԭ��+����¼ģʽ���������״̬�仯�ܴ�״̬ģʽ����
3����Ҫ����ʹ�÷ֲ�εĹ������������ֲ�εĶ��󣬲������ʵ������ֻ��һ�����ߺ��ټ������״̬����ʱ���Ʊȹ��췽��

��չ��
���ƶ���ĸ��ƣ�
	ԭ��ģʽ�����ͬ����󣬿��Զ����Խ����޸ģ��Ӷ���ȡ��Ҫ�Ķ���
	�������ѧ����רҵ��ѧУ�Ⱥܶ���Ϣ��һ����ֻ���Ա����������䲻ͬ

*/
/*
д��ʱ��ע��
1����һ�����ж������棬��ͨ�������Լ���һ���ǿ������캯����������new֮��Ľ������ʵ�ִ����Ĺ���
2������ԭ������Clone()�ӿڣ�����ԭ����ʵ�־���Clone()����
3���ͻ���ֻҪֱ��ʵ�������߹�����������ͨ������ʵ����Clone()��úܶ���ͬ�Ķ���
4��ʵ�����¡�Ƚϸ���
*/
class Monkey {
public:
	Monkey(){}
	virtual ~Monkey(){}
	virtual Monkey* Clone() = 0;
	//ս������
	virtual void tacticalBack() = 0;
};

//��ү��
class SixLittleAgeChild :public Monkey {
public:
	SixLittleAgeChild(string name) { m_strName = name; }
	~SixLittleAgeChild()
	{
		cout << "delete : " << m_strName << endl;
	}

	SixLittleAgeChild(const SixLittleAgeChild& other) {
		m_strName = other.m_strName;
	}

	SixLittleAgeChild* Clone() override {
		return new SixLittleAgeChild(*this);
	}

	void tacticalBack() override {
		cout << m_strName << "˵����ʲô�й���Ӱ�ǰ���" << endl;
	}

private:
	string m_strName;
};

int main() {
	Monkey* monkey = new SixLittleAgeChild("��С��ͯ");
	Monkey* monkey1 = monkey->Clone();
	Monkey* monkey2 = monkey1->Clone();

	monkey->tacticalBack();
	monkey1->tacticalBack();
	monkey2->tacticalBack();


	return 0;
}