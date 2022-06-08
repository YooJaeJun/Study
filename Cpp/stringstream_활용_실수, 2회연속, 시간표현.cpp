#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	int i;
	double d;
	string str = "1.4 2.545 2.0 .5 3.7f 4.5";
	// 일반적인 실수 / 소수점이 0 / '.5' 정수부 생략 / f로 float임을 명시
	stringstream stream;
	stream.str(str);

	cout << "int split \n";
	while (stream >> i)
	{
		cout << i << '\n';
	}
	stream.clear();
	// stream.clear() : 첫 위치부터 다시 추출받기 위한 용도. 
	// string 끝까지 도달했는 flag가 올라가서 값이 추출되지 않기 때문 flag bit 초기화.
	cout << '\n';

	cout << "double split \n";
	while (stream >> d)
	{
		cout << d << '\n';
	}
}






// 활용
/*
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// 시간 데이터를 받아 "~시 ~분 ~초" 형태로 표현하자.

int main(void)
{
	string timeStr = "2022.06.08 15:01:20";
	//연 월 일 시 분 초

	for (auto& timeCh : timeStr)
		if (timeCh == ':' || timeCh == '.')
			timeCh = ' ';
			// 추출이 멈추지 않기 위해 공백으로 바꿔준다.

	unsigned int num = 0;
	stringstream stream;
	stream.str(timeStr);
	vector<unsigned int> splitedTime;	// 출력 대신 저장해줄 공간

	while (stream >> num)
	{
		splitedTime.push_back(num);
	}

	vector<string> koreaTime{ "년", "월", "일", "시", "분", "초" };
	int idx = 0;
	for (auto& elem : splitedTime)
	{
		cout << elem << koreaTime[idx++] << ' ';
	}
	cout << '\n';

	return 0;
}


*/