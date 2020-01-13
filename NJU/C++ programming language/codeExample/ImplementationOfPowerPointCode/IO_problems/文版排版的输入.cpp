#include <iostream>
#include <string>
#include <vector>
using namespace std;

//["This","is","an","example","of","text","justification."]

void handleInput1(vector<string>& res) {

	char buffer[500];
	cin.getline(buffer, 499);

	char* token;
	char* next_token;
	char seps[] = "[]\",\n";
	token = strtok_s(buffer, seps, &next_token);

	while (token != NULL) {
		if (token != NULL) {
			string temp(token);
			res.push_back(temp);
			token = strtok_s(NULL, seps, &next_token);

		}
	}

}

int findHighest(vector<int>& heights, int begin, int end) {
	int high = 0;
	for (int i = begin; i < end; i++) {
		if (heights[i] > high) {
			high = heights[i];
		}
	}
	return high;
}


int cacuRain(vector<int>& heights) {
	int sum = 0;
	for (int i = 1; i < heights.size() - 1; i++) {
		int left = findHighest(heights, 0, i);
		int right = findHighest(heights, i + 1, heights.size());
		int secondHigh = (left > right ? right : left);
		if (heights[i] < secondHigh) {
			sum += (secondHigh - heights[i]);
		}
	}
	return sum;

}

//[time="2019-08",area="shanghai"]
void handleRainInput(vector<string>& res) {
	char buffer[500];
	cin.getline(buffer, 499);


	char* token;
	char* next_token;
	char seps[] = "[]\",\n";
	token = strtok_s(buffer, seps, &next_token);
	token = strtok_s(NULL, seps, &next_token);
	string time(token);
	res.push_back(time);
	token = strtok_s(NULL, seps, &next_token);
	token = strtok_s(NULL, seps, &next_token);

	string area(token);
	res.push_back(area);


}

//int main() {
//	vector<string> res;
//	//handleInput1(res);
//	handleRainInput(res);
//
//	for (int i = 0; i < res.size(); i++) {
//		cout << res[i] << " ";
//	}
//	cout << endl;
//	vector<int> test1 = {2,1,0,3,4,0,6,2,3};
//	vector<int> test2 = { 0,1,0,2,1,0,1,3,2,1,2,1 };
//	vector<int> test3 = { 0, 5, 4, 3, 2, 1, 2, 3, 4, 5, 0, 2, 1, 2, 2, 2 };
//	cout << cacuRain(test1) << endl;
//	cout << cacuRain(test2) << endl;
//	cout << cacuRain(test3) << endl;
//
//	return 0;
//}