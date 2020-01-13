#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
const std::string c_stateToStrCourier[] = { "收到", "验证可达性", "分配人员", "派送包裹", "获取交货确认", "完成" };
const std::string c_stateToStrVendor[] = { "收到", "确认库存", "从仓库得到物品", "包装", "联系快递员", "完成" };
const std::string c_stateToStrOrderTeam[] = { "收到", "确认付款", "联系供应商", "完成" };
const int c_nMsec = 300;

/*
现在假设要在狗东网购，我作为用户，只想点一下晚一年（不是
就是那些具体下单、收获、送货任务我不想自己去了解
如果要我自己去了解，我就要去主动找人签订单，联系快递公司
当然我也可以单独委托一个具体的公司，让他帮我做下订单后续的事情，但这个与我们设立一个外观角色本质一样的

动机：
用户之和外观角色直接交互，用户与子系统之间的复杂关系，外观角色来实现

定义：
1、外部和子系统通信，必须通过一个统一的外观对象进行
2、从而为子系统提供了一个一致的界面
3、是对象结构型模式

写的时候注意：
1、外观角色Facade类，持有不同子系统的实例，调用子系统的方法
2、子系统角色，这个子系统实际上会很复杂多样
3、这里的代码是通过一个m_nState控制此时使用哪一个子系统
而子系统内部也通过一个state控制执行状态

分析：
1、体现单一职责原则
子系统之间的通信和相互依赖很小，同时外观对象，为子系统的访问提供了简单而单一的入口
这个单一和简单入口，就体现了单一职责
2、体现迪米特法则
引入新的外观类，降低了原有系统的复杂度
同时降低客户类与子系统的耦合，耦合的降低可见迪米特
3、提高了客户端使用的便捷性，于是客户端不用关心系统的细节

应用：
1、电源总开关，一次性开很多电源
2、文件加密，提供统一的加密外观类，完成文件的读取、加密、保存
不需要与每一个类交互
EntryFacade持有一个FileReader\Cipher\Writer对象，对外提供一个fileEncrypt方法
3、JDBC数据库操作，持有Connection类和Statement类
4、Session外观模式，不懂

优点：
1、对客户屏蔽子系统，使用起来容易，客户代码简单，关联代码少
2、实现子系统与客户之间的松耦合，子系统变化只会影响外观类
3、降低大型软件系统中的编译依赖性，简化系统再不同平台之间的移植过程
因为编译一个子系统，就不需要编译其他子系统。一个变了，其他不会受到影响
4、只提供了访问子系统的统一入口，不影响用户使用子系统类

缺点：
1、不能很好限制客户使用子系统类
但另一方面，对客户访问子系统如果做太多限制，就会减少可变性和灵活性
2、如果不引入抽象外观类，增加新的子系统可能要修改外观类或者客户端代码
违背开闭原则！！

适用：
1、要为复杂子系统提供简单接口时，可用外观模式
2、客户程序与多个子系统之间存在很大依赖性，通过外观类可以便于解耦
提供子系统独立性和可移植性
3、层次化结构中，可以使用外观类定义系统每层的入口
层与层之间没有直接联系，而是通过外观类建立联系，降低耦合

模式扩展：
1、通常只要一个外观类，于是设计为单例，节约资源
但一个大系统给可以有多个外观类，复杂不同功能
2、千万不要通过继承一个外观类，为子系统增加新行为
外观本来就是为子系统提供集中并简化的接口，而不是加入新的行为
新行为应该用新的子系统类
3、迪米特法则（废话）
外观对象，充当客户与子系统之间第三者
客户与子系统相互作用被外观取代
4、抽象外观类
外观模式违背开闭原则！！因为增加子系统或移除子系统需要修改外观类
新的业务需求，可以不修改外观类，让原有外观类关联新的子系统对象
只需要修改配置文件

*/

class OrderTeam {
public:
	void submitRequest() {
		m_nState = 0;
	}

	bool checkStatus() {
		cout << "订单团队-当前状态：" << c_stateToStrOrderTeam[m_nState] << endl;
		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}
private:
	enum States {
		Received,
		VerifyPayment,
		ContactVendor,
		Complete
	};
	int m_nState;
};

// 供应商
class Vendor
{
public:
	void submitRequest() {
		m_nState = 0;
	}

	// 检测状态
	bool checkStatus() {
		std::cout << "供应商 - 当前状态：" << c_stateToStrVendor[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // 收到
		VerifyInventory,  // 确认库存
		GetItemFromWareHouse,  // 从仓库得到物品
		PackItem,  // 包装
		ContactCourier,  // 联系快递员
		Send,//发货
		Complete  // 完成
	};
	int m_nState;
};

// 快递员
class Courier
{
public:
	// 将请求转发给快递员
	void submitRequest() {
		m_nState = 0;
	}

	// 检测状态
	bool checkStatus() {
		std::cout << "快递员 - 当前状态：" << c_stateToStrCourier[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // 收到
		VerifyReachbility,  // 验证可达性
		AssignPerson,  // 分配人员
		DispatchPackage,  // 派送包裹
		GetDeliveryConfirmation,  // 获取交货确认
		Complete  // 完成
	};
	int m_nState;
};

class OnlineShoppingFacade{
public:
	OnlineShoppingFacade() { m_nCount = 0; }

	void submitRequest() { m_nState = 0; }

	int getFollowUpNum() {
		return m_nCount;
	}

	bool checkStatus() {
		switch (m_nState)
		{
		case Received:
			m_nState++;
			m_order.submitRequest();
			cout << "**提交给订单团队，跟踪次数：" << m_nCount << "**" << endl;
			break;
		case SubmittedToOrderTeam:
			//订单完成验证后，再进行这一步，向供应商提出请求
			if (m_order.checkStatus()) {
				m_nState++;
				m_vendor.submitRequest();
				cout << "**提交给供应商，跟踪次数：" << m_nCount << "**" << endl;
			}
			break;
		case SubmittedToVendor:
			if (m_vendor.checkStatus()) {
				m_nState++;
				m_courier.submitRequest();
				cout << "**提交给快递员，跟踪次数：" << m_nCount << "**" << endl;
			}
			break;
		case SubmittedToCourier:
			if (m_courier.checkStatus())
				return true;
		default:
			break;
		}

		m_nCount++;
		return false;
	}

private:
	enum States
	{
		Received,
		SubmittedToOrderTeam,
		SubmittedToVendor,
		SubmittedToCourier
	};
	int m_nState;
	int m_nCount;

	OrderTeam m_order;
	Vendor m_vendor;
	Courier m_courier;

};

//int main() {
//	OnlineShoppingFacade facade;
//
//	facade.submitRequest();
//
//	while (!facade.checkStatus());
//
//	cout << "**完成订单，跟踪次数：" << facade.getFollowUpNum() << "**";
//
//	return 0;
//}