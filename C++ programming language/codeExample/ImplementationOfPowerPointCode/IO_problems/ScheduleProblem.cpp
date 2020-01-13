#include <iostream>
#include <string>
#include <vector>
#include<fstream>
using namespace std;

/*
给出了调度题目的一个大概的模板

输入样例

lpc 1
ztfn 3
erika 2
nanase 5
end



*/

class Component {
public:
	Component(string name, int time):m_name(name), m_addTime(time){
		m_leftTime = time;
	}
	virtual void say() = 0;
	virtual int getLeftTime() {
		return m_leftTime;
	}
	virtual void descLeftTime() {
		m_leftTime--;
	}
protected:
	string m_name;
	int m_addTime;
	int m_leftTime;
};

class ComponentA :public Component {
public:
	ComponentA(string name, int time) :Component(name, time) {}

	virtual void say() override { cout << m_name << " : ComponentA"; }
};

class ComponentB :public Component {
public:
	ComponentB(string name, int time) :Component(name, time) {}

	virtual void say() override { cout << m_name << " : ComponentB"; }

};

class MainBoard {
public:
	MainBoard():m_curTime(0){}
	void startSchedule() {
		while (true) {
			checkState();
			change();
			manageTime();
			if (components.size() == 0) {
				cout << "schedule end";
				break;
			}
		}
	}
	void addComponent(Component* newComp) {
		components.push_back(newComp);
	}
private:
	int m_curTime;
	vector<Component*> components;

	void checkState() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->say();
			cout << "  ";
		}
		cout << endl;
	}

	void change() {
		for (auto it = components.begin(); it != components.end(); ) {
			if ((*it)->getLeftTime() == 0) {
				it = components.erase(it);
			}
			else {
				++it;
			}
		}

	}

	void manageTime() {
		m_curTime++;
		for (int i = 0; i < components.size(); i++) {
			components[i]->descLeftTime();
		}
	}
};

MainBoard board;

bool initTask(vector<string> cmdList) {
	if (cmdList[0] == "end") {
		return false;
	}
	else {

		if (cmdList[0] == "lpc"){
			board.addComponent(new ComponentA(cmdList[0], stoi(cmdList[1])));
		}
		else {
			board.addComponent(new ComponentB(cmdList[0], stoi(cmdList[1])));
		}
	}
	return true;
}

void handleCommand(vector<string>& cmdList, char* buffer) {
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

void handleInput() {
	char buffer[500]{0};
	while (true) {
		vector<string> cmdList;
		cin.getline(buffer, 499);
		handleCommand(cmdList, buffer);
		bool canContinue = initTask(cmdList);
		if (!canContinue) {
			break;
		}
	}
}

//int main() {
//	//string s;
//	//ofstream out("E:\\input.txt", ios::app);
//
//	//for (int i = 0; i < 50; i++) {
//	//	getline(cin, s);
//	//	out << s << endl;
//	//}
//	//out << endl;
//	handleInput();
//	board.startSchedule();
//	return 0;
//}