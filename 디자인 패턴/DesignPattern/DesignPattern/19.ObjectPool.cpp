#include <bits/stdc++.h>
using namespace std;

/*
class Particle
{
public:
	Particle() : framesLeft_(0) {}
	void init(double x, double y, double xVel, double yVel, int lifetime)
	{
		x_ = x;
		y_ = y;
		xVel_ = xVel;
		yVel_ = yVel;
		framesLeft_ = lifetime;
	}
	bool animate()
	{
		if (!inUse()) return;

		framesLeft_--;
		x_ += xVel_;
		y_ += yVel_;

		return framesLeft_ == 0;
	}
	bool inUse() const { return framesLeft_ > 0; }

	Particle* getNext() const { return state_.next; }
	void setNext(Particle* next)
	{
		state_.next = next;
	}

private:
	int framesLeft_;
	union
	{
		// ��� ���� ���� ����
		struct
		{
			double x, y;
			double xVel, yVel;
		} live;

		// ��� ���� �ƴ� ���� ����
		Particle* next;
	} state_;
};

class ParticlePool
{
public:
	ParticlePool()
	{
		// ó�� ��ƼŬ���� ��� �����ϴ�.
		firstAvailable_ = &particles_[0];

		// ��� ��ƼŬ�� ���� ��ƼŬ�� ����Ų��.
		for (int i = 0; i < POOL_SIZE - 1; i++)
		{
			particles_[i].setNext(&particles_[i + 1]);
		}

		// ������ ��ƼŬ���� ����Ʈ�� �����Ѵ�.
		particles_[POOL_SIZE - 1].setNext(nullptr);
	}

	void create(double x, double y, double xVel, double yVel, int lifetime)
	{
		// Ǯ�� ��� ���� �������� Ȯ���Ѵ�.
		assert(firstAvailable_ != nullptr);

		// ���� ��ƼŬ�� '��ĭ ���'���� �����Ѵ�.
		Particle* newParticle = firstAvailable_;
		firstAvailable_ = newParticle->getNext();

		newParticle->init(x, y, xVel, yVel, lifetime);
	}
	void animate()
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			if (particles_[i].animate())
			{
				// ��� ���� ��ƼŬ�� ��ĭ ����Ʈ �տ� �߰��Ѵ�.
				particles_[i].setNext(firstAvailable_);
				firstAvailable_ = &particles_[i];
			}
		}
	}

private:
	Particle* firstAvailable_;
	static const int POOL_SIZE = 100;
	Particle particles_[POOL_SIZE];
};
*/



// ��ü�� Ǯ�� ���ؼ��� ������ �� �ֵ��� ����
class Particle
{
	friend class ParticlePool;

private:
	Particle() : inUse_(false) {}
	bool inUse_;
};

class ParticlePool
{
	Particle pool_[100];
};


// ��� �� ���¸� ��ü �ܺο��� ����
template <class TObject>
class GenericPool
{
private:
	static const int POOL_SIZE = 100;

	TObject pool_[POOL_SIZE];
	bool inUse_[POOL_SIZE];	// ��Ʈ �ʵ� ���� �α�
};



// ��ü �ۿ��� �ʱ�ȭ
class Particle
{
public:
	// �پ��� �ʱ�ȭ ���
	void init(double x, double y);
	void init(double x, double y, double angle);
};

class ParticlePool
{
public:
	Particle* create()
	{
		// ��� ������ ��ƼŬ�� ���� ���۷����� ��ȯ
	}
private:
	Particle pool_[100];
};

int main()
{
	ParticlePool pool;
	pool.create()->init(1, 2);
	pool.create()->init(1, 2, 0.3);

	
	Particle* particle = pool.create();
	if (particle != nullptr) particle->init(1, 2);
}