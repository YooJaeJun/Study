#include <iostream>
using namespace std;

int StrStr(const char * s1, const char * s2, int len)
{
	if (len <= 0) { return -1; }

	int result = 0;
	bool bFlag = true;
	//s2 문자열이 s1 문자열에 포함되어 있는지
	for (int i = 0; i < len; i = ++result) {
		//s2 문자열의 첫 문자가 s1 문자열에 있는지 판단
		for (int j = i; j < len; j++) {
			if (s1[j] == s2[0]) {
				bFlag = true;
				result = j;
				break;
			}
		}
		//문자가 하나라도 포함되어 있으면
		if (bFlag) {
			int dLen = strlen(s2);
			//s1 문자열에 그 다음 문자가 s2 문자열의 그 다음 문자와 같은지 판단
			for (int j = 0; j != dLen; j++) {
				if (s1[result + j] == s2[j]) {
					bFlag = true;
				}
				//한 번이라도 안 같으면 break;
				else {
					bFlag = false;
					break;
				}
			}
			//모든 문자열 포함되면 반환
			if (bFlag) {
				return result;
			}
		}
	}
	return -1;
}

void main()
{
	const char * s1 = "abcde";
	const char * s2 = "de";

	printf("%d", StrStr(s1, s2, strlen(s1)));
}