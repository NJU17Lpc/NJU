#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
strtok_s 
1����һ�������Ǵ����Ҫ�ָ���ַ���
2���ڶ��������Ǵ�ŷָ���
3�������������Ǵ�ű��ָ�����ַ���
*/
void doSplit() {
	char string1[] = "A string\tof ,,tokens\nand some   more tokens";
	char string2[] = "Another string\n\tparsed at  the same   time.";
	char seps[] = " ,\t\n";
	char* token1 = NULL;
	char* token2 = NULL;
	char* next_token1 = NULL;
	char* next_token2 = NULL;

	vector<string> v_token1;
	vector<string> v_token2;

	token1 = strtok_s(string1, seps, &next_token1);
	token2 = strtok_s(string2, seps, &next_token2);

	while ((token1 != NULL) || (token2 != NULL)) {
		if (token1 != NULL) {
			v_token1.push_back(token1);
			token1 = strtok_s(NULL, seps, &next_token1);
		}

		if (token2 != NULL) {
			v_token2.push_back(token2);
			token2 = strtok_s(NULL, seps, &next_token2);
		}
	}

}

//int main() {
//	doSplit();
//	return 0;
//}