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
	void update() { /*�۾� �� ���� ����*/ }

private:
	// ��ǥ, ��� ���
};

class PhysicsComponent
{
public:
	void update() { /*�۾� �� ���� ����*/ }

private:
	// ��ü(rigid body), �ӵ�, ���� ���
};

class RenderComponent
{
public:
	void render() { /*�۾� �� ���� ����*/ }

private:
	// �޽�, �ؽ�ó, ���̴� ���
};


int main()
{
	vector<GameEntity*> entities;
	int numEntities = entities.size();
	bool gameOver = false;
	while (!gameOver)
	{
		// AI�� ó���Ѵ�.
		for (int i = 0; i < numEntities; i++)
			entities[i]->ai()->update();

		// ������ ������Ʈ�Ѵ�.
		for (int i = 0; i < numEntities; i++)
			entities[i]->physics()->update();

		// ȭ�鿡 �׸���.
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
	void update() { /*�߷� ���*/ }
	// ��ġ, �ӵ�, ���
};

class ParticleSystem
{
public:
	ParticleSystem() : numParticles_(0) {}
	void update()
	{
		// ĳ�� �̽� ����
		/*
		for (int i = 0; i < numParticles_; i++)
		{
			if (particles_[i].isActive())	
			{
				particles_[i].update();
			}
		}
		*/

		// Ȱ�� ��ƼŬ�� �� ������ ��Ƶα�
		for (int i = 0; i < numActive_; i++)
			particles[i].update();
	}
	void activateParticle(int index)
	{
		// ��Ȱ�� ���¿��� ��
		assert(index >= numActive_);

		// ���� Ȱ��ȭ�� ��ƼŬ�� ��Ȱ�� ��ƼŬ �� �� �տ� �ִ� �Ͱ� �ٲ㼭
		// Ȱ�� ��ƼŬ �߿��� �� �ڿ� ���� �Ѵ�.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;

		// ���� Ȱ�� ��ƼŬ�� �ϳ� �þ���.
		numActive_++;
	}
	void deactivateParticle(int index)
	{
		// Ȱ�� ��ƼŬ�̾�� ��
		assert(index < numActive_);

		// ��ƼŬ�� �ϳ� �پ���.
		numActive_--;

		// ������ Ȱ�� ��ƼŬ�� �¹ٲ㼭
		// ��Ȱ�� ��ƼŬ �߿��� �� �տ� ���� �Ѵ�.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;
	}

private:
	static const int MAX_PARTICLES = 100000;
	int numParticles_;
	Particle particles_[MAX_PARTICLES];
};


// ����� �ڵ�� �ѻ��� �ڵ� ������
class AIComponent
{
public:
	void update() {}

private:
	// ����
	Animation* animation_;
	double energy_;
	Vector goalPos_;
	// �ѻ�
	LootDrop* loot_;
	// �о�� �� ��ü ������ ũ�Ⱑ ũ�� ���� ĳ�� �̽��� �� ���� �߻��Ѵ�.
};

class LootDrop
{
	friend class AIComponet;
	LootType drop_;
	int minDrops_;
	int maxDrops_;
	double chanceOfDrop_;
};