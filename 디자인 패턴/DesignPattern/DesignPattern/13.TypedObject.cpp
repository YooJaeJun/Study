#include <bits/stdc++.h>
using namespace std;

// ���� ��� ����
/*
class Monster
{
public:
	virtual ~Monster() {}
	virtual const char* getAttack() = 0;

protected:
	Monster(int startingHealth) : health_(startingHealth) {}

private:
	int health_;
};

class Dragon : public Monster
{
	Dragon() : Monster(230) {}
	virtual const char* getAttack()
	{
		return "���� ���� �ս��ϴ�!";
	}
};

class Troll : public Monster
{
public:
	Troll() : Monster(48) {}
	virtual const char* getAttack()
	{
		return "Ʈ���� ����� ������� ����Ĩ�ϴ�!";
	}
};
*/


// �޸� ���� �Ҵ��� �� �޸� ������ Ŭ������ �Ҵ��ϴ� ���
/*��
class Breed
{
public:
	Breed(int health, const char* attack)
		: health_(health),
		attack_(attack)
	{}
	int getHealth() { return health_; }
	const char* getAttack() { return attack_; }

private:
	int health_;	// �ִ�(�ʱ�) ü��
	const char* attack_;
};

class Monster
{
public:
	Monster(Breed& breed)
		: health_(breed.getHealth()),
		breed_(breed)
	{}
	const char* getAttack() { return breed_.getAttack(); }

private:
	int health_;	// ���� ü��
	Breed& breed_;
};

int main()
{
	Breed someBreed;
	Monster* monster = new Monster(someBreed);
}
*/

// Ŭ������ �����ڸ� ȣ���� Ŭ������ �˾Ƽ� �� �ν��Ͻ� ���� <- ���丮 �޼��� ����
/*
class Breed;

class Monster
{
	friend class Breed;

public:
	const char* getAttack() { return breed_.getAttack(); }

private:
	Monster(Breed& breed)
		: health_(breed.getHealth()),
		breed_(breed)
	{}
	int health_;
	Breed& breed_;
};

class Breed
{
public:
	Monster* newMonster()
	{
		return new Monster(*this);
	}
	int getHealth() { return health_; }
	const char* getAttack() { return attack_; }

private:
	int health_;	// �ִ�(�ʱ�) ü��
	const char* attack_;
};

int main()
{
	Breed someBreed;
	Monster* monster = someBreed.newMonster();
}
*/


// ���� ��ü�� ���� ���� ��ü
class Breed
{
public:
	Breed(Breed* parent, int health, const char* attack)
		: parent_(parent),
		health_(health),
		attack_(attack)
	{
		if (parent != nullptr)
		{
			if (health == 0)
				health_ = parent->getHealth();
			if (attack == nullptr)
				attack_ = parent->getAttack();
		}
	}

	int getHealth() { return health_; }
	const char* getAttack() { return attack_; }

private:
	Breed* parent_;
	int health_;
	const char* attack_;
};

class Monster
{
	friend class Breed;

public:
	Breed& getBreed() { return breed_; }
	const char* getAttack()
	{
		if (health_ < LOW_HEALTH)
		{
			return "���Ͱ� ������ ���� �ֵθ��ϴ�.";
		}
		return breed_.getAttack();
	}

private:
	Monster(Breed& breed)
		: health_(breed.getHealth()),
		breed_(breed)
	{}
	int health_;
	Breed& breed_;
};

int main()
{
	Breed troll(nullptr, 25, "�׾��");
}

int main() {
}