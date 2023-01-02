#include <bits/stdc++.h>
using namespace std;

class Entity
{
public:
	bool isOnSurface();
	void accelerate(float gravity);
	void update();
	bool isHero();
};


class Event
{};


class Observer
{
	friend class Subject;

public:
	Observer() : next_(nullptr) {}
	virtual ~Observer() {}
	virtual void onNotify(const Entity& entity, Event event) = 0;

private:
	Observer* next_;
};


class Acievements : public Observer
{
public:
	virtual void onNotify(const Entity& entity, Event event)
	{
		switch (event)
		{
		case EVENT_ENTITY_FELL:
			if (entity.isHero() && heroIsOnBridge_)
			{
				unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
			}
			break;
			// 그 외 다른 이벤트를 처리하고...
			// heroIsOnBridge_ 값을 업데이트한다..
		}
	}
	
private:
	void unlock(Acievements achievement)
	{
		// 아직 업적이 잠겨 있다면 잠금해제 한다..
	}
	bool heroIsOnBridge_;
};


class Subject
{
public:
	Subject() : head_(nullptr)
	{}

	void addObserver(Observer* observer)
	{
		// 배열에 추가한다..
		observer->next_ = head_;
		head_ = observer;
	}
	void removeObserver(Observer* observer)
	{
		// 배열에서 제거한다.
		if (head_ == observer)
		{
			head_ = observer->next_;
			observer->next_ = nullptr;
			return;
		}

		Observer* current = head_;
		while (current != nullptr)
		{
			if (current->next_ == observer)
			{
				current->next_ = observer->next_;
				observer->next_ = nullptr;
				return;
			}
			current = current->next_;
		}
	}
	// 그 외...

protected:
	void notify(const Entity& entity, Event event)
	{
		Observer* observer = head_;
		while (observer != nullptr)
		{
			observer->onNotify(entity, event);
			observer = observer->next_;
		}
	}

private:
	Observer* head_;
	Observer* observers_[MAX_OBSERVERS];
	int numObservers_;
};


class Physics : public Subject
{
public:
	void updateEntity(Entity& entity)
	{
		bool wasOnSurface = entity.isOnSurface();
		entity.accelerate(GRAVITY);
		entity.update();
		if (wasOnSurface && !entity.isOnSurface())
		{
			// 다리에서 떨어지기 업적
			notify(entity, EVENT_START_FALL);
		}
	}

private:
	const float GRAVITY = 10.0f;
};