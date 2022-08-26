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
	cout << "행맨 ㄱㄱ? <y/n> ";
	cin >> play;
	play = tolower(play);
	while (play == 'y')
	{
		string target = wordlist[rand() % num];
		int length = target.length();
		string attempt(length, '-');
		int guesses = 6;
		cout << "--------------------------\n" 
			<< "단어 추측해봐!\n"
			<< length << "개의 문자로 이루어져 있어.\n"
			<< "한 번에 한 문자씩 추측해봐.\n"
			<< "틀릴 수 있는 기회: " << guesses << "번\n";
		cout << "추측하는 단어: " << attempt << '\n'
			<< "--------------------------\n";

		string badchars;
		while (guesses > 0 && attempt != target)
		{
			char letter;
			cout << "문자 추측해봐: ";
			cin >> letter;

			if (badchars.find(letter) != string::npos ||
				attempt.find(letter) != string::npos)
			{
				cout << "이미 추측한 문자야!! 다시 해!!! \n";
				continue;
			}
			int loc = target.find(letter);
			if (loc == string::npos)
			{
				cout << "땡! 틀렸지롱 \n";
				--guesses;
				badchars += letter;
			}
			else
			{
				cout << "딩동댕! 맞았엉 \n";
				attempt[loc] = letter;
				// 같은 문자가 또 있는지 검사
				loc = target.find(letter, loc + 1);
				while (loc != string::npos)
				{
					attempt[loc] = letter;
					loc = target.find(letter, loc + 1);
				}
			}

			cout << "추측하는 단어: " << attempt << '\n';
			if (attempt != target)
			{
				if (badchars.length() > 0)
					cout << "틀리게 추측한 문자들: " << badchars << '\n';
				cout << "틀릴 수 있는 기회: " << guesses << "번\n";
			}
			cout << "--------------------------\n";
		}

		cout << "--------------------------\n";
		if (guesses > 0)
			cout << "그렇다. 그것이 수수께끼 단어다! \n";
		else 
			cout << "안타깝구만. 수수께끼 단어는 " << target << "이다! \n";

		cout << "게임을 다시 시작할래? <y/n> ";
		cin >> play;
		play = tolower(play);
	}

	cout << "프로그램 종료한다. 빠이 \n";
	return 0;
}