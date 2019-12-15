#include <iostream>
#include <vector>
using namespace std;

void deleteByNum(vector<int>& v, int num) {
	for (auto it = v.begin(); it != v.end(); ) {
		if ((*it) == num) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}
}

void printV(vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> v = { 2,3,4,53,2,13,5,32,21,1,2 };
	printV(v);
	deleteByNum(v, 2);
	printV(v);

}