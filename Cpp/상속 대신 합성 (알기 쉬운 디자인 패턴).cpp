#include <bits/stdc++.h>
using namespace std;

class Movement
{
protected:
	~Movement() {}
public:
	void Move();
};

class Walking : public Movement
{
public:
	void Move() { cout << "Walk\n"; }
};

class Flying : public Movement
{
public:
	void Move() { cout << "Fly\n"; }
};

class Swimming : public Movement
{
public:
	void Move() { cout << "Swim\n"; }
};


class Taste
{
protected:
	~Taste() {}
public:
	void Eat();
};

class PlantEating : public Taste
{
public:
	void Eat() { cout << "plant\n"; }
};

class FleshEating : public Taste
{
public:
	void Eat() { cout << "Flesh\n"; }
};


class PlantEatingAndWalkingMob : public Walking, public PlantEating
{
};

class FleshEatingAndFlyingMob : public Flying, public FleshEating
{
};


template <class TasteType, class MoveType>
class Mob : public TasteType, public MoveType
{
public:
	void Eat() { TasteType::Eat(); }	// 템플릿 특화를 위한 재정의
};

template<>
void Mob<FleshEating, Swimming>::Eat()
{
	// 기존 기능에 배를 삼키는 기능 추가
	cout << "Eat ship\n";
}


int main()
{
	Mob<FleshEating, Walking> ogre;
	Mob<FleshEating, Flying> wyvern;
	Mob<PlantEating, Walking> gnome;
	Mob<FleshEating, Swimming> shark;
	shark.Eat();
}