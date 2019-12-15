#include <iostream>
#include <string>
#include <vector>
#include<sstream>
using namespace std;

void splitWithStrtok2(vector<int>& res) {
	char string1[200];
	cin.getline(string1, 199);

	char* token;
	char* next_token;
	char seps[] = "(),\n";
	token = strtok_s(string1, seps, &next_token);

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

void splitWithGetchar2(vector<int>& res) {
	int x1, y1;
	char c;
	while (c = getchar()) {
		if (c == '(') {
			cin >> x1;
			res.push_back(x1);
		}
		if (c == ',') {
			cin >> y1;
			res.push_back(y1);
		}
		if (c == ')') {
			break;
		}
	}
	getchar();

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
//	//splitWithStrtok2(res);
//	splitWithGetchar2(res);
//	return 0;
//}