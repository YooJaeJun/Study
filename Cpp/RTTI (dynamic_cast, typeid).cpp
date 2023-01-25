// RTTI - dynamic_cast, typeid, type_info ���
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
using namespace std;

class Grand
{
private:
	int hold;
public:
	Grand(int h = 0) : hold(h) {}
	virtual void Speak() const { cout << "���� Grand Ŭ������!\n"; }
	virtual int Value() const { return hold; }
};

class Superb : public Grand
{
public:
	Superb(int h = 0) : Grand(h) {}
	void Speak() const override { cout << "���� Superb Ŭ������!!\n"; }
	virtual void Say() const
	{
		cout << "���� ������ �ִ� Superb ���� " << Value() << "�̴�.\n";
	}
};

class Magnificent : public Superb
{
private:
	char ch;
public:
	Magnificent(int h = 0, char cv = 'A') : Superb(h), ch(cv) {}
	void Speak() const override { cout << "���� Magnificent Ŭ������!!!\n"; }
	void Say() const override
	{
		cout << "���� ������ �ִ� ���ڴ� " << ch << "�̰�, ������ " << Value() << "�̴�.\n";
	}
};

Grand* GetOne()
{
	Grand* p = nullptr;
	switch (rand() % 3)
	{
	case 0:
		p = new Grand(rand() % 100);
		break;
	case 1:
		p = new Superb(rand() % 100);
		break;
	case 2:
		p = new Magnificent(rand() % 100, 'A' + rand() % 26);
		break;
	default:
		break;
	}
	return p;
}

int main()
{
	srand(time(0));
	Grand* pg;
	Superb* ps;
	for (int i = 0; i < 5; i++)
	{
		pg = GetOne();
		cout << "���� " << typeid(*pg).name() << "���� ó���ϰ� �ֽ��ϴ�.\n";
		pg->Speak();
		if (ps = dynamic_cast<Superb*>(pg))
			ps->Say();
		if (typeid(Magnificent) == typeid(*pg))
			cout << "�׷�, �ʾ߸��� ��¥ Magnificent Ŭ������.\n";
	}
	return 0;
}