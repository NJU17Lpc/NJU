#include <iostream>
#include <string>
using namespace std;

/*
现在房间里面有很多电器，包括灯泡\电风扇等，他由对应的开关控制
现在比如我想要换掉灯泡，但是我不想连着开关一换掉

定义：
1、将抽象部分与他的实现部分分离，使他们可以独立地变化
2、是对象结构模式

分析：
1、抽象化：将对象共同性质抽取出来形成类
2、实现化：针对抽象化给出的具体实现
3、脱耦：将抽象化和实现化之间的耦合解开，或者说将他们之间强关联改成弱关联
将两个角色之间的继承关系改成关联关系

例如：
1、一个毛笔，他一个维度上，可有small pen/big pen/middle pen 继承自pen
另一个维度上，他有red/green/blue/white/black 这些颜色，被pen关联
2、一个跨平台播放器，他一个维度上，可以有windowsVersion/UnixVersion/LinuxVersion继承自OSVersion
另一个维度上，他需要对多种格式解码: RMVB/MPEG/AVI，于是使用一个videoFile关联到OSVersion类

优点：
1、分离抽象接口以及实现
2、其实问题背景类似于多继承，但是多继承违背了单一职责原则，复用性差
于是桥接模式是比多继承更好的解决方案
3、提高了系统的可扩充性，任意扩展一个维度，都不需要修改原有系统
4、系统对客户透明，对用户隐藏实现细节

缺点：
1、引入桥接模式会增加系统的理解与设计难度
因为关联在抽象类中引入，开发者对抽象进行设计比较难
2、要正确识别出系统中两个独立变化的维度有点难，于是使用该模式有一点局限性

适用环境：
1、系统需要在构件的抽象化角色和具体化角色之间增加更多的灵活性
避免在两个层次之间建立静态继承关系（比如对每种大小的毛笔都建立对应的颜色子类）
2、抽象化角色和实现化角色可以用 继承方式 独立扩展 而 不相互影响！！
3、一个类存在连个独立变化的维度，都需要进行扩展
4、抽象化角色和具体化角色需要独立变化，被独立管理
5、不希望使用继承，或者因为多层次继承导致类的个数快速增加
有这样要求的系统可以用桥接模式

应用：
1、Java程序使用JVM实现平台的无关性，程序中关联一个平台，平台有很多子类(windows/unix)，程序也有很多子类
2、JDBC驱动程序，将特定类型的数据库，关联到一个Java应用程序

模式扩展：
1、适配器模式与桥接模式联用
在设计的不同阶段中:
桥接模式用于系统的初步设计，将两个独立变化维度的类，分成抽象化和实现化两个角色，独立变化
初步设计完成之后，有一些类和系统不能协同工作，可以采用适配器模式
另一方面设计初期，有时候涉及很多第三方接口，可以考虑适配器模式
2、例如，一个用于显示报表的类
一个维度上，有很多显示方式，作为抽象化维度
另一个维度，有很多数据源，作为实现化维度，可以读取文本数据
但如果要接受excel的数据，可以写一个适配器便于读取


写的时候注意：
1、抽象类和实现类他们的接口区别挺大的
2、抽象类里面维护一个实现类的对象的接口引用
3、抽象类中调用实现类中的方法，于是抽象类要兼顾自己和实现类双方
因此抽象类里面的方法更加复杂

*/

class IElectricalEquipment {
public:
	virtual ~IElectricalEquipment(){}

	virtual void PowerOn() = 0;

	virtual void PowerOff() = 0;
};

class Light : public IElectricalEquipment {
public:
	virtual void PowerOn() override {
		cout << "light is on" << endl;
	}

	virtual void PowerOff() override {
		cout << "light is off" << endl;
	}
};

class Fan :public IElectricalEquipment {
public:
	virtual void PowerOn() override {
		cout << "fan is on" << endl;
	}
	virtual void PowerOff() override {
		cout << "fan is off" << endl;
	}
};

class ISwitch {
public:
	ISwitch(IElectricalEquipment* ee) { m_pEe = ee; }
	virtual ~ISwitch()
	{

	}

	virtual void SwitchOn() = 0;
	virtual void SwitchOff() = 0;
protected:
	IElectricalEquipment* m_pEe;
};

class PullChainSwitch:public ISwitch
{
public:
	PullChainSwitch	(IElectricalEquipment* ee):ISwitch(ee){}

	virtual void SwitchOn() override {
		cout << "Switch on the equipment with a pull chain switch" << endl;
		m_pEe->PowerOn();
	}

	virtual void SwitchOff() override {
		cout << "Switch off the equipment with a pull chain switch" << endl;
		m_pEe->PowerOff();
	}

};

class TwoPositionSwitch :public ISwitch
{
public:
	TwoPositionSwitch(IElectricalEquipment* ee) :ISwitch(ee) {}

	virtual void SwitchOn() override {
		cout << "Switch on the equipment with a Two Position switch" << endl;
		m_pEe->PowerOn();
	}

	virtual void SwitchOff() override {
		cout << "Switch off the equipment with a Two Position switch" << endl;
		m_pEe->PowerOff();
	}

};


//int main() {
//	IElectricalEquipment* light = new Light();
//	IElectricalEquipment* fan = new Fan();
//
//	ISwitch* pullChain = new PullChainSwitch(light);
//	ISwitch* twoPosition = new TwoPositionSwitch(fan);
//
//	pullChain->SwitchOn();
//	pullChain->SwitchOff();
//
//	twoPosition->SwitchOn();
//	twoPosition->SwitchOff();
//
//
//	return 0;
//}