#include <iostream>
#include <string>
using namespace std;

/*
֮ǰ�Ĺ�������ģʽ�������Ĳ�Ʒ��ͬһ�������͵ģ�ֻ������ί�ɲ�ͬ�Ĺ���ȥ����ͬ��������Ʒ
���ڱ���˾�����������������������г�����Ȼ����ֻ�ù�������ģʽ
���ڹ����е�ÿ��������������һ�����͵Ĳ�Ʒ��һ���������������һ������һ��Ĳ�Ʒ

��ʱд��ʱ�򣬺����ڸ�������ľ�̬�����У�����������󷵻�ʱ�����˵����⣬���ǵ������Ӷ�������֮ǰ����û�ж�������
������������д���������嶨���Ƶ����ඨ���֮����д����û����
��Ҫ��һ��C++�ĳ�ʼ��˳��

��ʵ�ҳ�������������棬�Ҹо������static������������������е���֣���Ϊdemoֱ�Ӷ�̬�󶨲������ˣ�����
*/

/*
������
1��һ������£������������ã���Ϊһ�����幤����Ӧһ�������Ʒ
2����ʱ��������Ҫһ�������������ṩ�����Ʒ���󣬶����ǵ�һ��Ʒ����

��Ʒ�ȼ��ṹ��
1�����ǲ�Ʒ�ļ̳нṹ�������࣬��������
2��������䣬���ຣ������
��Ʒ��
1��ͬһ�����������ģ�λ�� ��ͬ��Ʒ�ȼ��ṹ �е�һ���Ʒ
2�����������У����ӻ������䲻��һ���ȼ��ṹ��������һ����Ʒ��

����
1�����󹤳��Ǹ��ֹ���ģʽ�У���Ϊ�����һ�����̬
2�������������ͬһ����Ʒ�ȼ��ṹ�����󹤳���Զ����Ʒ�ȼ��ṹ

���壺
1���ṩһ������һϵ����ػ����໥��������Ľӿڣ�����Ҫָ���������
2���ֽ�Kitģʽ
3�����󴴽���ģʽ

ʵ����
1����������
2���Զ������ݿ����Ӷ���connection ��������statement
factory�������createConntection(),createStatement()

�ŵ㣺
1�������˾���������ɣ����Ǹ���һ�����幤���Ƚ����ף�ֻҪ�ı���幤����ʵ��
2�����ھۣ������
3���е�ϵͳ�����Ҫ���ݵ�ǰ������������Ϊ����ˣ�һ����Ʒ����������Ҫһ����ʱ
���󹤳����Ա��Ͽͻ�����ʹ��ͬһ����Ʒ���еĶ���
4�������µľ��幤���Ͳ�Ʒ��ܷ��㣬����Ҫ�޸�����ϵͳ
���Ͽ���ԭ��

ȱ�㣺
1�������µĲ�Ʒ����ʱ��������չ���󹤳�������������Ĳ�Ʒ
������Ҫ�漰�Գ��󹤳�����������޸ģ�������
2������ԭ����б�ԣ�
�����µĹ����Ͳ�Ʒ�����ף�ע�⣬�����ģ����Ӳ�Ʒ����磬����������ӻ�����С���ӻ���
�����µĲ�Ʒ�ȼ��ṹ�鷳

���ã�
1��һ��ϵͳ��Ӧ�������ڲ�Ʒ��ʵ����α���������Ϻͱ���ϸ��
2��ϵͳ��������Ʒ�壬ÿ��ֻ����һ����Ʒ��
3������ͬһ����Ʒ��Ĳ�Ʒ��һ��ʹ�ã���һ���������Ƶ����������ֳ���
4��ϵͳ�ṩһ����Ʒ��Ŀ⣬���в�Ʒͬ���ӿڣ����ǿͻ��˲������ھ���ʵ��

����ԭ�����б�ԣ�
1�������µĲ�Ʒ�壬ֻ��Ҫ����һ���µľ��幤�����У�����Ҫ�޸����д���
2�������µĲ�Ʒ�ȼ��ṹ����Ҫ�޸����й�����ɫ���������󹤳���
	���ӵȼ��ṹ�����Ϊԭ��ֻ��Ҫ�������Ӻͱ��䣬������Ҫ���ӿյ�

�˻���
1�����ֻ����һ����Ʒ�ȼ��ṹ�����󹤳��˻��ɹ�������
2�����������У����󹤳��;��幤���ϲ����ṩһ��ͳһ�Ĺ�����������Ʒ
������������Ĺ����������Ϊ��̬ʱ
�˻��ɼ򵥹���

*/

class ICar {
public:
	virtual string Name() = 0;
};

class IBike {
public:
	virtual string Name() = 0;
};

//////////////////����
class BenzCar :public ICar {
public:
	string Name() override{
		return "Benz Car";
	}
};

class BMWCar :public ICar {
public:
	string Name() override {
		return "BMW Car";
	}
};

class AudiCar :public ICar {
public:
	string Name() override {
		return "Audi Car";
	}
};

//////////////////���г�
class BenzBike :public IBike {
public:
	string Name() override {
		return "Benz Bike";
	}
};

class BMWBike :public IBike {
public:
	string Name() override {
		return "BMW Bike";
	}
};

class AudiBike :public IBike {
public:
	string Name() override {
		return "Audi Bike";
	}
};

///////////////////////////////����


class AbstractFactory {
public:
	enum Factory_type
	{
		BENZ_FACTORY,
		BMW_FACTORY,
		AUDI_FACTORY
	};

	virtual ICar* CreateCar() = 0;
	virtual IBike* CreateBike() = 0;
	static AbstractFactory* CreateFactory(Factory_type fac_type);
};

class BenzFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new BenzCar();
	}
	IBike* CreateBike() {
		return new BenzBike();
	}
};

class BMWFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new BMWCar();
	}
	IBike* CreateBike() {
		return new BMWBike();
	}
};

class AudiFactory :public AbstractFactory {
public:
	ICar* CreateCar() {
		return new AudiCar();
	}
	IBike* CreateBike() {
		return new AudiBike();
	}
};

AbstractFactory* AbstractFactory::CreateFactory(Factory_type fac_type) {
	AbstractFactory* pFactory = NULL;
	switch (fac_type)
	{
	case AbstractFactory::Factory_type::BENZ_FACTORY:
		pFactory = new BenzFactory();
		break;
	case AbstractFactory::Factory_type::BMW_FACTORY:
		pFactory = new BMWFactory();
		break;
	case AbstractFactory::Factory_type::AUDI_FACTORY:
		pFactory = new AudiFactory();
		break;
	default:
		break;
	}
	return pFactory;
}

//int main() {
//	AbstractFactory* pFactory = AbstractFactory::CreateFactory(AbstractFactory::Factory_type::BENZ_FACTORY);
//	ICar* pCar = pFactory->CreateCar();
//	IBike* pBike = pFactory->CreateBike();
//
//	cout << "����������:" << pCar->Name();
//	cout << endl;
//	cout << "���������г�:" << pBike->Name();
//
//
//	return 0;
//}