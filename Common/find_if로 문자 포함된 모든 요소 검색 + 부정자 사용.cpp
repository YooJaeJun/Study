//IncludeSin

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct IsSin {
	bool operator()(string name) const {
		//��� 2�� �ǹ� : �ѱ��� �����ڵ� ���� 2����Ʈ
		for (int i = 0; i != name.size() / 2; i++) {
			if (name.substr(i * 2, 2) == "��") {
				return true;
			}
		}
		//return (strncmp(name.c_str(), "��", 2) == 0);
		return false;
	}
};
void main()
{
	string names[] = { "������","�̼���","���﹮","�庸��","������",
		 "�ż���","��ȫ��","������","�̼���","������" };
	vector<string> vs(&names[0], &names[10]);
	vector<string>::iterator it;

	names[0].substr(0, 2);
	for (it = vs.begin(); ; it++) {
		it = find_if(it, vs.end(), IsSin());
		if (it == vs.end()) {
			cout << "��" << endl;
			break;
		}
		cout << *it << "��(��) �ִ�." << endl;
	}
}







//notKim
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct IsKim : public unary_function <string, bool> {
	bool operator()(string name) const {
		return (strncmp(name.c_str(), "��", 2) == 0);
	}
};
void main()
{
	string names[] = { "������","�̼���","���﹮","�庸��","������",
		 "�ż���","��ȫ��","������","�̼���","������" };
	vector<string> vs(&names[0], &names[10]);
	vector<string>::iterator it;

	names[0].substr(0, 2);
	for (it = vs.begin(); ; it++) {
		it = find_if(it, vs.end(), not1(IsKim()));
		if (it == vs.end()) {
			cout << "��" << endl;
			break;
		}
		cout << *it << "��(��) �ִ�." << endl;
	}
}