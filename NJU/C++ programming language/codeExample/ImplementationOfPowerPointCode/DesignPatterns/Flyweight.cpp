#include <iostream>
#include <string>
#include <map>
using namespace std;

/*
现在要开始打游戏，cs
玩家有恐怖分子和反恐精英两个阵营，恐怖分子(Terrorists)和反恐精英(Counter Terrorists)两个阵营
每个队伍有不同任务，恐怖分子要指定时间内安装C4并引爆，反恐精英要拆除C4
如果要对每个玩家创建一个对象，会占用很大内存。可以只需要为恐怖分子和反恐精英创建两个对象，需要的时候反复使用
这里的内部状态是玩家的任务，不随外部环境变化；外部状态比如玩家可以选择自己的武器
*/

/*
动机：
1、对象数量太多的时候，运行代价过高，性能下降
2、享元模式通过共享技术实现相同或者相似对象重用
3、可以共享的相同内容叫内部状态；需要外部环境来设置的是外部状态
4、享元模式通常结合工厂模式，创建一个享元工厂，维护一个享元池，通常是一个HashMap，存储相同内部状态的享元对象
5、享元对象包含的内部对象一般比较小，可以实现大量细粒度对象的重用

定义：
1、因为内部状态变化很小，所以多次复用很方便
2、又叫轻量级模式
3、对象结构型模式

实例：
1、共享网络设备，多台终端计算机连接同一台网络设备。这样就可以用享元工厂，创建出路由器、交换机等
2、虽然网络设备共享，但是分配给每一个计算机的端口不同，于是把端口抽取出来作为外部状态

优点：
1、极大减少内存中对象数量，相同对象只保存一份
2、外部状态相对独立，而不影响内部状态，享元对象可以在不同环境中被共享

缺点：
1、系统更加复杂，需要分离内部状态和外部状态，程序逻辑复杂化
2、为了让对象共享，享元对象的状态需要外部化，于是读取外部状态使得运行时间变长

适用：
1、系统有大量相同或者相似的对象
2、大部分对象都可以外部化，即可以将外部状态注入
3、维护享元池挺耗费资源，多次重复使用享元对象时，才值得用享元模式

应用：
1、编辑器软件中，一个图片在文档中多次出现，只要设置图片出现的位置，就可以使得该图片在许多地方重复显示
2、JDK的string类

扩展：
1、单纯享元模式
所有享元对象都可以共享，不存在非共享具体享元类
2、复合享元模式
单纯享元使用组合模式加以组合，形成复合享元模式
这个CompositeComcreteFlyweight和其他具体享元一样，继承自Flyweight，同时也组合进了一个Flyweight
这种复合享元本身不能共享，但是可以分解成可共享的单纯享元
3、其他模式联用
静态工厂返回享元
组合模式，形成复合享元模式

*/

/*
写的时候注意
1、静态工厂维护静态享元池 HashMap:flyweights
如果享元池包括key，那么返回对应的key-value;如果不包括，创建新的key-value，并put进去
2、内部状态存储在享元内部，例子中是m_task,他在创建对象的时候就确定了，根据输入的类型确定
而外部状态是额外指定的，不可共享的，这种外部状态由客户端保存，需要的时候再传入内部。比如这里的武器，是用户指定的
外部状态与另一个外部状态独立
*/
class IPlayer {
public:
	virtual ~IPlayer()
	{

	}

	virtual void assignWeapon(string weapon) = 0;

	virtual void mission() = 0;

protected:
	string m_task;
	string m_weapon;

};

class Terrorist :public IPlayer {
public:
	Terrorist() { m_task = "艺术就是爆炸"; }

	virtual void assignWeapon(string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		cout << "恐怖分子拿到了武器:" + m_weapon + ", Task is" + m_task << endl;
	}
};

class CounterTerrorist :public IPlayer {
public:
	CounterTerrorist() { m_task = "拆了炸弹"; }

	virtual void assignWeapon(string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		cout << "反恐精英拿到了武器:" + m_weapon + ", Task is" + m_task << endl;
	}
};

class PlayerFactory {
public:
	static IPlayer* getPlayer(string type) {
		IPlayer* player = NULL;
		if (m_map.find(type) != m_map.end()) {
			player = m_map[type];
		}
		else {
			if (type == "T") {
				cout << "创建恐怖分子Terrorist" << endl;
				player = new Terrorist();
			}
			else if (type == "CT") {
				cout << "创建反恐精英CounterTerrorist" << endl;
				player = new CounterTerrorist();
			}
			else {
				cout << "not valid type" << endl;
			}
			m_map.insert(make_pair(type, player));
		}
		return player;

	}

private:
	static map<string, IPlayer*> m_map;
};
map<string, IPlayer*> PlayerFactory::m_map = map<string, IPlayer*>();


//int main() {
//
//	//其实这个例子有点不恰当，因为最后恐怖分子共享同一种武器了。但看可以体现出共享同一个对象，就像java string
//	static string s_playerType[2] = { "T", "CT" };
//	static string s_weapons[4] = { "AK-47","Maverick","Gut Knife","Desert Eagle" };
//
//	for (int i = 0; i < 10; i++) {
//		IPlayer* player = PlayerFactory::getPlayer(s_playerType[i % 2]);
//		player->assignWeapon(s_weapons[i % 4]);
//		player->mission();
//	}
//
//	return 0;
//}