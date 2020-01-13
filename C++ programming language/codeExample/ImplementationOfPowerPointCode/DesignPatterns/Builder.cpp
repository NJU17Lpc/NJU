#include<iostream>
#include <string>
using namespace std;

/*
现在联想有很多系列的电脑，每台电脑基本组装结构都是一样的，CPU+显卡+主板+内存等怼上去就好
其实怼起来的过程都差不多，如果为每一个型号设置一个组装流程，对于一个拥有很多型号的电脑的大公司，管理流程很不方便
于是有必要为所有系列指定一个统一的组装流程

将部件和组装过程分开，一步一步创建复杂对象

是对象创建型模式
*/

/*
很多复杂对象，存在很多限制条件，可能某些属性赋值需要按照某个特定顺序
建造者返回的是建造完毕的完整产品，用户不需要关心产品的属性和组装方式

这个指挥者隔离了用户与生产过程，负责控制产品的生成过程
客户只要提供具体类型给指挥者，指挥者就会被命令去装配
这就体现了客户不需要关心具体组装过程，只要知道类型就行

应用：
KFC套餐组装过程

优点：
客户端不需要知道产品内部细节，将产品与创建过程解耦，于是相同创建过程可以创建不同产品对象
可以方便替换具体建造者获得不同产品对象
可以更加精细控制产品创建过程，将复杂产品创建步骤分解
增加新的builder不需要修改原来的代码，因为director是针对抽象builder编程的，符合开闭原则

缺点：
建造者的产品一般具有很多共同点，组成相似；如果产品之间差异很大，不适合建造者
如果产品内部变化（记住是变化）很复杂，有必要定义很多具体建造者，针对不同情况建造产品，于是系统会很庞大

适用：
生成对象有复杂内部结构（变化不是很复杂），同时他们的属性相互依赖，有一定顺序
对象的创建过程独立于创建这个对象的类，即加入第三者，这就是需要指挥者。建造者不造自己，只提供造自己的方法
隔离复杂对象的创建和使用，于是相同创建过程适用于不同产品

例如游戏中，任务角色包括人体，服装，装备等。适合用建造者进行设计。
通过不同建造者创建不同类型人物

可以简化：
1、只有一个建造者builder时，可以省去IBuilder
2、在1的情况下，还可以舍去指挥者，此时建造者承担建造和指挥两种职责

对比抽象工厂模式：
1、建造者返回组装好的完整产品，抽象工厂返回一系列相关产品，构成产品族
2、建造者通过指挥类获取完整对象，不直接调用建造者的方法，被屏蔽了组装的过程
工厂模式中，客户端实例化工厂，然后调用工厂方法获取需要的产品对象
3、建造者模式是汽车组装工厂，他职责是组装部件返回完整汽车
抽象工厂模式是汽车配件生产工厂，生产一个产品族的产品

*/

/*
写的时候注意
需要写一个具体的产品，这个产品目测也可以用继承，但是一定要是可装配的
然后一个IBuilder，抽象出装配可以使用的方法，并返回装配完整后的对象
接着一个Director，接收一个Builder，自己组织装配过程
客户端只需要指出具体用什么builder，builder自己会创建出私有产品
然后客户端把builder交给director做，最后使用一个产品基类，接收director做好了的放在builder里面的产品
*/

class Computer {
public:
	void setmCpu(string cpu) { m_strCpu = cpu; }
	void setmMainBoard(string mainboard) { m_strMainboard = mainboard; }
	void setmRam(string ram) { m_strRam = ram; }
	void setmVideoCard(string videoCard) { m_strVideoCard = videoCard; }

	string getCpu() { return m_strCpu; }
	string getMainBoard() { return m_strMainboard; }
	string getRam() { return m_strRam; }
	string getVideoCard() { return m_strVideoCard; }

private:
	//这种命名方式挺不错的
	string m_strCpu;
	string m_strMainboard;
	string m_strRam;
	string m_strVideoCard;
};

//接口命名用I开始
class IBuilder {
public:
	virtual void BuildCpu() = 0;
	virtual void BuildMainBoard() = 0;
	virtual void BuildRam() = 0;
	virtual void BuildVideoCard() = 0;
	virtual Computer* GetResult() = 0;
};

class ThinkPadBuilder :public IBuilder {
public:
	ThinkPadBuilder() { m_pComputer = new Computer(); }
	void BuildCpu() override {
		m_pComputer->setmCpu("i5-6200U");
	}
	void BuildMainBoard() override {
		m_pComputer->setmMainBoard("Intel DH57DD");
	}
	void BuildRam() override {
		m_pComputer->setmRam("DDR4");
	}
	void BuildVideoCard() override {
		m_pComputer->setmVideoCard("NVDIA Geforce 920MX");
	}
	Computer* GetResult() override {
		return m_pComputer;
	}
private:
	//好习惯：成员变量前面m_，指针加上p
	Computer* m_pComputer;
};

class YogaBuilder :public IBuilder {
public:
	YogaBuilder() { m_pComputer = new Computer(); }
	void BuildCpu() override {
		m_pComputer->setmCpu("i7-7500U");
	}
	void BuildMainBoard() override {
		m_pComputer->setmMainBoard("Intel DP55KG");
	}
	void BuildRam() override {
		m_pComputer->setmRam("DDR5");
	}
	void BuildVideoCard() override {
		m_pComputer->setmVideoCard("NVDIA Geforce 940MX");
	}
	Computer* GetResult() override {
		return m_pComputer;
	}
private:
	//好习惯：成员变量前面m_，指针加上p
	Computer* m_pComputer;
};

class Director {
public:
	void Create(IBuilder* builder) {
		builder->BuildCpu();
		builder->BuildMainBoard();
		builder->BuildRam();
		builder->BuildVideoCard();
	}
};

//int main() {
//	//director没有什么动态调用的需要，于是静态和动态定义都可以
//	//Director* pDirector = new Director();
//	Director director;
//	IBuilder* pTPBuilder = new ThinkPadBuilder();
//	IBuilder* pYogaBuilder = new YogaBuilder();
//	director.Create(pTPBuilder);
//	director.Create(pYogaBuilder);
//
//	Computer* pTPComputer = pTPBuilder->GetResult();
//	Computer* pYogaComputer = pYogaBuilder->GetResult();
//
//
//	cout << "-----ThinkPad-----" << endl;
//	cout << "CPU: " << pTPComputer->getCpu() << endl;
//	cout << "Mainboard: " << pTPComputer->getMainBoard() << endl;
//	cout << "Ram: " << pTPComputer->getRam() << endl;
//	cout << "VideoCard: " << pTPComputer->getVideoCard() << endl;
//
//	cout << "-----Yoga-----" << endl;
//	cout << "CPU: " << pYogaComputer->getCpu() << endl;
//	cout << "Mainboard: " << pYogaComputer->getMainBoard() << endl;
//	cout << "Ram: " << pYogaComputer->getRam() << endl;
//	cout << "VideoCard: " << pYogaComputer->getVideoCard() << endl;
//
//	return 0;
//}