#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

class Car {
protected:
	string type;
	string id;
	double spot_length;
	int park_time;
	int wait_time;
	double park_fee;
	int arrival_time;
	int final_wait_time;
	int leave_time;
public:
	Car(string type, string id, double spot, int parkTime, int waitTime, double parkFee, int arrival_time) :type(type),
		id(id), spot_length(spot), park_time(parkTime), wait_time(waitTime), park_fee(parkFee),
		arrival_time(arrival_time), final_wait_time(arrival_time + waitTime) {}
	virtual string getType() { return type; }
	string getId() { return id; }
	int getArrivalTime() { return arrival_time; }
	int getFinalWaitTime() { return final_wait_time; }
	void setLeaveTime(int curTime) {
		leave_time = curTime + park_time;
	}
	int getLeaveTime() { return leave_time; }
	double getSpotLength() { return spot_length; }
	int getParkTime() { return park_time; }
	int getWaitTime() { return wait_time; }
	double getParkFee() { return park_fee; }
};

class CarS :public Car {
public:
	CarS(string id, int arrivalTime) : Car("S", id, 1, 3, 1, 1.5, arrivalTime) {}
};

class CarM :public Car {
public:
	CarM(string id, int arrivalTime) : Car("M", id, 1.5, 2, 2, 3, arrivalTime) {}
};

class CarL :public Car {
public:
	CarL(string id, int arrivalTime) : Car("L", id, 2, 1, 3, 4.5, arrivalTime) {}
};

class Park {
protected:
	vector<Car*> waiting_cars;
	vector<Car*> parked_cars;
	vector<vector<string>> snapShot;
	int parkSize;
	double price;

public:
	Park(int parkSize) :parkSize(parkSize) {}

	virtual void putCar() {
	}
	virtual void start() {}

	void addWaitingCar(Car* c) {
		waiting_cars.push_back(c);
	}
	bool hasWaitingCar() {
		return waiting_cars.size() > 0;
	}
	bool hasNextMove() {
		return parked_cars.size() != 0 && waiting_cars.size() != 0;
	}
	void printSnapShot() {
		for (int i = 0; i < snapShot.size(); i++) {
			for (int j = 0; j < snapShot[i].size(); j++) {
				cout << snapShot[i][j] << " ";
			}
			cout << endl;
		}
		cout << price;
	}
};

