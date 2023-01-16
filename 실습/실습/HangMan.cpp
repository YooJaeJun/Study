#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using std::string;

const int num = 4;
const string wordlist[num] = { "as", "df", "qwer", "zxcvb" };

int main()
{
	using namespace std;

	srand(time(0));

	char play;
	cout << "��� ����? <y/n> ";
	cin >> play;
	play = tolower(play);
	while (play == 'y')
	{
		string target = wordlist[rand() % num];
		int length = target.length();
		string attempt(length, '-');
		int guesses = 6;
		cout << "--------------------------\n" 
			<< "�ܾ� �����غ�!\n"
			<< length << "���� ���ڷ� �̷���� �־�.\n"
			<< "�� ���� �� ���ھ� �����غ�.\n"
			<< "Ʋ�� �� �ִ� ��ȸ: " << guesses << "��\n";
		cout << "�����ϴ� �ܾ�: " << attempt << '\n'
			<< "--------------------------\n";

		string badchars;
		while (guesses > 0 && attempt != target)
		{
			char letter;
			cout << "���� �����غ�: ";
			cin >> letter;

			if (badchars.find(letter) != string::npos ||
				attempt.find(letter) != string::npos)
			{
				cout << "�̹� ������ ���ھ�!! �ٽ� ��!!! \n";
				continue;
			}
			int loc = target.find(letter);
			if (loc == string::npos)
			{
				cout << "��! Ʋ������ \n";
				--guesses;
				badchars += letter;
			}
			else
			{
				cout << "������! �¾Ҿ� \n";
				attempt[loc] = letter;
				// ���� ���ڰ� �� �ִ��� �˻�
				loc = target.find(letter, loc + 1);
				while (loc != string::npos)
				{
					attempt[loc] = letter;
					loc = target.find(letter, loc + 1);
				}
			}

			cout << "�����ϴ� �ܾ�: " << attempt << '\n';
			if (attempt != target)
			{
				if (badchars.length() > 0)
					cout << "Ʋ���� ������ ���ڵ�: " << badchars << '\n';
				cout << "Ʋ�� �� �ִ� ��ȸ: " << guesses << "��\n";
			}
			cout << "--------------------------\n";
		}

		cout << "--------------------------\n";
		if (guesses > 0)
			cout << "�׷���. �װ��� �������� �ܾ��! \n";
		else 
			cout << "��Ÿ������. �������� �ܾ�� " << target << "�̴�! \n";

		cout << "������ �ٽ� �����ҷ�? <y/n> ";
		cin >> play;
		play = tolower(play);
	}

	cout << "���α׷� �����Ѵ�. ���� \n";
	return 0;
}