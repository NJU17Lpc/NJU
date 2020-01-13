#include <iostream>
using namespace std;

int main() {

	char testC[] = "[[ldf[ fdac ]";
	char* token = NULL;
	char* next_token = NULL;
	char seps[] = "[] ";
	token = strtok_s(testC, seps, &next_token);


	return 0;
}