class SunnyPark :public Park {
private:
	int curTime;
	double spaceLeft;
	void sunnyMove() {}
	bool hasEnoughSpace(Car* car) {
		return spaceLeft >= car->getSpotLength();
	}
	void parkCar(Car* car) {
		parked_cars.push_back(car);
		spaceLeft = spaceLeft - car->getSpotLength();
		price = car->getParkFee() + price;
	}
	void unparkCar(Car* car) {
		spaceLeft = spaceLeft + car->getSpotLength();
	}
	bool carArrived(Car* c) {
		return c->getArrivalTime() <= curTime;
	}
	void putCar() {
		for (int i = 0; i < waiting_cars.size(); i++) {
			if (hasWaitingCar()) {
				Car* frontCar = waiting_cars.front();
				if (hasEnoughSpace(frontCar) && carArrived(frontCar)) {
					waiting_cars.erase(waiting_cars.begin());
					parkCar(frontCar);
					frontCar->setLeaveTime(curTime);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		vector<string> curParkedCars;
		if (parked_cars.size() == 0) {
			curParkedCars.push_back("null");
		}
		else {
			for (auto& car : parked_cars) {
				curParkedCars.push_back(car->getId());
			}
		}

		snapShot.push_back(curParkedCars);
	}

	void checkLeave() {

		for (auto it = parked_cars.begin(); it != parked_cars.end();) {
			if ((*it)->getLeaveTime() == curTime) {
				this->spaceLeft = this->spaceLeft + (*it)->getSpotLength();

				it = parked_cars.erase(it);
			//	if (it == parked_cars.end())break;
			}
			else {
				++it;
			}
		}
		for (auto it = waiting_cars.begin(); it != waiting_cars.end();) {
			if ((*it)->getFinalWaitTime() <= curTime) {
				it = waiting_cars.erase(it);
				//if (it == waiting_cars.end())break;
			}
			else {
				++it;
			}
		}
	}
public:
	SunnyPark(int parkSize) :Park(parkSize), spaceLeft(parkSize), curTime(1) {}

	void start() {
		while (waiting_cars.size() != 0 || parked_cars.size() != 0) {
			putCar();
			curTime++;
			checkLeave();
		}
		vector<string> finalShot;
		finalShot.push_back("null");
		snapShot.push_back(finalShot);
		printSnapShot();
	}

};

class RainyPark :public Park {
private:
	int curTime;

	bool putIntoEnoughSpace(Car* newCar) {
		int needSize = newCar->getSpotLength() * 2;
		int spaceLen = 0;
		int spaceIndex = -1;
		bool found = false;
		for (int i = 0; i < parked_cars.size()-1; i++) {
			if (parked_cars[i] != NULL) {
				continue;
			}
			for (int j = i+1; j < parked_cars.size(); j++) {
				if (parked_cars[j] == NULL) {
					spaceLen = j - i + 1;
				}
				else {
					break;
				}
			}
			if (spaceLen >= needSize) {
				found = true;
				spaceIndex = i;
				price = price + newCar->getParkFee();
				break;
			}
		}
		if (found) {
			for (int i = spaceIndex; i < spaceIndex + needSize; i++) {
				parked_cars[i] = newCar;
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool carArrived(Car* c) {
		return c->getArrivalTime() <= curTime;
	}
	bool hasParkedCar() {
		bool hasCar = false;
		for (int i = 0; i < parked_cars.size(); i++) {
			if (parked_cars[i] != NULL) {
				hasCar = true;
				break;
			}
		}
		return hasCar;
	}
	void checkLeave() {

		for (auto it = parked_cars.begin(); it != parked_cars.end(); ++it) {
			if ((*it) == NULL) {
				continue;
			}
			if ((*it)->getLeaveTime() == curTime) {
				(*it) = NULL;
			}
			
		}
		for (auto it = waiting_cars.begin(); it != waiting_cars.end();) {
			if ((*it)->getFinalWaitTime() <= curTime) {
				it = waiting_cars.erase(it);
				//if (it == waiting_cars.end())break;
			}
			else {
				++it;
			}
		}
	}
public:
	RainyPark(int parkSize) :Park(parkSize), curTime(1) {
		for (int i = 0; i < parkSize * 2; i++) {
			parked_cars.push_back(NULL);
		}
	}
	void putCar() {
		int waitingSize = waiting_cars.size();
		for (int i = 0; i < waitingSize; i++) {
			if (hasWaitingCar()) {
				Car* frontCar = waiting_cars.front();
				if (carArrived(frontCar)&&putIntoEnoughSpace(frontCar)) {
					waiting_cars.erase(waiting_cars.begin());
					frontCar->setLeaveTime(curTime);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		vector<string> curParkedCars;
		bool hasCar = false;
		for (int i = 0; i < parked_cars.size(); ) {
			if (parked_cars[i] != NULL) {
				hasCar = true;
				curParkedCars.push_back(parked_cars[i]->getId());
				i = i + parked_cars[i]->getSpotLength() * 2;
			}
			else {
				i++;
			}
		}

		if (!hasCar) {
			curParkedCars.push_back("null");
		}
		

		snapShot.push_back(curParkedCars);
	
	}
	void start() {
		while (waiting_cars.size() != 0 || hasParkedCar()) {
			putCar();
			curTime++;
			checkLeave();
		}
		vector<string> finalShot;
		finalShot.push_back("null");
		snapShot.push_back(finalShot);
		printSnapShot();
	}
};

void splitSpace(vector<string>& commands, string s) {
	stringstream ss(s);
	string token;
	while (getline(ss, token, ' ')) {
		commands.push_back(token);
	}
}

int main() {

	//string s;
	//ofstream outfile("E:\\input2.txt", ios::app);
	//for(int i=0; i<150; i++){
	//	getline(cin, s);
	//	outfile << s << endl;
	//}
	//outfile << endl << endl;
	//return 0;

	string command;
	getline(cin, command);
	vector<string> parkInfo;
	splitSpace(parkInfo, command);
	int size = stoi(parkInfo[0]);
	Park* park;
	if (parkInfo[1] == "sunny") {
		park = new SunnyPark(size);
	}
	else if (parkInfo[1] == "rainy") {
		park = new RainyPark(size);
	}
	else {
		cout << parkInfo[1] << " is not a valid parkInfo" << endl;
		return 0;
	}
	int curTime = 1;
	while (true) {
		vector<string> commands;
		getline(cin, command);
		splitSpace(commands, command);
		if (commands[0] == "in") {
			Car* car;
			if (commands[1] == "S") {
				car = new CarS(commands[2], curTime);
			}
			else if (commands[1] == "M") {
				car = new CarM(commands[2], curTime);
			}
			else if (commands[1] == "L") {
				car = new CarL(commands[2], curTime);
			}
			else {
				cout << "not a valid command" << endl;
				return 0;
			}
			park->addWaitingCar(car);
			curTime++;
		}
		else if (commands[0] == "end") {
			park->start();
			break;
		}
		else {
			cout << command << " is not a valid command" << endl;
			break;
		}
	}

	return 0;
}