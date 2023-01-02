#include <bits/stdc++.h>
using namespace std;

/*
class Entity
{

};

int main()
{
	Entity skeleton;
	bool patrollingLeft = false;
	double x = 0;

	Entity leftStatue;
	Entity rightStatue;
	int leftStatueFrames = 0;
	int rightStatueFrames = 0;


	while (true)
	{
		if (patrollingLeft)
		{
			x--;
			if (x == 0) patrollingLeft = false;
		}
		else
		{
			x++;
			if (x == 100) patrollingLeft = true;
		}
		skeleton.setX(x);


		if (++leftStatueFrames == 90)
		{
			leftStatueFrames = 0;
			leftStatue.shootLightning();
		}
		if (++leftStatueFrames == 80)
		{
			rightStatueFrames = 0;
			rightStatue.shootLightning();
		}
	}
}
*/

int main()
{
	// objects_는 게임에서 업데이트 가능한 객체 배열
	int numObjectsThisTurn = numObjects_;
	for (int i = 0; i < numObjectsThisTurn; i++)
	{
		objects_[i]->update();
	}
}

class Entity
{
public:
	Entity() : x_(0), y_(0) {}
	virtual ~Entity() {}
	virtual void update() = 0;

	double x() const { return x_; }
	double y() const { return y_; }

	void setX(double x) { x_ = x; }
	void setY(double y) { y_ = y; }

private:
	double x_;
	double y_;
};

class World
{
public:
	World() : numEntities_(0) {}
	void gameLoop()
	{
		while (true)
		{
			// 유저 입력 처리...

			// 각 개체 업데이트
			for (int i = 0; i < numEntities_; i++)
			{
				entities_[i]->update();
			}

			// 물리, 렌더링...
		}
	}

private:
	Entity* entities_[MAX_ENTITIES];
	int numEntities_;
};

class Skeleton : public Entity
{
public:
	Skeleton() : patrollingLeft_(false) {}

	virtual void update(double elapsed)
	{
		if (patrollingLeft_)
		{
			x -= elapsed;
			if (x <= 0)
			{
				patrollingLeft_ = false;
				x = -x;
			}
		}
		else
		{
			x += elapsed;
			if (x <= 0)
			{
				patrollingLeft_ = true;
				x = 100 - (x - 100);
			}
		}
	}

private:
	bool patrollingLeft_;
};

class Statue : public Entity
{
public:
	Statue(int delay) : frames_(0), delay_(delay) {}

	virtual void update()
	{
		if (++frames_ == delay_)
		{
			shootLightning();

			// 타이머 초기화
			frames_ = 0;
		}
	}

	void shootLightning() {}

private:
	int frames_;
	int delay_;
};