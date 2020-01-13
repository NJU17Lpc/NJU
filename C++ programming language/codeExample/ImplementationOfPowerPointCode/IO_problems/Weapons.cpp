#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class Weapon {

public:
	Weapon(int id, string name, int arrivalTime, int needTime, int priority) {
		m_id = id;
		m_name = name;
		m_arriveTime = arrivalTime;
		m_needTime = needTime;
		m_priority = priority;
		wLog.push_back(to_string(id) + " " + name + " " + to_string(arrivalTime) + " " + to_string(needTime) + " " + to_string(priority));
	}
	int getId() {
		return m_id;
	}
	void descNeedTime() {
		m_needTime--;
	}
	int getNeedTime() {
		return m_needTime;
	}
	int getArrivalTime() {
		return m_arriveTime;
	}
	int getPriority() {
		return m_priority;
	}
	vector<string> getLog() {
		return wLog;
	}

private:
	int m_id;
	string m_name;
	int m_arriveTime;
	int m_needTime;
	int m_priority;
	vector<string> wLog;
};

bool cmp(Weapon* w1, Weapon* w2) {
	if (w1->getNeedTime() < w2->getNeedTime()) {
		return true;
	}
	else if (w1->getNeedTime() == w2->getNeedTime()) {
		if (w1->getPriority() > w2->getPriority()) {
			return true;
		}
		else if (w1->getPriority() == w2->getPriority()) {
			return w1->getArrivalTime() < w2->getArrivalTime();
		}
	}
	return false;
}


class AoEn {
public:
	AoEn():m_curTime(0){}
	void addWeapon(Weapon* newWeapon) {
		allWeapons.push_back(newWeapon);
	}
	void startSchedule() {
		while (true)
		{
			checkState();
			doMake();
			changeTime();
			if (comedWeapons.size() == 0 && allWeapons.size() != 0) {
				continue;
			}
			if (allWeapons.size() == 0 && comedWeapons.size()==0) {
				break;
			}
		}

	}

	void displayLog() {
		for (int i = 0; i < log.size(); i++) {
			for (int j = 0; j < log[i].size(); j++) {
				cout << log[i][j] << " ";
			}
			cout << endl;
		}

	}

private:
	vector<vector<string>> log;

	void checkState() {

		//把到达时间到了的武器放到指定地方
		for (int i = 0; i < allWeapons.size(); i++) {
			if (allWeapons[i]->getArrivalTime() == m_curTime) {
				comedWeapons.push_back(allWeapons[i]);
				deleteWeaponFromAll(allWeapons[i]);
			}
		}

		//如果正在做的武器到时间了，就扔掉
		if (m_curWeapon != NULL) {
			if (m_curWeapon->getNeedTime() == 0) {
				log.push_back(m_curWeapon->getLog());
				deleteWeaponFromComed(m_curWeapon);
				m_curWeapon = NULL;
			}
		}
	}

	void doMake() {
		//对锻造时间和优先级做排序
		if (comedWeapons.size() == 0) {
			return;
		}
		sort(comedWeapons.begin(), comedWeapons.end(), cmp);
		if (m_curWeapon == NULL) {
			m_curWeapon = comedWeapons[0];
		}
		else if (m_curWeapon->getId() != comedWeapons[0]->getId()) {
			m_curWeapon = comedWeapons[0];
		}

	}

	void changeTime() {
		m_curTime++;
		if (m_curWeapon != NULL) {
			m_curWeapon->descNeedTime();
		}

	}


	void deleteWeaponFromAll(Weapon* weapon) {
		int id = weapon->getId();
		for (auto it = allWeapons.begin(); it != allWeapons.end(); ) {
			if ((*it)->getId() == id) {
				it = allWeapons.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void deleteWeaponFromComed(Weapon* weapon) {
		int id = weapon->getId();
		for (auto it = comedWeapons.begin(); it != comedWeapons.end(); ) {
			if ((*it)->getId() == id) {
				it = comedWeapons.erase(it);
			}
			else {
				++it;
			}
		}
	}

	int m_curTime;
	Weapon* m_curWeapon;
	vector<Weapon*> allWeapons;
	vector<Weapon*> comedWeapons;
};




AoEn aoen;

void initTask(vector<string> cmdList) {
	// 1 P1 0 8 1 兵器号，名称，送到时间，锻造时间，优先级
	aoen.addWeapon(new Weapon(stoi(cmdList[0]), cmdList[1], stoi(cmdList[2]), stoi(cmdList[3]), stoi(cmdList[4])));
}

void handleCommand1(vector<string>& cmdList, char* buffer) {
	char* token = NULL;
	char* next_token = NULL;
	char seps[] = " \n\t";
	token = strtok_s(buffer, seps, &next_token);

	while (token != NULL) {
		if (token != NULL) {
			string temp(token);
			cmdList.push_back(temp);
			token = strtok_s(NULL, seps, &next_token);
		}
	}
}

void handleInput(int lineNum) {
	//vector<string> 
	char buffer[1000];
	for (int i = 0; i < lineNum; i++) {
		for (int i = 0; i < 1000; i++) {
			buffer[i] = 0;
		}
		cin.getline(buffer, 999);
		vector<string> res;
		handleCommand1(res, buffer);
		initTask(res);
	}
}

//int main() {
//
//	int n;
//	cin >> n;
//	getchar();
//	handleInput(n);
//	aoen.startSchedule();
//	aoen.displayLog();
//
//	return 0;
//}