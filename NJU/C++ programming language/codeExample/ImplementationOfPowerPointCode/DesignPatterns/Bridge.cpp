#include <iostream>
#include <string>
using namespace std;

/*
���ڷ��������кܶ��������������\����ȵȣ����ɶ�Ӧ�Ŀ��ؿ���
���ڱ�������Ҫ�������ݣ������Ҳ������ſ���һ����

���壺
1�������󲿷�������ʵ�ֲ��ַ��룬ʹ���ǿ��Զ����ر仯
2���Ƕ���ṹģʽ

������
1�����󻯣�������ͬ���ʳ�ȡ�����γ���
2��ʵ�ֻ�����Գ��󻯸����ľ���ʵ��
3����������󻯺�ʵ�ֻ�֮�����Ͻ⿪������˵������֮��ǿ�����ĳ�������
��������ɫ֮��ļ̳й�ϵ�ĳɹ�����ϵ

���磺
1��һ��ë�ʣ���һ��ά���ϣ�����small pen/big pen/middle pen �̳���pen
��һ��ά���ϣ�����red/green/blue/white/black ��Щ��ɫ����pen����
2��һ����ƽ̨����������һ��ά���ϣ�������windowsVersion/UnixVersion/LinuxVersion�̳���OSVersion
��һ��ά���ϣ�����Ҫ�Զ��ָ�ʽ����: RMVB/MPEG/AVI������ʹ��һ��videoFile������OSVersion��

�ŵ㣺
1���������ӿ��Լ�ʵ��
2����ʵ���ⱳ�������ڶ�̳У����Ƕ�̳�Υ���˵�һְ��ԭ�򣬸����Բ�
�����Ž�ģʽ�Ǳȶ�̳и��õĽ������
3�������ϵͳ�Ŀ������ԣ�������չһ��ά�ȣ�������Ҫ�޸�ԭ��ϵͳ
4��ϵͳ�Կͻ�͸�������û�����ʵ��ϸ��

ȱ�㣺
1�������Ž�ģʽ������ϵͳ�����������Ѷ�
��Ϊ�����ڳ����������룬�����߶Գ��������ƱȽ���
2��Ҫ��ȷʶ���ϵͳ�����������仯��ά���е��ѣ�����ʹ�ø�ģʽ��һ�������

���û�����
1��ϵͳ��Ҫ�ڹ����ĳ��󻯽�ɫ�;��廯��ɫ֮�����Ӹ���������
�������������֮�佨����̬�̳й�ϵ�������ÿ�ִ�С��ë�ʶ�������Ӧ����ɫ���ࣩ
2�����󻯽�ɫ��ʵ�ֻ���ɫ������ �̳з�ʽ ������չ �� ���໥Ӱ�죡��
3��һ����������������仯��ά�ȣ�����Ҫ������չ
4�����󻯽�ɫ�;��廯��ɫ��Ҫ�����仯������������
5����ϣ��ʹ�ü̳У�������Ϊ���μ̳е�����ĸ�����������
������Ҫ���ϵͳ�������Ž�ģʽ

Ӧ�ã�
1��Java����ʹ��JVMʵ��ƽ̨���޹��ԣ������й���һ��ƽ̨��ƽ̨�кܶ�����(windows/unix)������Ҳ�кܶ�����
2��JDBC�������򣬽��ض����͵����ݿ⣬������һ��JavaӦ�ó���

ģʽ��չ��
1��������ģʽ���Ž�ģʽ����
����ƵĲ�ͬ�׶���:
�Ž�ģʽ����ϵͳ�ĳ�����ƣ������������仯ά�ȵ��࣬�ֳɳ��󻯺�ʵ�ֻ�������ɫ�������仯
����������֮����һЩ���ϵͳ����Эͬ���������Բ���������ģʽ
��һ������Ƴ��ڣ���ʱ���漰�ܶ�������ӿڣ����Կ���������ģʽ
2�����磬һ��������ʾ�������
һ��ά���ϣ��кܶ���ʾ��ʽ����Ϊ����ά��
��һ��ά�ȣ��кܶ�����Դ����Ϊʵ�ֻ�ά�ȣ����Զ�ȡ�ı�����
�����Ҫ����excel�����ݣ�����дһ�����������ڶ�ȡ


д��ʱ��ע�⣺
1���������ʵ�������ǵĽӿ�����ͦ���
2������������ά��һ��ʵ����Ķ���Ľӿ�����
3���������е���ʵ�����еķ��������ǳ�����Ҫ����Լ���ʵ����˫��
��˳���������ķ������Ӹ���

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