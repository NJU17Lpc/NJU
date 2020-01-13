#include <iostream>
#include <string>
using namespace std;

/*
现在想要从一个支付工厂里面获得不同的支付方式的实例
*/

/*
定义：
1、简单工厂模式 就是 静态工厂模式
2、类创建型模式
3、根据不同参数返回不同实例，实例有相同的父类

分析
1、将对象创建和对象本身业务分离，降低系统耦合度
2、工厂方法是静态方法，可通过类名直接调用
开发中可以把参数放在XML里面，修改配置时就不需要修改代码
3、不需要知道创建的细节
4、工厂类的职责过重

优点：
1、工厂类负责判断，客户端只需要消费产生的对象
于是责任得到分割
2、客户端不需要知道具体类名，只需要知道参数
3、引入配置文件，可以在不修改客户端代码的时候，灵活更换和增加新的产品类

缺点：
1、集中所有产品创建逻辑，一旦工厂类出问题，整个系统受到影响
2、增加系统中类的个数，增加复杂度
3、系统虽然修改参数容易，但是扩展困难，一旦增加新的产品就必须修改工厂逻辑
产品类型很多的时候，工厂逻辑会过于复杂
4、静态工厂，使得工厂无法形成继承的结构，扩展性不够好

适用：
1、工厂创建对象较少
2、客户端只需要知道参数和对象类型对应关系，不关心创建细节，甚至具体的子类类型都不需要知道

应用：
1、JDK的java.text.DataFormat::getDataInstance()参数可以不同，获取不同类型的结果
2、Java加密，参数决定不同加密算法

扩展：
可以把工厂的静态方法，放到产品类的抽象类中，简化工厂模式

不足：
1、违背开闭原则
系统加入新产品时需要修改工厂类，加入处理逻辑
具体产品和工厂类耦合过高
2、可以换成工厂方法模式
*/

class IPayMethod {
public:
	virtual void pay() = 0;
};

class AliPay:public IPayMethod
{
public:
	void pay() override {
		cout << "use AliPay" << endl;
	}
};

class WeCharPay :public IPayMethod {
public:
	void pay() override {
		cout << "use WeChatPay" << endl;
	}
};

class CreditCardPay :public IPayMethod {
public:
	void pay() override {
		cout << "use CreditCardPay" << endl;
	}
};

class PayFactory {
public:
	static IPayMethod* getPayMethod(string method) {
		if (method == "ali") {
			return new AliPay();
		}
		else if (method == "wc") {
			return new WeCharPay();
		}
		else if (method == "cc") {
			return new CreditCardPay();
		}
		else {
			cout << "not a valid pay type" << endl;
			return NULL;
		}
	}
};

//int main() {
//	IPayMethod* method1 = PayFactory::getPayMethod("ali");
//	IPayMethod* method2 = PayFactory::getPayMethod("wc");
//	IPayMethod* method3 = PayFactory::getPayMethod("cc");
//	IPayMethod* method4 = PayFactory::getPayMethod("lpc");
//
//	method1->pay();
//	method2->pay();
//	method3->pay();
//	//method4->pay();
//
//
//	return 0;
//}