#include <iostream>
#include <string>
using namespace std;

/*
现在用户需要做Log记录，于是有不同的Log类型：FileLog, DatabaseLog; 有不同的LogFactory类型：FileLogFactory, DatabaseLogFactory
加入新的Log类型，需要继承一个Log，同时要扩展继承一个LogFactory
*/

/*
工厂方法模式 定义：
1、又叫多态工厂模式
2、类创建型模式
3、工厂父类定义创建产品对象的公共接口，工厂子类负责生成具体的产品对象
4、通过工厂子类，来确定实例化哪个具体产品类（去除了静态工厂中复杂的判断逻辑）

分析：
1、核心的工厂类将具体创建交给子类去做
2、可以在不修改工厂角色的情况下，引进新产品
3、系统添加新的产品对象，只需要加入具体产品对象和一个具体工厂对象，不用修改原有工厂对象
符合开闭原则
4、实际开发中，一般将不直接用new创建对象，而是把具体类名写入配置文件里面
通过java反射机制，读取XML格式的配置文件，通过XML里面的类名字符串生成对象
	这个反射机制就是，可以通过class c = class.forName("String");获得string相关联的class对象
	再用Object obj = c.newInstance()创建对象所表示类的一个实例
	就是通过 类名字符串 得到类的实例
	具体用的时候，有一个DocumentBuilderFactory创建Dom文档对象，然后可以doc.getElementsByTagName("className")
	后面就是获取NodeValue，最后就Class c = Class.forName(xxx), Object obj = c.newInstance()
客户端用的时候，就像这样PayMethodFactory factory = (PayMethodFactory)XMLUtil.getBean()

优点：
1、用户只要关心产品对应的工厂，不需要关心创建细节，也不用知道具体产品类类名（注意，至少要知道工厂名哈）
2、工厂可以自主决定创建哪种产品对象，如何创建的细节被封装
3、系统中加入新产品，不需要修改抽象工厂和抽象产品的接口，不需要修改客户端，也不用修改其他具体工厂和具体产品，加上新的产品和工厂就好了

缺点：
1、加一个新产品时，要加上产品类和工厂类，类的个数踏跺，更多的类被编译和运行，增加系统开销
2、加上了一个抽象层，增加系统抽象性和理解难度
3、实现需要用到DOM、反射等技术，实现难度高了

适用：
1、一个类不知道他需要的对象的类，只需要知道工厂就行
2、一个类通过子类，指定创建哪个对象
3、将创建对象的任务委托给某个子类工厂，客户端使用对象的时候，不关心哪个工厂创建的这个对象，需要时动态指定


*/
class ILog {
public:
	virtual void writeLog() = 0;
};

class FileLog :public ILog{
public:
	virtual void writeLog() override {
		cout << "write a FileLog" << endl;
	}
};

class DatabaseLog :public ILog{
public:
	virtual void writeLog()	override {
		cout << "write a DatabaseLog" << endl;
	}
};

class ILogFactory {
public:
	virtual ILog* createLog() = 0;
};

class FileLogFactory :public ILogFactory {
public:
	ILog* createLog() override {
		cout << "FileLogFactory creates a File Log" << endl;
		return new FileLog();
	}
};

class DatabaseLogFactory :public ILogFactory {
public:
	ILog* createLog() override {
		cout << "DatabaseLogFactory creates a Database Log" << endl;
		return new DatabaseLog();
	}

};
//int main() {
//	ILogFactory* fileFac = new FileLogFactory();
//	ILogFactory* databaseFac = new DatabaseLogFactory();
//
//	ILog* log1 = fileFac->createLog();
//	ILog* log2 = databaseFac->createLog();
//
//	log1->writeLog();
//	log2->writeLog();
//
//	return 0;
//}