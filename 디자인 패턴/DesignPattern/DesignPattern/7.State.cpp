#include <bits/stdc++.h>
using namespace std;

// enum ...

class Input 
{};

class Heroine
{
public:
	virtual void handleInput(Input input)
	{
		state_->handleInput(*this, input);
		equipment_->handleInput(*this, input);
		//if (state_ != nullptr)
		//{
		//	delete state_;
		//	state_ = state;

		//	state_->enter(*this);
		//}
	}
	virtual void update() { state_->update(*this); }

private:
	HeroineState* state_;
	HeroineState* equipment_;
};

class HeroineState
{
public:
	virtual ~HeroineState() {}
	virtual void enter(Heroine& heroine) {}
	virtual void handleInput(Heroine& heroine, Input input) {}
	virtual void update(Heroine& heroine) {}

	static StandingState stading;
	static DuckingState ducking;
	// 등등
};

class StandingState : public HeroineState
{
public:
	StandingState() {}

	virtual void enter(Heroine& heroine)
	{
		heroine.setGraphics(IMAGE_STAND);
	}
};

class OnGroundState : public HeroineState
{
public:
	virtual void handleInput(Heroine& heroine, Input input)
	{
		if (input == PRESS_B) {} // 점프
		else if (input == PRESS_DOWN) {} // 엎드리기
	}
};

class DuckingState : public OnGroundState
{
public:
	DuckingState() : chargeTime_(0) {}

	virtual void handleInput(Heroine& heroine, Input input) 
	{
		if (input == RELEASE_DOWN) {} // 서기
		else
		{
			// 따로 입력 처리 없이, 상위 상태로 보낸다.
			OnGroundState::handleInput(heroine, input);
		}
	}

	virtual void update(Heroine& heroine) 
	{
		chargeTime_++;
		if (chargeTime_ > MAX_CHARGE)
		{
			heroine.superBomb();
		}
	}

private:
	int chargeTime_;
};


int main()
{
	Heroine heroine;
	heroine.state_ = &HeroineState::jumping;
	heroine.setGraphics(IMAGE_JUMP);
}