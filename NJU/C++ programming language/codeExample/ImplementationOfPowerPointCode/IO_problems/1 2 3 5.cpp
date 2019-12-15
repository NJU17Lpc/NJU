#include <iostream>
#include <string>
#include <vector>
#include<sstream>
using namespace std;

void splitWithGetchar1(vector<int>& res) {
	int temp = 0;
	while (cin >> temp) {
		res.push_back(temp);
		char c = getchar();
		if (c == '\n') {
			break;
		}
	}
	for (auto& i : res) {
		cout << i << " ";
	}
	cout << endl;
	int testNextLine;
	cin >> testNextLine;
	cout << testNextLine;
}

void splitWithStrtok1(vector<int>& res) {
	char input[200];
	cin.getline(input, 199);
	char* token;
	char* next_token;
	char seps[] = " \n";

	token = strtok_s(input, seps, &next_token);
	while (token != NULL) {
		if (token != NULL) {
			res.push_back(atoi(token));
			token = strtok_s(NULL, seps, &next_token);
		}
	}
	for (auto& i : res) {
		cout << i << " ";
	}
	cout << endl;
	int testNextLine;
	cin >> testNextLine;
	cout << testNextLine;
}

//int main() {
//	vector<int> res;
//	splitWithStrtok1(res);
//	//splitWithGetchar1(res);
//	return 0;
//}