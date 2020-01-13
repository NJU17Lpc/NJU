#include <iostream>
#include <string>
#include <map>
using namespace std;

/*
����Ҫ��ʼ����Ϸ��cs
����пֲ����Ӻͷ��־�Ӣ������Ӫ���ֲ�����(Terrorists)�ͷ��־�Ӣ(Counter Terrorists)������Ӫ
ÿ�������в�ͬ���񣬿ֲ�����Ҫָ��ʱ���ڰ�װC4�����������־�ӢҪ���C4
���Ҫ��ÿ����Ҵ���һ�����󣬻�ռ�úܴ��ڴ档����ֻ��ҪΪ�ֲ����Ӻͷ��־�Ӣ��������������Ҫ��ʱ�򷴸�ʹ��
������ڲ�״̬����ҵ����񣬲����ⲿ�����仯���ⲿ״̬������ҿ���ѡ���Լ�������
*/

/*
������
1����������̫���ʱ�����д��۹��ߣ������½�
2����Ԫģʽͨ��������ʵ����ͬ�������ƶ�������
3�����Թ������ͬ���ݽ��ڲ�״̬����Ҫ�ⲿ���������õ����ⲿ״̬
4����Ԫģʽͨ����Ϲ���ģʽ������һ����Ԫ������ά��һ����Ԫ�أ�ͨ����һ��HashMap���洢��ͬ�ڲ�״̬����Ԫ����
5����Ԫ����������ڲ�����һ��Ƚ�С������ʵ�ִ���ϸ���ȶ��������

���壺
1����Ϊ�ڲ�״̬�仯��С�����Զ�θ��úܷ���
2���ֽ�������ģʽ
3������ṹ��ģʽ

ʵ����
1�����������豸����̨�ն˼��������ͬһ̨�����豸�������Ϳ�������Ԫ������������·��������������
2����Ȼ�����豸�������Ƿ����ÿһ��������Ķ˿ڲ�ͬ�����ǰѶ˿ڳ�ȡ������Ϊ�ⲿ״̬

�ŵ㣺
1����������ڴ��ж�����������ͬ����ֻ����һ��
2���ⲿ״̬��Զ���������Ӱ���ڲ�״̬����Ԫ��������ڲ�ͬ�����б�����

ȱ�㣺
1��ϵͳ���Ӹ��ӣ���Ҫ�����ڲ�״̬���ⲿ״̬�������߼����ӻ�
2��Ϊ���ö�������Ԫ�����״̬��Ҫ�ⲿ�������Ƕ�ȡ�ⲿ״̬ʹ������ʱ��䳤

���ã�
1��ϵͳ�д�����ͬ�������ƵĶ���
2���󲿷ֶ��󶼿����ⲿ���������Խ��ⲿ״̬ע��
3��ά����Ԫ��ͦ�ķ���Դ������ظ�ʹ����Ԫ����ʱ����ֵ������Ԫģʽ

Ӧ�ã�
1���༭������У�һ��ͼƬ���ĵ��ж�γ��֣�ֻҪ����ͼƬ���ֵ�λ�ã��Ϳ���ʹ�ø�ͼƬ�����ط��ظ���ʾ
2��JDK��string��

��չ��
1��������Ԫģʽ
������Ԫ���󶼿��Թ��������ڷǹ��������Ԫ��
2��������Ԫģʽ
������Ԫʹ�����ģʽ������ϣ��γɸ�����Ԫģʽ
���CompositeComcreteFlyweight������������Ԫһ�����̳���Flyweight��ͬʱҲ��Ͻ���һ��Flyweight
���ָ�����Ԫ�����ܹ������ǿ��Էֽ�ɿɹ���ĵ�����Ԫ
3������ģʽ����
��̬����������Ԫ
���ģʽ���γɸ�����Ԫģʽ

*/

/*
д��ʱ��ע��
1����̬����ά����̬��Ԫ�� HashMap:flyweights
�����Ԫ�ذ���key����ô���ض�Ӧ��key-value;����������������µ�key-value����put��ȥ
2���ڲ�״̬�洢����Ԫ�ڲ�����������m_task,���ڴ��������ʱ���ȷ���ˣ��������������ȷ��
���ⲿ״̬�Ƕ���ָ���ģ����ɹ���ģ������ⲿ״̬�ɿͻ��˱��棬��Ҫ��ʱ���ٴ����ڲ���������������������û�ָ����
�ⲿ״̬����һ���ⲿ״̬����
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
	Terrorist() { m_task = "�������Ǳ�ը"; }

	virtual void assignWeapon(string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		cout << "�ֲ������õ�������:" + m_weapon + ", Task is" + m_task << endl;
	}
};

class CounterTerrorist :public IPlayer {
public:
	CounterTerrorist() { m_task = "����ը��"; }

	virtual void assignWeapon(string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		cout << "���־�Ӣ�õ�������:" + m_weapon + ", Task is" + m_task << endl;
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
				cout << "�����ֲ�����Terrorist" << endl;
				player = new Terrorist();
			}
			else if (type == "CT") {
				cout << "�������־�ӢCounterTerrorist" << endl;
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
//	//��ʵ��������е㲻ǡ������Ϊ���ֲ����ӹ���ͬһ�������ˡ������������ֳ�����ͬһ�����󣬾���java string
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