#include <iostream>
#include <string>
using namespace std;

/*
现在我们想充值流量卡，总不能直接去移动公司吧。移动公司把职责放给代理点，客户直接与代理点打交道
*/

/*
动机：
1、一个客户不想或者不能直接引用一个对象，此时可以通过“代理”实现间接引用
2、想通过代理在客户端与目标之间起到中介作用，并且可以通过这个代理，去掉客户不能看见的内容，或者加上额外服务(比如充钱不能太少)
3、引入新的代理对象，作为对真实对象操作的替身

定义：
1、给某个对象提供一个代理，代理对象控制对原对象引用
2、对象结构型模式

应用：
1、论坛权限管理
已注册的会员和游客对论坛帖子的访问权限不同
2、数学运算代理
比如远程机器上实现了复杂的加减乘除，可以在本地设置一个代理

优点：
1、协调调用者和被调用者，降低耦合度
2、客户端可以访问远程机器上的对象，利用远程机器的高性能
3、虚拟代理通过小对象代表大对象，减少系统资源消耗，对系统进行优化，提高运行速度
4、保护代理可以控制对真实对象的使用权限

缺点：
1、客户端与真实主题之间增加了代理对象，因此有时代理模式会造成请求的处理速度变慢
2、代理模式额外的工作，导致代理模式的实现会很复杂

常见的代理模式有几种类型：
1、Remote 远程代理:
有一个不同地址空间的对象，想要访问我的主机，我可以为他提供我自己的代理
2、virtual 虚拟代理:
一种内存节省技术
如果要创建资源消耗很大的对象，可以先创建一个小的对象，需要时再创建真实对象
加速了系统的启动时间
比如用户浏览器访问大图的时候，先试用一个线程加载小图片，后台另一个线程将大图片加载到客户端；即不先加载真实的大图，这个代理先发小图
3、copy-on-write 代理:
对象深克隆很消耗资源，我可以把克隆对象的操作，延迟到真正用他的时候
4、protect or Access 代理:
控制不同权限的访问
5、cache代理:
为同一目标的操作提供临时缓存
6、Firewall防火墙代理:
保护目标对象
7、Smart Reference 智能引用代理:
一个对象被引用时，通过中间的代理，记录下对象被引用的次数

应用：
1、java RMI
不同jvm之间TCP连接
2、很多分布式应用
web service, EJB 等，本地有一个桩代理，客户端通过桩进行远程调用，不需要直接和远程应用交互





*/

/*
写的时候注意：
1、Proxy和realSubject都继承自Subject, Proxy持有对RealSubject的引用
2、同时Proxy中调用RealSubject中方法时，可以在调用前后加上一些限定方法
3、client直接持有proxy，不需要考虑realSubject

*/

//电信运行商，命名时注意对接口类加上I
class ITelco {
public:
	virtual ~ITelco(){}

	virtual void Recharge(int money) = 0;
};

class CMCC: public ITelco
{
public:
	void Recharge(int money) override {
		cout << "充值:" << money << "元" << endl;
	}
};

class Proxy: public ITelco
{
public:
	Proxy() :m_pCMCC(NULL) {};
	~Proxy() { delete m_pCMCC; };
	void Recharge(int money) override {
		if (money >= 50) {
			if (m_pCMCC == NULL) {
				m_pCMCC = new CMCC();
			}
			m_pCMCC->Recharge(money);
		}
		else {
			cout << "才充" << money << "元，" << "充的钱太少了，多充点钱可以更好上网，才能上王者哦" << endl;
		}
	}

private:
	CMCC* m_pCMCC;
};


//int main() {
//	Proxy* proxy = new Proxy();
//	proxy->Recharge(20);
//	proxy->Recharge(200);
//
//
//	return 0;
//}