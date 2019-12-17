#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void splitByStrtok(vector<string>& res, char* buffer) {
	char* token = NULL;
	char* next_token = NULL;
	char seps[] = " \n";

	token = strtok_s(buffer, seps, &next_token);
	
	while (token != NULL) {
		if (token != NULL) {
			string temp(token);
			res.push_back(temp);
			token = strtok_s(NULL, seps, &next_token);
		}
	}
}

void handleCommandStrtok() {
	char buffer[10000];
	
	while (true) {
		for (int i = 0; i < 10000; i++) {
			buffer[i] = '\0';
		}
		cin.getline(buffer, 9999);
		vector<string> res;
		splitByStrtok(res, buffer);
		//具体处理代码
	}
}

void makeCommand(vector<string>& commands) {
	cout << "make Command" << endl;

}

void splitByStringstream(vector<string>& res, string s) {
	stringstream ss(s);
	string token;
	while (ss >> token) {
		res.push_back(token);
	}
}

void handleCommandStringstream() {
	string s;

	while (true) {
		getline(cin, s);
		vector<string> res;
		splitByStringstream(res, s);
		//具体处理代码
		makeCommand(res);
	}

}

//int main() {
//	//string s;
//	//ofstream outfile("E:\\input.txt", ios::app);
//	//for (int i = 0; i < 50; i++) {
//	//	getline(cin, s);
//	//	outfile << s << endl;
//	//}
//
//	//handleCommandStrtok();
//	handleCommandStringstream();
//
//	return 0;
//}

//void deletev(vector<int>& v) {
//	for (auto it = v.begin(); it != v.end(); ) {
//		if ((*it) == 1) {
//			it = v.erase(it);
//		}
//		else {
//			++it;
//		}
//	}
//
//}