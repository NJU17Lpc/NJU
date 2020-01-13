#include <iostream>
#include <string>
using namespace std;

/*
�����û���Ҫ��Log��¼�������в�ͬ��Log���ͣ�FileLog, DatabaseLog; �в�ͬ��LogFactory���ͣ�FileLogFactory, DatabaseLogFactory
�����µ�Log���ͣ���Ҫ�̳�һ��Log��ͬʱҪ��չ�̳�һ��LogFactory
*/

/*
��������ģʽ ���壺
1���ֽж�̬����ģʽ
2���ഴ����ģʽ
3���������ඨ�崴����Ʒ����Ĺ����ӿڣ��������ฺ�����ɾ���Ĳ�Ʒ����
4��ͨ���������࣬��ȷ��ʵ�����ĸ������Ʒ�ࣨȥ���˾�̬�����и��ӵ��ж��߼���

������
1�����ĵĹ����ཫ���崴����������ȥ��
2�������ڲ��޸Ĺ�����ɫ������£������²�Ʒ
3��ϵͳ����µĲ�Ʒ����ֻ��Ҫ��������Ʒ�����һ�����幤�����󣬲����޸�ԭ�й�������
���Ͽ���ԭ��
4��ʵ�ʿ����У�һ�㽫��ֱ����new�������󣬶��ǰѾ�������д�������ļ�����
ͨ��java������ƣ���ȡXML��ʽ�������ļ���ͨ��XML����������ַ������ɶ���
	���������ƾ��ǣ�����ͨ��class c = class.forName("String");���string�������class����
	����Object obj = c.newInstance()������������ʾ���һ��ʵ��
	����ͨ�� �����ַ��� �õ����ʵ��
	�����õ�ʱ����һ��DocumentBuilderFactory����Dom�ĵ�����Ȼ�����doc.getElementsByTagName("className")
	������ǻ�ȡNodeValue������Class c = Class.forName(xxx), Object obj = c.newInstance()
�ͻ����õ�ʱ�򣬾�������PayMethodFactory factory = (PayMethodFactory)XMLUtil.getBean()

�ŵ㣺
1���û�ֻҪ���Ĳ�Ʒ��Ӧ�Ĺ���������Ҫ���Ĵ���ϸ�ڣ�Ҳ����֪�������Ʒ��������ע�⣬����Ҫ֪������������
2�������������������������ֲ�Ʒ������δ�����ϸ�ڱ���װ
3��ϵͳ�м����²�Ʒ������Ҫ�޸ĳ��󹤳��ͳ����Ʒ�Ľӿڣ�����Ҫ�޸Ŀͻ��ˣ�Ҳ�����޸��������幤���;����Ʒ�������µĲ�Ʒ�͹����ͺ���

ȱ�㣺
1����һ���²�Ʒʱ��Ҫ���ϲ�Ʒ��͹����࣬��ĸ���̤�壬������౻��������У�����ϵͳ����
2��������һ������㣬����ϵͳ�����Ժ�����Ѷ�
3��ʵ����Ҫ�õ�DOM������ȼ�����ʵ���Ѷȸ���

���ã�
1��һ���಻֪������Ҫ�Ķ�����ֻ࣬��Ҫ֪����������
2��һ����ͨ�����ָ࣬�������ĸ�����
3�����������������ί�и�ĳ�����๤�����ͻ���ʹ�ö����ʱ�򣬲������ĸ��������������������Ҫʱ��ָ̬��


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