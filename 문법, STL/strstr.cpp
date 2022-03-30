#include <iostream>
using namespace std;

int StrStr(const char * s1, const char * s2, int len)
{
	if (len <= 0) { return -1; }

	int result = 0;
	bool bFlag = true;
	//s2 ���ڿ��� s1 ���ڿ��� ���ԵǾ� �ִ���
	for (int i = 0; i < len; i = ++result) {
		//s2 ���ڿ��� ù ���ڰ� s1 ���ڿ��� �ִ��� �Ǵ�
		for (int j = i; j < len; j++) {
			if (s1[j] == s2[0]) {
				bFlag = true;
				result = j;
				break;
			}
		}
		//���ڰ� �ϳ��� ���ԵǾ� ������
		if (bFlag) {
			int dLen = strlen(s2);
			//s1 ���ڿ��� �� ���� ���ڰ� s2 ���ڿ��� �� ���� ���ڿ� ������ �Ǵ�
			for (int j = 0; j != dLen; j++) {
				if (s1[result + j] == s2[j]) {
					bFlag = true;
				}
				//�� ���̶� �� ������ break;
				else {
					bFlag = false;
					break;
				}
			}
			//��� ���ڿ� ���ԵǸ� ��ȯ
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