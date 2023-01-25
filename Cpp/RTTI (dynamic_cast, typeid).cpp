// RTTI - dynamic_cast, typeid, type_info 사용
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
	virtual void Speak() const { cout << "나는 Grand 클래스다!\n"; }
	virtual int Value() const { return hold; }
};

class Superb : public Grand
{
public:
	Superb(int h = 0) : Grand(h) {}
	void Speak() const override { cout << "나는 Superb 클래스다!!\n"; }
	virtual void Say() const
	{
		cout << "내가 가지고 있는 Superb 값은 " << Value() << "이다.\n";
	}
};

class Magnificent : public Superb
{
private:
	char ch;
public:
	Magnificent(int h = 0, char cv = 'A') : Superb(h), ch(cv) {}
	void Speak() const override { cout << "나는 Magnificent 클래스다!!!\n"; }
	void Say() const override
	{
		cout << "내가 가지고 있는 문자는 " << ch << "이고, 정수는 " << Value() << "이다.\n";
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
		cout << "지금 " << typeid(*pg).name() << "형을 처리하고 있습니다.\n";
		pg->Speak();
		if (ps = dynamic_cast<Superb*>(pg))
			ps->Say();
		if (typeid(Magnificent) == typeid(*pg))
			cout << "그래, 너야말로 진짜 Magnificent 클래스다.\n";
	}
	return 0;
}