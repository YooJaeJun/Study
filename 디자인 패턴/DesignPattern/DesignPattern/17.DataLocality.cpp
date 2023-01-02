#include <bits/stdc++.h>
#include <vector>
using namespace std;

class GameEntity
{
public:
	GameEntity(AIComponent* ai,
		PhysicsComponent* physics,
		RenderComponent* render)
		: ai_(ai), physics_(physics), render_(render) {}
	AIComponent* ai() { return ai_; }
	PhysicsComponent* physics() { return physics_; }
	RenderComponent* render() { return render_; }

private:
	AIComponent* ai_;
	PhysicsComponent* physics_;
	RenderComponent* render_;
};

class AIComponent
{
public:
	void update() { /*작업 후 상태 변경*/ }

private:
	// 목표, 기분 등등
};

class PhysicsComponent
{
public:
	void update() { /*작업 후 상태 변경*/ }

private:
	// 강체(rigid body), 속도, 질량 등등
};

class RenderComponent
{
public:
	void render() { /*작업 후 상태 변경*/ }

private:
	// 메시, 텍스처, 셰이더 등등
};


int main()
{
	vector<GameEntity*> entities;
	int numEntities = entities.size();
	bool gameOver = false;
	while (!gameOver)
	{
		// AI를 처리한다.
		for (int i = 0; i < numEntities; i++)
			entities[i]->ai()->update();

		// 물리를 업데이트한다.
		for (int i = 0; i < numEntities; i++)
			entities[i]->physics()->update();

		// 화면에 그린다.
		for (int i = 0; i < numEntities; i++)
			entities[i]->render()->render();
	}

	const int MAX_ENTITIES = 10;
	AIComponent* aiComponents = new AIComponent[MAX_ENTITIES];
	PhysicsComponent* physicsComponents = new PhysicsComponent[MAX_ENTITIES];
	RenderComponent* renderComponents = new RenderComponent[MAX_ENTITIES];

	while (!gameOver)
	{
		for (int i = 0; i < numEntities; i++)
			aiComponents[i].update();

		for (int i = 0; i < numEntities; i++)
			physicsComponents[i].update();

		for (int i = 0; i < numEntities; i++)
			renderComponents[i].render();
	}
}


class Particle
{
public:
	void update() { /*중력 등등*/ }
	// 위치, 속도, 등등
};

class ParticleSystem
{
public:
	ParticleSystem() : numParticles_(0) {}
	void update()
	{
		// 캐시 미스 유발
		/*
		for (int i = 0; i < numParticles_; i++)
		{
			if (particles_[i].isActive())	
			{
				particles_[i].update();
			}
		}
		*/

		// 활성 파티클만 맨 앞으로 모아두기
		for (int i = 0; i < numActive_; i++)
			particles[i].update();
	}
	void activateParticle(int index)
	{
		// 비활성 상태여야 함
		assert(index >= numActive_);

		// 새로 활성화된 파티클을 비활성 파티클 중 맨 앞에 있는 것과 바꿔서
		// 활성 파티클 중에서 맨 뒤에 가게 한다.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;

		// 이제 활성 파티클이 하나 늘었다.
		numActive_++;
	}
	void deactivateParticle(int index)
	{
		// 활성 파티클이어야 함
		assert(index < numActive_);

		// 파티클이 하나 줄었다.
		numActive_--;

		// 마지막 활성 파티클과 맞바꿔서
		// 비활성 파티클 중에서 맨 앞에 가게 한다.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;
	}

private:
	static const int MAX_PARTICLES = 100000;
	int numParticles_;
	Particle particles_[MAX_PARTICLES];
};


// 빈번한 코드와 한산한 코드 나누기
class AIComponent
{
public:
	void update() {}

private:
	// 자주
	Animation* animation_;
	double energy_;
	Vector goalPos_;
	// 한산
	LootDrop* loot_;
	// 읽어야 할 전체 데이터 크기가 크다 보니 캐시 미스가 더 자주 발생한다.
};

class LootDrop
{
	friend class AIComponet;
	LootType drop_;
	int minDrops_;
	int maxDrops_;
	double chanceOfDrop_;
};