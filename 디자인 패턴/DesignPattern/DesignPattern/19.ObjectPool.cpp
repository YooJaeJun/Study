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
		// 사용 중일 때의 상태
		struct
		{
			double x, y;
			double xVel, yVel;
		} live;

		// 사용 중이 아닐 때의 상태
		Particle* next;
	} state_;
};

class ParticlePool
{
public:
	ParticlePool()
	{
		// 처음 파티클부터 사용 가능하다.
		firstAvailable_ = &particles_[0];

		// 모든 파티클은 다음 파티클을 가리킨다.
		for (int i = 0; i < POOL_SIZE - 1; i++)
		{
			particles_[i].setNext(&particles_[i + 1]);
		}

		// 마지막 파티클에서 리스트를 종료한다.
		particles_[POOL_SIZE - 1].setNext(nullptr);
	}

	void create(double x, double y, double xVel, double yVel, int lifetime)
	{
		// 풀이 비어 있지 않은지를 확인한다.
		assert(firstAvailable_ != nullptr);

		// 얻은 파티클을 '빈칸 목록'에서 제거한다.
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
				// 방금 죽은 파티클을 빈칸 리스트 앞에 추가한다.
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



// 객체가 풀을 통해서만 생성할 수 있도록 강제
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


// 사용 중 상태를 객체 외부에서 관리
template <class TObject>
class GenericPool
{
private:
	static const int POOL_SIZE = 100;

	TObject pool_[POOL_SIZE];
	bool inUse_[POOL_SIZE];	// 비트 필드 따로 두기
};



// 객체 밖에서 초기화
class Particle
{
public:
	// 다양한 초기화 방법
	void init(double x, double y);
	void init(double x, double y, double angle);
};

class ParticlePool
{
public:
	Particle* create()
	{
		// 사용 가능한 파티클에 대한 레퍼런스르 반환
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