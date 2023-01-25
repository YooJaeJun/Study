#include <iostream>
#include <string>
#include <cstring>
using namespace std;

bool AlmostEqualFloat(const float x, const float y)
{
	return fabsf(x - y) <= std::numeric_limits<float>::epsilon() * fabsf(x + y) * static_cast<float>(7)
		|| fabsf(x - y) < std::numeric_limits<float>::min();
}

string ToString(float f)
{
	string ret;
	float temp = f;

	while (f >= 1.0f)
	{
		ret += to_string((int)fmod(f, 10.0f));
		f /= 10.0f;
	}

	reverse(ret.begin(), ret.end());
	ret += '.';

	f = temp;
	while (false == AlmostEqualFloat(f, ceil(f)))
	{
		f *= 10;
		ret += to_string((int)fmod(f, 10));
	}

	return ret;
}

int main()
{
	cout << ToString(143.141592) << endl;
}