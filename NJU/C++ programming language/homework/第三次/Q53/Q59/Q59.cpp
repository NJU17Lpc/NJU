#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<fstream>
using namespace std;

class Rectangle {
protected:
	string id;
	int R;
	int G;
	int B;
	double Gray;
	void setGray() {
		Gray = R * 0.299 + G * 0.587 + B * 0.114;
	}
public:
	Rectangle(string id):id(id){
		R = 0;
		G = 0;
		B = 0;
	}
	virtual void setRGB(int R, int G, int B) = 0;
	string getId() { return id; }
	double getGray() { return Gray; }
	int getR() { return R; }
	int getG() { return G; }
	int getB() { return B; }
};

class NormalRec :public Rectangle {
public:
	NormalRec(string id):Rectangle(id){}
	void setRGB(int R, int G, int B){
		this->R = R;
		this->G = G;
		this->B = B;
		setGray();
	}
};

class ReverseRec :public Rectangle {
public:
	ReverseRec(string id):Rectangle(id){}
	void setRGB(int R, int G, int B) {
		this->R = 255 - R;
		this->G = 255 - G;
		this->B = 255 - B;
		setGray();
	}
};

class SingleRedRec :public Rectangle {
public:
	SingleRedRec(string id):Rectangle(id){}
	void setRGB(int R, int G, int B) {
		this->R = R;
		this->G = 0;
		this->B = 0;
		setGray();
	}
};



class Group {
private:
	vector<Rectangle*> groupRecs;
	string groupId;
public:
	void groupAddRectangle(Rectangle* newRec) {
		groupRecs.push_back(newRec);
	}
	Group(string id):groupId(id){}
	string getGroupId() { return groupId; }
	void setGroupRGB(int R, int G, int B) {
		for (int i = 0; i < groupRecs.size(); i++) {
			groupRecs[i]->setRGB(R, G, B);
		}
	}
};

bool recIdCmp(Rectangle* rec1, Rectangle* rec2) {
	int id1 = stoi((rec1->getId()).substr(1));
	int id2 = stoi((rec2->getId()).substr(1));

	return id1<id2;
}

bool grayCmp(Rectangle* rec1, Rectangle* rec2) {
	if (rec1->getGray() < rec2->getGray()) {
		return true;
	}
	else if (rec1->getGray() == rec2->getGray()) {
		return recIdCmp(rec1, rec2);
	}
	else {
		return false;
	}
}

class Plane {
private:
	vector<Rectangle*> rectangles;
	vector<Group> groups;

public:
	void addRectangle(Rectangle* newRec) {
		rectangles.push_back(newRec);
	}
	void addGroup(Group& group) {
		groups.push_back(group);
	}
	void addRecToGroup(string& recId, Group& group) {
		int recIndex = 0;
		for (int i = 0; i < rectangles.size(); i++) {
			if (rectangles[i]->getId() == recId) {
				recIndex = i;
			}
		}
		group.groupAddRectangle(rectangles[recIndex]);
	}
	Group& findGroup(string& groupId) {
		int groupIndex = 0;
		for (int i = 0; i < groups.size(); i++) {
			if (groups[i].getGroupId() == groupId) {
				groupIndex = i;
			}
		}
		return groups[groupIndex];
	}
	Rectangle* findRectangle(string& recId) {
		int recIndex = 0;
		for (int i = 0; i < rectangles.size(); i++) {
			if (rectangles[i]->getId() == recId) {
				recIndex = i;
			}
		}
		return rectangles[recIndex];
	}
	void NormalOutput() {
		sort(rectangles.begin(), rectangles.end(), recIdCmp);
		for (int i = 0; i < rectangles.size(); i++) {
			cout << rectangles[i]->getId() << " " << rectangles[i]->getR() << " " << rectangles[i]->getG() << " " << rectangles[i]->getB() << endl;
		}
	}
	void GrayOutput() {
		sort(rectangles.begin(), rectangles.end(), grayCmp);
		for (int i = 0; i < rectangles.size(); i++) {
			cout << rectangles[i]->getId() << " " << rectangles[i]->getR() << " " << rectangles[i]->getG() << " " << rectangles[i]->getB() << endl;
		}
	}
};

vector<string>& splitSpace(vector<string>& tokens, string s) {
	string token;
	stringstream ss(s);
	while (getline(ss, token, ' ')) {
		tokens.push_back(token);
	}
	return tokens;
}

int main() {
	int n = 0;
	string command;

	//ofstream outfile("E:\\input1.txt", ios::app);
	//for (int i = 0; i < 30; i++) {
	//	getline(cin, command);
	//	outfile << command << endl;
	//}
	//outfile << endl << endl;



	getline(cin, command);
	n = stoi(command);
	Plane plane;
	for (int i = 0; i < n; i++) {
		getline(cin, command);
		vector<string> commands;
		splitSpace(commands, command);
		if (commands[0] == "Add") {
			Rectangle* rec;
			if (commands[1] == "single") {
				rec = new SingleRedRec(commands[2]);
			}
			else if (commands[1] == "normal") {
				rec = new NormalRec(commands[2]);
			}
			else if (commands[1] == "reverse") {
				rec = new ReverseRec(commands[2]);
			}
			else {
				cout << command << " is not a valid command" << endl;
				return 0;
			}
			plane.addRectangle(rec);
		}
		else if (commands[0] == "Set") {
			string sign = commands[1].substr(0, 1);
			if (sign == "P") {
				int R = stoi(commands[2]);
				int G = stoi(commands[3]);
				int B = stoi(commands[4]);
				plane.findRectangle(commands[1])->setRGB(R, G, B);
			}
			else if (sign == "G") {
				int R = stoi(commands[2]);
				int G = stoi(commands[3]);
				int B = stoi(commands[4]);
				plane.findGroup(commands[1]).setGroupRGB(R, G, B);
			}
			else {
				cout << command << " is not a valid command" << endl;
				return 0;
			}
		}
		else if (commands[0] == "Group") {
			int recSize = stoi(commands[1]);
			string groupId = commands[commands.size() - 1];
			Group newGroup(groupId);
			for (int i = 2; i < commands.size() - 1; i++) {
				plane.addRecToGroup(commands[i], newGroup);
			}
			plane.addGroup(newGroup);
		}
	}
	getline(cin, command);
	if (command == "Normal") {
		plane.NormalOutput();
	}
	else if (command == "Gray") {
		plane.GrayOutput();
	}
	else {
		cout << command << " is not a valid command" << endl;
		return 0;
	}

	return 0;
}