#include <iostream>
#include <list>
using namespace std;


class NLComponent {//newsletter component

public:
	virtual void getType() = 0;
	virtual NLComponent* clone() const = 0;
};

class TextBlock :public NLComponent {
public:
	virtual void getType() override {
		cout << "this is TextBlock" << endl;
	}
	//Ϊʲô���濽��������Ҫ�������clone�أ���
	//�Ҹо�����Ϊ�����ڿ�����ʱ���ǰ�һ�Ѹ����͵�ָ�뿽������
	//����ʹ���������������ָ���clone�����������ٶ�̬�ؽ�������ָ��ӵ�list����
	//����������Ϊ�ɱ������������ҾͲ�׷����
	virtual TextBlock* clone() const {
		return new TextBlock(*this);
	}
};


class Graphic :public NLComponent {
public:
	virtual void getType() override {
		cout << "this is Graphic" << endl;
	}
	virtual Graphic* clone() const {
		return new Graphic(*this);
	}
};

class NewsLetter {
public:
	//�����Ϊ�빹�캯������
	//�ܸ����������ݲ�ͬ��������ͬ���͵Ķ��󣬳�Ϊ���⹹�캯��
	NewsLetter(istream& str) {
		while (str) {
			components.push_back(readComponent(str));
		}
	}

	//��������⿽�����캯��
	NewsLetter(const NewsLetter& rhs) {
		for (auto it = rhs.components.begin(); it != rhs.components.end(); ++it) {
			components.push_back((*it)->clone());
		}
	}

	//Ŀ�⾲̬�Ǿ�̬��ûɶ��ϵ��
	//�ҾͲ�ʵ���ˣ��������Ӿͺ�
	static NLComponent* readComponent(istream& str);
private:
	list<NLComponent*> components;
};

/*
never treats array polymorphically
���Բ�Ҫ�ö�̬�ķ�ʽ��������

*/
class Base{
public:
	friend ostream& operator<<(ostream& out, const Base &b) {
		out << "Base ";
	}
};
class Derived:public Base{
	//friend ostream& operator<<(ostream& out, const Base &d) {
	//	out << "Derived ";
	//}
};

/*
����
1������array[i]ʵ���Ͼ���*(array+i)�������ƶ�i����Ԫ���ٽ�����
2�����Ǳ�������Ҫ֪���ƶ��˶��ٸ��ֽ�
3������������ʱ��Ϊ�������飬�ƶ����ֽھ��� i*sizeof(Base)
4��������ȥһ����������ʱ�����������ȸ������ɵĽ������Ԥ��
5��ͬ��������ȥһ�� Base array[] ��Ҫȥdelete[] array �� ���Ҳ�ǲ���Ԥ��
��˾��Բ�Ҫ�Զ�̬��ʽ��������
*/
//void Print(ostream& s, const Base array[], int size) {
//	for (int i = 0; i < size; i++) {
//		s << array[i];
//	}
//}

	//�������ǲ�������ĵ�ʵ������


