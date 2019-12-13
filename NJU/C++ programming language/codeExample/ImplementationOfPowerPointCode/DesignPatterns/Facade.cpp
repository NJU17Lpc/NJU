#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
const std::string c_stateToStrCourier[] = { "�յ�", "��֤�ɴ���", "������Ա", "���Ͱ���", "��ȡ����ȷ��", "���" };
const std::string c_stateToStrVendor[] = { "�յ�", "ȷ�Ͽ��", "�Ӳֿ�õ���Ʒ", "��װ", "��ϵ���Ա", "���" };
const std::string c_stateToStrOrderTeam[] = { "�յ�", "ȷ�ϸ���", "��ϵ��Ӧ��", "���" };
const int c_nMsec = 300;

/*
���ڼ���Ҫ�ڹ�������������Ϊ�û���ֻ���һ����һ�꣨����
������Щ�����µ����ջ��ͻ������Ҳ����Լ�ȥ�˽�
���Ҫ���Լ�ȥ�˽⣬�Ҿ�Ҫȥ��������ǩ��������ϵ��ݹ�˾
��Ȼ��Ҳ���Ե���ί��һ������Ĺ�˾�������������¶������������飬���������������һ����۽�ɫ����һ����

������
�û�֮����۽�ɫֱ�ӽ������û�����ϵͳ֮��ĸ��ӹ�ϵ����۽�ɫ��ʵ��

���壺
1���ⲿ����ϵͳͨ�ţ�����ͨ��һ��ͳһ����۶������
2���Ӷ�Ϊ��ϵͳ�ṩ��һ��һ�µĽ���
3���Ƕ���ṹ��ģʽ

д��ʱ��ע�⣺
1����۽�ɫFacade�࣬���в�ͬ��ϵͳ��ʵ����������ϵͳ�ķ���
2����ϵͳ��ɫ�������ϵͳʵ���ϻ�ܸ��Ӷ���
3������Ĵ�����ͨ��һ��m_nState���ƴ�ʱʹ����һ����ϵͳ
����ϵͳ�ڲ�Ҳͨ��һ��state����ִ��״̬

������
1�����ֵ�һְ��ԭ��
��ϵͳ֮���ͨ�ź��໥������С��ͬʱ��۶���Ϊ��ϵͳ�ķ����ṩ�˼򵥶���һ�����
�����һ�ͼ���ڣ��������˵�һְ��
2�����ֵ����ط���
�����µ�����࣬������ԭ��ϵͳ�ĸ��Ӷ�
ͬʱ���Ϳͻ�������ϵͳ����ϣ���ϵĽ��Ϳɼ�������
3������˿ͻ���ʹ�õı���ԣ����ǿͻ��˲��ù���ϵͳ��ϸ��

Ӧ�ã�
1����Դ�ܿ��أ�һ���Կ��ܶ��Դ
2���ļ����ܣ��ṩͳһ�ļ�������࣬����ļ��Ķ�ȡ�����ܡ�����
����Ҫ��ÿһ���ཻ��
EntryFacade����һ��FileReader\Cipher\Writer���󣬶����ṩһ��fileEncrypt����
3��JDBC���ݿ����������Connection���Statement��
4��Session���ģʽ������

�ŵ㣺
1���Կͻ�������ϵͳ��ʹ���������ף��ͻ�����򵥣�����������
2��ʵ����ϵͳ��ͻ�֮�������ϣ���ϵͳ�仯ֻ��Ӱ�������
3�����ʹ������ϵͳ�еı��������ԣ���ϵͳ�ٲ�ͬƽ̨֮�����ֲ����
��Ϊ����һ����ϵͳ���Ͳ���Ҫ����������ϵͳ��һ�����ˣ����������ܵ�Ӱ��
4��ֻ�ṩ�˷�����ϵͳ��ͳһ��ڣ���Ӱ���û�ʹ����ϵͳ��

ȱ�㣺
1�����ܺܺ����ƿͻ�ʹ����ϵͳ��
����һ���棬�Կͻ�������ϵͳ�����̫�����ƣ��ͻ���ٿɱ��Ժ������
2������������������࣬�����µ���ϵͳ����Ҫ�޸��������߿ͻ��˴���
Υ������ԭ�򣡣�

���ã�
1��ҪΪ������ϵͳ�ṩ�򵥽ӿ�ʱ���������ģʽ
2���ͻ�����������ϵͳ֮����ںܴ������ԣ�ͨ���������Ա��ڽ���
�ṩ��ϵͳ�����ԺͿ���ֲ��
3����λ��ṹ�У�����ʹ������ඨ��ϵͳÿ������
�����֮��û��ֱ����ϵ������ͨ������ཨ����ϵ���������

ģʽ��չ��
1��ͨ��ֻҪһ������࣬�������Ϊ��������Լ��Դ
��һ����ϵͳ�������ж������࣬���Ӳ�ͬ����
2��ǧ��Ҫͨ���̳�һ������࣬Ϊ��ϵͳ��������Ϊ
��۱�������Ϊ��ϵͳ�ṩ���в��򻯵Ľӿڣ������Ǽ����µ���Ϊ
����ΪӦ�����µ���ϵͳ��
3�������ط��򣨷ϻ���
��۶��󣬳䵱�ͻ�����ϵͳ֮�������
�ͻ�����ϵͳ�໥���ñ����ȡ��
4�����������
���ģʽΥ������ԭ�򣡣���Ϊ������ϵͳ���Ƴ���ϵͳ��Ҫ�޸������
�µ�ҵ�����󣬿��Բ��޸�����࣬��ԭ�����������µ���ϵͳ����
ֻ��Ҫ�޸������ļ�

*/

class OrderTeam {
public:
	void submitRequest() {
		m_nState = 0;
	}

	bool checkStatus() {
		cout << "�����Ŷ�-��ǰ״̬��" << c_stateToStrOrderTeam[m_nState] << endl;
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

// ��Ӧ��
class Vendor
{
public:
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "��Ӧ�� - ��ǰ״̬��" << c_stateToStrVendor[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyInventory,  // ȷ�Ͽ��
		GetItemFromWareHouse,  // �Ӳֿ�õ���Ʒ
		PackItem,  // ��װ
		ContactCourier,  // ��ϵ���Ա
		Send,//����
		Complete  // ���
	};
	int m_nState;
};

// ���Ա
class Courier
{
public:
	// ������ת�������Ա
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "���Ա - ��ǰ״̬��" << c_stateToStrCourier[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyReachbility,  // ��֤�ɴ���
		AssignPerson,  // ������Ա
		DispatchPackage,  // ���Ͱ���
		GetDeliveryConfirmation,  // ��ȡ����ȷ��
		Complete  // ���
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
			cout << "**�ύ�������Ŷӣ����ٴ�����" << m_nCount << "**" << endl;
			break;
		case SubmittedToOrderTeam:
			//���������֤���ٽ�����һ������Ӧ���������
			if (m_order.checkStatus()) {
				m_nState++;
				m_vendor.submitRequest();
				cout << "**�ύ����Ӧ�̣����ٴ�����" << m_nCount << "**" << endl;
			}
			break;
		case SubmittedToVendor:
			if (m_vendor.checkStatus()) {
				m_nState++;
				m_courier.submitRequest();
				cout << "**�ύ�����Ա�����ٴ�����" << m_nCount << "**" << endl;
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
//	cout << "**��ɶ��������ٴ�����" << facade.getFollowUpNum() << "**";
//
//	return 0;
//}