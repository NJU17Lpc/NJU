#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<list>
const int BATTLE_PLANE = 1;
const int TRANSPORT_PLANE = 2;
const int HELICOPTER = 3;
using namespace std;
class Plane;
bool planeCompare(Plane* plane1, Plane* plane2);

class Plane {
protected:
	int id;
	string name;
	int up_time;
	int task_time;
	int down_time;
	
	int join_time;
	int back_time;
	int leftTaskTime;
	int leftUpTime;
	int leftDownTime;
	bool setOut;
	int outTime;
	int upPriority;
	int downPriority;
	int finalLandTime;
	int landFirstTime;
public:
	Plane(int up, int task, int down, string rawId, string name, int upPrio, int downPrio) :
		up_time(up), task_time(task), down_time(down), id(stoi(rawId.substr(1))), name(name), setOut(false),
		leftTaskTime(task), leftUpTime(up), leftDownTime(down), upPriority(upPrio), downPriority(downPrio),landFirstTime(-1) {}

	void setTimes(int up, int task, int down) {
		this->up_time = up;
		this->task_time = task;
		this->down_time = down;
		leftUpTime = up;
		leftDownTime = down;
		leftTaskTime = task;
	}
	void setJoinAndBackTime(int joinTime) {
		join_time = joinTime;
		back_time = joinTime + task_time;
	}
	int getLandFirstTime() {
		return landFirstTime;
	}
	void setLandFirstTime(int time) {
		landFirstTime = time;
	}
	int getUpTime() { return up_time; }
	int getTaskTime() { return task_time; }
	int getDownTime() { return down_time; }
	int getLeftTaskTime() { return leftTaskTime; }
	int getLeftDownTime() { return leftDownTime; }
	int getLeftUpTime() { return leftUpTime; }
	bool hasSetOut() { return setOut; }
	int getId() { return id; }
	string getName() { return name; }
	int getJoinTime() { return join_time; }
	int getOutTime() { return outTime; }
	void decreaseLeftUpTime() { leftUpTime--; }
	void decreaseLeftTaskTime() { leftTaskTime--; }
	void decreaseLeftDownTime() { leftDownTime--; }
	void successSetout() { setOut = true; }
	void setOutTime(int time) { outTime = time; }
	int getUpPriority() { return upPriority; }
	int getDownPriority() { return downPriority; }
	int getFinalLandTime() { return finalLandTime; }
	void setFinalLandTime(int time) {
		finalLandTime = time;
	}
	bool operator < (Plane* plane2) {
		Plane* plane1 = this;
		int arriveTime1 = 0, arriveTime2 = 0;
		if (plane1->hasSetOut()) {
			arriveTime1 = plane1->getOutTime() + plane1->getTaskTime();
		}
		else {
			arriveTime1 = plane1->getJoinTime();
		}

		if (plane2->hasSetOut()) {
			arriveTime2 = plane2->getOutTime() + plane2->getTaskTime();
		}
		else {
			arriveTime2 = plane2->getJoinTime();
		}

		if (arriveTime1 < arriveTime2) {
			return true;
		}
		else if (arriveTime1 == arriveTime2) {
			if (plane1->hasSetOut() && (!plane2->hasSetOut())) {
				//1返航，2出发
				return false;
			}
			else if (plane2->hasSetOut() && (!plane1->hasSetOut())) {
				//2返航，1出发
				return true;
			}
			else if (plane1->hasSetOut() && plane2->hasSetOut()) {
				//12都出发
				if (plane1->getDownPriority() < plane2->getDownPriority()) {
					//1优先级高
					return true;
				}
				else if (plane1->getDownPriority() > plane2->getDownPriority()) {
					return false;
				}
				else {
					return plane1->getId() < plane2->getId();
				}
			}
			else if ((!plane1->hasSetOut()) && (!plane2->hasSetOut())) {
				//12都没出发
				if (plane1->getUpPriority() < plane2->getUpPriority()) {
					//1优先级高
					return true;
				}
				else if (plane1->getUpPriority() > plane2->getUpPriority()) {
					return false;
				}
				else {
					return plane1->getId() < plane2->getId();
				}
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}
};

bool normalCmp(Plane* p1, Plane* p2) {
	return p1->getId() < p2->getId();
}

class BattlePlane :public Plane {
public:
	BattlePlane(string rawId) :Plane(2, 0, 2, rawId, "battleplane", 2, 2) {}
};

class TransportPlane :public Plane {
public:
	TransportPlane(string rawId) :Plane(3, 0, 3, rawId, "transportplane", 3, 1) {}
};

class Helicopter :public Plane {
public:
	Helicopter(string rawId) :Plane(1, 0, 1, rawId, "helicopter", 1, 3) {}
};

class Carrier {
private:
	int curTime;
	Plane* curPlane;
	vector<Plane*> planes;
	vector<Plane*> competePlanes; //到达甲板的飞机
	list<Plane*> planesOnAir; //在天上飞的飞机
	vector<Plane*> arrivedPlanes;
	Plane* findPlane(int id) {
		int index = -1;
		for (int i = 0; i < planes.size(); i++) {
			if (planes[i]->getId() == id) {
				index = i;
			}
		}
		if (index < 0) {
			cout << "can't find plane of id:" << id << endl;
			return NULL;
		}
		else {
			return planes[index];
		}
	}
public:
	void addPlane(int type, string rawId) {
		Plane* p;
		switch (type) {
		case BATTLE_PLANE:
			p = new BattlePlane(rawId);
			break;
		case TRANSPORT_PLANE:
			p = new TransportPlane(rawId);
			break;
		case HELICOPTER:
			p = new Helicopter(rawId);
			break;
		default:
			cout << "not a valid plane type" << endl;
			break;
		}
		planes.push_back(p);
	}
	void setPlaneAttr(string rawId, string up, string task, string down) {
		Plane* p = findPlane(stoi(rawId.substr(1)));
		p->setTimes(stoi(up), stoi(task), stoi(down));
	}
	void normalPrint() {
		sort(planes.begin(), planes.end(), normalCmp);
		for (int i = 0; i < planes.size(); i++) {
			cout << "p" << planes[i]->getId() << " ";
			cout << planes[i]->getName() << " ";
			cout << planes[i]->getUpTime() << " ";
			cout << planes[i]->getTaskTime() << " ";
			cout << planes[i]->getDownTime() << endl;
		}
	}

	void joinPlane(string rawId, string time) {
		Plane* p = findPlane(stoi(rawId.substr(1)));
		p->setJoinAndBackTime(stoi(time));
	}

	void setLandFirstPlane(string rawId, string time) {
		Plane* p = findPlane(stoi(rawId.substr(1)));
		p->setLandFirstTime(stoi(time));
	}

	void timeManage() {
		//系统时间调整
		curTime++;
		//当前甲板上飞机时间调整
		if (curPlane != NULL) {
			if (curPlane->hasSetOut()) {
				//当前飞机是在返航
				curPlane->decreaseLeftDownTime();
			}
			else {
				//当前飞机是在出发
				curPlane->decreaseLeftUpTime();
			}
		}
		//已飞出的飞机时间调整任务剩余的时间
		for (auto it = planesOnAir.begin(); it != planesOnAir.end(); it++) {
			if ((*it)->getTaskTime() > 0) {
				(*it)->decreaseLeftTaskTime();
			}
		}
	}

	void checkCompetePlanes() {
		//到时间，将该时间已经到甲板的飞机都作为竞争的飞机
		for (int i = 0; i < planes.size(); i++) {
			if (planes[i]->getJoinTime() == curTime) {
				competePlanes.push_back(planes[i]);
			}
		}
		//到时间，将飞行中的已经完成任务的飞机放入竞争的飞机中
		for (auto it = planesOnAir.begin(); it != planesOnAir.end(); ) {
			if ((*it)->getLeftTaskTime() == 0) {
				competePlanes.push_back((*it));
				it = planesOnAir.erase(it);
			}
			else {
				++it;
			}
		}
		

	}

	void fuck() {
		//对甲板上有无飞机的控制
		if (curPlane != NULL) {
			//如果正在甲板上返航，并还没有返回完，锁住
			if (curPlane->hasSetOut() && curPlane->getLeftDownTime() != 0) {
				return;
			}//如果正在甲板上出行，并没有走完，锁住
			else if ((!curPlane->hasSetOut()) && curPlane->getLeftUpTime() != 0) {
				return;
			}//其他情况，甲板上都没有飞机
			else {
				if (curPlane->hasSetOut() && curPlane->getLeftDownTime() == 0) {
					curPlane->setFinalLandTime(curTime);
					arrivedPlanes.push_back(curPlane);
				}
				else if ((!curPlane->hasSetOut()) && curPlane->getLeftUpTime() == 0) {
					//curPlane->setOutTime(curTime);
					planesOnAir.push_back(curPlane);
					curPlane->successSetout();
				}
				curPlane = NULL;
			}
		}


		//处理landfirst，即使在工作也要召回
		for (auto it = planesOnAir.begin(); it != planesOnAir.end(); ) {
			if ((*it)->getLandFirstTime() == curTime) {
				competePlanes.push_back((*it));
				it = planesOnAir.erase(it);
				break;
			}
			else {
				++it;
			}
		}

		//对优先级调度的控制
		sort(competePlanes.begin(), competePlanes.end(), planeCompare);

		if (competePlanes.size() != 0) {


			Plane* temp = NULL;
			bool hasLandFirst = false;
			for (auto it = competePlanes.begin(); it != competePlanes.end(); ) {
				if ((*it)->getLandFirstTime() > 0 && (*it)->hasSetOut()) {
					temp = (*it);
					hasLandFirst = true;
					it = competePlanes.erase(it);
					break;
				}
				else {
					++it;
				}
			}
			
			if (hasLandFirst) {
				curPlane = temp;
				curPlane->setFinalLandTime(curTime + curPlane->getDownTime());

			}
			else {
				curPlane = competePlanes.front();
				if (curPlane->hasSetOut()) {
					curPlane->setFinalLandTime(curTime + curPlane->getDownTime());
					//arrivedPlanes.push_back(curPlane);
				}
				else {
					curPlane->setOutTime(curTime);
				}
				competePlanes.erase(competePlanes.begin());
			}
		}
	}



	void startSchedule() {
		while (true) {
			checkCompetePlanes();
			fuck();
			timeManage();
			if (arrivedPlanes.size() == planes.size()) {
				break;
			}
		}
	}

	void schedulePrint() {
		for (auto it = arrivedPlanes.begin(); it != arrivedPlanes.end(); it++) {
			cout << "p" << (*it)->getId() << " " << (*it)->getOutTime() << " " << (*it)->getFinalLandTime() << endl;
		}
	}
};


bool planeCompare(Plane* plane1, Plane* plane2) {
	//if (plane1->getLandFirstTime() > 0 && plane2->getLandFirstTime()<0) {
	//	//既然他只制定一个landfirst，我就直接这样写了
	//	return true;
	//}
	if (plane1->hasSetOut() && (!plane2->hasSetOut())) {
		return false;
	}else if (plane2->hasSetOut() && (!plane1->hasSetOut())) {
		return true;
	}



	int arriveTime1 = 0, arriveTime2 = 0;
	if (plane1->hasSetOut()) {
		arriveTime1 = plane1->getOutTime() + plane1->getUpTime() + plane1->getTaskTime() - 1;
	}
	else {
		arriveTime1 = plane1->getJoinTime();
	}

	if (plane2->hasSetOut()) {
		arriveTime2 = plane2->getOutTime() + plane2->getUpTime() + plane2->getTaskTime() - 1;
	}
	else {
		arriveTime2 = plane2->getJoinTime();
	}

	if (arriveTime1 < arriveTime2) {
		return true;
	}
	else if (arriveTime1 == arriveTime2) {
		if (plane1->hasSetOut() && (!plane2->hasSetOut())) {
			//1返航，2出发
			return false;
		}
		else if (plane2->hasSetOut() && (!plane1->hasSetOut())) {
			//2返航，1出发
			return true;
		}
		else if (plane1->hasSetOut() && plane2->hasSetOut()) {
			//12都出发
			if (plane1->getDownPriority() < plane2->getDownPriority()) {
				//1优先级高
				return true;
			}
			else if (plane1->getDownPriority() > plane2->getDownPriority()) {
				return false;
			}
			else {
				return plane1->getId() < plane2->getId();
			}
		}
		else if ((!plane1->hasSetOut()) && (!plane2->hasSetOut())) {
			//12都没出发
			if (plane1->getUpPriority() < plane2->getUpPriority()) {
				//1优先级高
				return true;
			}
			else if (plane1->getUpPriority() > plane2->getUpPriority()) {
				return false;
			}
			else {
				return plane1->getId() < plane2->getId();
			}
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

void splitSpace(vector<string>& tokens, string s) {
	stringstream ss(s);
	string token;
	while (getline(ss, token, ' ')) {
		tokens.push_back(token);
	}
}

int main() {
	int n;
	string command;
	getline(cin, command);
	n = stoi(command);
	Carrier carrier;

	for (int i = 0; i < n - 1; i++) {
		getline(cin, command);
		vector<string> commands;
		splitSpace(commands, command);
		if (commands[0] == "add") {
			if (commands[1] == "battleplane") {
				carrier.addPlane(BATTLE_PLANE, commands[2]);
			}
			else if (commands[1] == "transportplane") {
				carrier.addPlane(TRANSPORT_PLANE, commands[2]);
			}
			else if (commands[1] == "helicopter") {
				carrier.addPlane(HELICOPTER, commands[2]);
			}
			else {
				cout << commands[1] << " is not a valid plane name" << endl;
			}
		}
		else if (commands[0] == "set") {
			carrier.setPlaneAttr(commands[1], commands[2], commands[3], commands[4]);
		}
		else if (commands[0] == "join") {
			carrier.joinPlane(commands[1], commands[2]);
		}
		else if (commands[0] == "landfirst") {
			carrier.setLandFirstPlane(commands[2], commands[1]);

		}
		else {
			cout << command << " is not a valid command" << endl;
		}
	}

	getline(cin, command);
	if (command == "normal") {
		carrier.normalPrint();
	}
	else if (command == "schedule") {
		carrier.startSchedule();
		carrier.schedulePrint();
	}
	else {
		cout << command << " is not a valid command" << endl;
	}
	return 0;
}