#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// istringstream
int main() {
	string str = "yoo study 777";
	istringstream iss(str);

	while (iss >> str)
	{
		cout << str << '\n';
	}

	return 0;
}

// ostringstream
int main() {
	const int n = 5;
	string str[n] = { "yoo", "study", "777", "  ", "0.55" };
	ostringstream oss;
	for (int i = 0; i < n; i++)
	{
		oss << str[i];
	}
	cout << oss.str() << '\n';

	return 0;
}

// stringstream + getline
int main() {
	string str = "yoo@study@777";
	istringstream iss(str);
	string buffer;
	while (getline(iss, buffer, '@'))
	{
		cout << buffer << '\n';
	}

	return 0;
}