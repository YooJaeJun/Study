#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Character
{
public:
	void Set(T name)
	{
		this->name = name;
	}

	virtual void Print() = 0;

protected:
	T name;
};

class Player : public Character<int>
{
public:
	void Print() override
	{
		printf("플레이어: %d\n", name);
	}

private:
};

class Enemy : public Character<string>
{
public:
	void Print() override
	{
		printf("에너미: %s\n", name.c_str());
	}
};

int main()
{
	Player ob;
	ob.Set(20);
	ob.Print();

	Enemy obs;
	obs.Set("Oak");
	obs.Print();
}