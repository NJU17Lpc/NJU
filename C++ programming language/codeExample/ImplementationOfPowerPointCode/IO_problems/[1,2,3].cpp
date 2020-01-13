#include <iostream>
#include <string>
#include <vector>
#include<sstream>
using namespace std;

void splitWithGetchar(vector<int>& res) {
	//需要手动输入[1,2,3,4,10]
	char c;

	while (c = getchar()) {
		if (c == ',' || c=='[') {
			int temp = 0;
			cin >> temp;
			res.push_back(temp);
		}
		else if (c == ']') {
			break;
		}
	}
	getchar();
	for (auto& i : res) {
		cout << i << " ";
	}
	cout << endl;
}


void splitWithStrtok(vector<int>& res, char string1[]) {
	char seps[] = ",\n[]";
	char* token = NULL;
	char* next_token = NULL;
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
}



//int main() {
//	vector<int> res;
//	char string1[] = "[1,2,3,4]";
//	//splitWithStrtok(res, string1);
//	splitWithGetchar(res);
//	return 0;
//}