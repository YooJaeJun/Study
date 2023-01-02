#include <bits/stdc++.h>
using namespace std;


class Monster
{
public:
	virtual ~Monster() {}
	virtual Monster* clone() = 0;
};

class Ghost : public Monster
{
public:
	Ghost(int health, int speed)
		: health_(health),
		speed_(speed)
	{}
	virtual Monster* clone()
	{
		return new Ghost(health_, speed_);
	}

protected:
	int health_;
	int speed_;
};



typedef Monster* (*SpawnCallback)();

class Spawner
{
public:
	virtual ~Spawner() {}
	Spawner(SpawnCallback spawn) : spawn_(spawn) {}
	virtual Monster* spawnMonster() = 0;

private:
	SpawnCallback spawn_;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual Monster* spawnMonster() { return new T(); }
};

Monster* spawnGhost()
{
	return new Ghost(15, 3);
}



int main()
{
	Spawner* ghostSpawner = new SpawnerFor<Ghost>();
}

