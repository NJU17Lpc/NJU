#include<iostream>
#include <string>
using namespace std;

/*
���������кܶ�ϵ�еĵ��ԣ�ÿ̨���Ի�����װ�ṹ����һ���ģ�CPU+�Կ�+����+�ڴ�����ȥ�ͺ�
��ʵ������Ĺ��̶���࣬���Ϊÿһ���ͺ�����һ����װ���̣�����һ��ӵ�кܶ��ͺŵĵ��ԵĴ�˾���������̺ܲ�����
�����б�ҪΪ����ϵ��ָ��һ��ͳһ����װ����

����������װ���̷ֿ���һ��һ���������Ӷ���

�Ƕ��󴴽���ģʽ
*/

/*
�ܶิ�Ӷ��󣬴��ںܶ���������������ĳЩ���Ը�ֵ��Ҫ����ĳ���ض�˳��
�����߷��ص��ǽ�����ϵ�������Ʒ���û�����Ҫ���Ĳ�Ʒ�����Ժ���װ��ʽ

���ָ���߸������û����������̣�������Ʋ�Ʒ�����ɹ���
�ͻ�ֻҪ�ṩ�������͸�ָ���ߣ�ָ���߾ͻᱻ����ȥװ��
��������˿ͻ�����Ҫ���ľ�����װ���̣�ֻҪ֪�����;���

Ӧ�ã�
KFC�ײ���װ����

�ŵ㣺
�ͻ��˲���Ҫ֪����Ʒ�ڲ�ϸ�ڣ�����Ʒ�봴�����̽��������ͬ�������̿��Դ�����ͬ��Ʒ����
���Է����滻���彨���߻�ò�ͬ��Ʒ����
���Ը��Ӿ�ϸ���Ʋ�Ʒ�������̣������Ӳ�Ʒ��������ֽ�
�����µ�builder����Ҫ�޸�ԭ���Ĵ��룬��Ϊdirector����Գ���builder��̵ģ����Ͽ���ԭ��

ȱ�㣺
�����ߵĲ�Ʒһ����кܶ๲ͬ�㣬������ƣ������Ʒ֮�����ܴ󣬲��ʺϽ�����
�����Ʒ�ڲ��仯����ס�Ǳ仯���ܸ��ӣ��б�Ҫ����ܶ���彨���ߣ���Բ�ͬ��������Ʒ������ϵͳ����Ӵ�

���ã�
���ɶ����и����ڲ��ṹ���仯���Ǻܸ��ӣ���ͬʱ���ǵ������໥��������һ��˳��
����Ĵ������̶����ڴ������������࣬����������ߣ��������Ҫָ���ߡ������߲����Լ���ֻ�ṩ���Լ��ķ���
���븴�Ӷ���Ĵ�����ʹ�ã�������ͬ�������������ڲ�ͬ��Ʒ

������Ϸ�У������ɫ�������壬��װ��װ���ȡ��ʺ��ý����߽�����ơ�
ͨ����ͬ�����ߴ�����ͬ��������

���Լ򻯣�
1��ֻ��һ��������builderʱ������ʡȥIBuilder
2����1������£���������ȥָ���ߣ���ʱ�����߳е������ָ������ְ��

�Աȳ��󹤳�ģʽ��
1�������߷�����װ�õ�������Ʒ�����󹤳�����һϵ����ز�Ʒ�����ɲ�Ʒ��
2��������ͨ��ָ�����ȡ�������󣬲�ֱ�ӵ��ý����ߵķ���������������װ�Ĺ���
����ģʽ�У��ͻ���ʵ����������Ȼ����ù���������ȡ��Ҫ�Ĳ�Ʒ����
3��������ģʽ��������װ��������ְ������װ����������������
���󹤳�ģʽ�����������������������һ����Ʒ��Ĳ�Ʒ

*/

/*
д��ʱ��ע��
��Ҫдһ������Ĳ�Ʒ�������ƷĿ��Ҳ�����ü̳У�����һ��Ҫ�ǿ�װ���
Ȼ��һ��IBuilder�������װ�����ʹ�õķ�����������װ��������Ķ���
����һ��Director������һ��Builder���Լ���֯װ�����
�ͻ���ֻ��Ҫָ��������ʲôbuilder��builder�Լ��ᴴ����˽�в�Ʒ
Ȼ��ͻ��˰�builder����director�������ʹ��һ����Ʒ���࣬����director�����˵ķ���builder����Ĳ�Ʒ
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
	//����������ʽͦ�����
	string m_strCpu;
	string m_strMainboard;
	string m_strRam;
	string m_strVideoCard;
};

//�ӿ�������I��ʼ
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
	//��ϰ�ߣ���Ա����ǰ��m_��ָ�����p
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
	//��ϰ�ߣ���Ա����ǰ��m_��ָ�����p
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
//	//directorû��ʲô��̬���õ���Ҫ�����Ǿ�̬�Ͷ�̬���嶼����
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