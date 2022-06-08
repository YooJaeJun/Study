#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	int i;
	double d;
	string str = "1.4 2.545 2.0 .5 3.7f 4.5";
	// �Ϲ����� �Ǽ� / �Ҽ����� 0 / '.5' ������ ���� / f�� float���� ���
	stringstream stream;
	stream.str(str);

	cout << "int split \n";
	while (stream >> i)
	{
		cout << i << '\n';
	}
	stream.clear();
	// stream.clear() : ù ��ġ���� �ٽ� ����ޱ� ���� �뵵. 
	// string ������ �����ߴ� flag�� �ö󰡼� ���� ������� �ʱ� ���� flag bit �ʱ�ȭ.
	cout << '\n';

	cout << "double split \n";
	while (stream >> d)
	{
		cout << d << '\n';
	}
}






// Ȱ��
/*
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// �ð� �����͸� �޾� "~�� ~�� ~��" ���·� ǥ������.

int main(void)
{
	string timeStr = "2022.06.08 15:01:20";
	//�� �� �� �� �� ��

	for (auto& timeCh : timeStr)
		if (timeCh == ':' || timeCh == '.')
			timeCh = ' ';
			// ������ ������ �ʱ� ���� �������� �ٲ��ش�.

	unsigned int num = 0;
	stringstream stream;
	stream.str(timeStr);
	vector<unsigned int> splitedTime;	// ��� ��� �������� ����

	while (stream >> num)
	{
		splitedTime.push_back(num);
	}

	vector<string> koreaTime{ "��", "��", "��", "��", "��", "��" };
	int idx = 0;
	for (auto& elem : splitedTime)
	{
		cout << elem << koreaTime[idx++] << ' ';
	}
	cout << '\n';

	return 0;
}


*/