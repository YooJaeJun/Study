//IncludeSin

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct IsSin {
	bool operator()(string name) const {
		//상수 2의 의미 : 한글은 유니코드 문자 2바이트
		for (int i = 0; i != name.size() / 2; i++) {
			if (name.substr(i * 2, 2) == "신") {
				return true;
			}
		}
		//return (strncmp(name.c_str(), "신", 2) == 0);
		return false;
	}
};
void main()
{
	string names[] = { "김유신","이순신","성삼문","장보고","조광조",
		 "신숙주","김홍도","정도전","이성계","정몽주" };
	vector<string> vs(&names[0], &names[10]);
	vector<string>::iterator it;

	names[0].substr(0, 2);
	for (it = vs.begin(); ; it++) {
		it = find_if(it, vs.end(), IsSin());
		if (it == vs.end()) {
			cout << "끝" << endl;
			break;
		}
		cout << *it << "이(가) 있다." << endl;
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
		return (strncmp(name.c_str(), "김", 2) == 0);
	}
};
void main()
{
	string names[] = { "김유신","이순신","성삼문","장보고","조광조",
		 "신숙주","김홍도","정도전","이성계","정몽주" };
	vector<string> vs(&names[0], &names[10]);
	vector<string>::iterator it;

	names[0].substr(0, 2);
	for (it = vs.begin(); ; it++) {
		it = find_if(it, vs.end(), not1(IsKim()));
		if (it == vs.end()) {
			cout << "끝" << endl;
			break;
		}
		cout << *it << "이(가) 있다." << endl;
	}
}