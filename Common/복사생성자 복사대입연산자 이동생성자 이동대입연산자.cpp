#include <Turboc.h>
#include <iostream>
using namespace std;

class String {
private:
	char *strData;
	size_t len;
public:
	String() : strData(nullptr), len(0) { }
	String(const char *str) {
		len = strlen(str);
		strData = new char[len + 1];
		myStrcpy(strData, str, len);	//���� ����
	}
	~String() {
		delete[] strData;
		strData = NULL;
	}
	/**/
	String(const String &other) {
		if (this != &other) {
			len = strlen(other.strData);
			strData = new char[other.len + 1];
			myStrcpy(strData, other.strData, len);	//���� ����
		}
	}
	String& operator=(const String &other) {
		if (this != &other) {
			delete[] strData;
			len = strlen(other.strData);
			strData = new char[other.len + 1];
			myStrcpy(strData, other.strData, len);	//���� ����
		}
		return *this;
	}

	String(String &&other) {
		if (this != &other) {
			len = other.len;
			strData = other.strData;	//���� ����
			other.strData = nullptr;
			other.len = 0;
		}
	}
	String& operator=(String &&other) {
		if (this != &other) {
			len = other.len;
			strData = other.strData;	//���� ����
			other.strData = nullptr;
			other.len = 0;
		}
		return *this;
	}

	void Allocated() {

	}
	void Clear() {

	}

	char *GetStrData() const {
		return strData;
	}
	size_t GetLen() const {
		return len;
	}
	void myStrcpy(char * str1, const char * str2, size_t len)
	{
		for (size_t i = 0; i != len; ++i) {
			str1[i] = str2[i];
		}
		str1[len] = 0;
	}
};

int main()
{
	String s1("dd");
	String s2(s1);
	String s3;
	s3 = s1.GetStrData();
	printf("%s, %d", s3.GetStrData(), s3.GetLen());
	//�ӽ� ��ü�� r-value��!!(������ �� ���� ��)
	//String &&r = getName();
}