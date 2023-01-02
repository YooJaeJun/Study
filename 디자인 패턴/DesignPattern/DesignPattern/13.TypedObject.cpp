#include <bits/stdc++.h>
using namespace std;

// 고전 상속 구조
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
		return "용이 불을 뿜습니다!";
	}
};

class Troll : public Monster
{
public:
	Troll() : Monster(48) {}
	virtual const char* getAttack()
	{
		return "트롤이 당신을 곤봉으로 내리칩니다!";
	}
};
*/


// 메모리 먼저 할당한 후 메모리 영역에 클래스를 할당하는 방식
/*ㅌ
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
	int health_;	// 최대(초기) 체력
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
	int health_;	// 현재 체력
	Breed& breed_;
};

int main()
{
	Breed someBreed;
	Monster* monster = new Monster(someBreed);
}
*/

// 클래스의 생성자를 호출해 클래스가 알아서 새 인스턴스 생성 <- 팩토리 메서드 패턴
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
	int health_;	// 최대(초기) 체력
	const char* attack_;
};

int main()
{
	Breed someBreed;
	Monster* monster = someBreed.newMonster();
}
*/


// 종족 객체도 상위 종족 객체
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
			return "몬스터가 힘없이 팔을 휘두릅니다.";
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
	Breed troll(nullptr, 25, "죽어랏");
}

int main() {
}