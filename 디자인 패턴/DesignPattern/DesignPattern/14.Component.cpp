#include <bits/stdc++.h>
using namespace std;

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

class GameObject
{
public:
	int velocity;
	int x, y;

public:
	GameObject(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics)
		: input_(input) 
	{}

	GameObject* createBjorn()
	{
		return new GameObject(
			new PlayerInputComponent(),
			new BjornPhysicsComponent(),
			new BjornGraphicsComponent());
	}

	void update(World& world, Graphics& graphics)
	{
		// �Է�
		input_->update(*this);
		// �ӵ� ��ġ
		physics_->update(*this, world);
		// ��������Ʈ
		graphics_->update(*this, graphics);
	}

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;
};

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(GameObject& bjorn) = 0;

private:
	static const int WALK_ACCELERATION = 1;
};

class PlayerInputComponent : public InputComponent
{
public:
	virtual void update(GameObject& bjorn)
	{
		switch (Controller::getJoystickDirection())
		{
		case DIR_LEFT:
			bjorn.velocity_ -= WALK_ACCELERATION;
			break;
		case DIR_RIGHT:
			bjorn.velocity_ += WALK_ACCELERATION;
			break;
		}
	}

private:
	static const int WALK_ACCELERATION = 1;
};

class DemoInputComponent : public InputComponent
{
public:
	virtual void update(GameObject& bjorn)
	{ /*AI�� Bjorn �����ϴ� �ڵ�*/ }
};

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void update(GameObject& bjorn, World& world) = 0;

private:
	Volume volume_;
};

class BjornPhysicsComponent : public PhysicsComponent
{
public:
	virtual void update(GameObject& obj, World& world)
	{
		bjorn.x += bjorn.velocity;
		world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
	}
};

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(GameObject& bjorn, Graphics& graphics) = 0;

private:
	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};

/*
class BjornGraphicsComponent : public GraphicsComponent
{
public:
	virtual void update(GameObject& obj, Graphics& graphics) 
	{
		Sprite* sprite = &spriteStand_;
		if (bjorn.velocity < 0)
		{
			sprite = &spriteWalkLeft_;
		}
		else if (bjorn.velocity > 0)
		{
			sprite = &spriteWalkRight_;
		}
		graphics.draw(*sprite, bjorn.x, bjorn.y);
	}
};
*/

// ������Ʈ ���� �����ϴ� ���
class BjornGraphicsComponent
{
public:
	BjornGraphicsComponent(BjornPhysicsComponent* physics)
		: physics_(physics) {}

	void update(GameObject& obj, Graphics& graphics)
	{
		Sprite* sprite;
		if (!physics_->isOnGround())
		{
			sprite = &spriteJump_;
		}
		else {}
		graphics.draw(*sprite, obj.x, obj.y);
	}

private:
	BjornPhysicsComponent* physics_;

	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
	Sprite spriteJump_;
};

int main()
{
	// �Ϲ�
	// Bjorn* bjorn = new Bjorn(new PlayerInputComponent());
	// �����
	GameObject* bjorn = new GameObject(new DemoInputComponent());
}


// �޽��� �����ϴ� ���
class Component
{
public:
	virtual ~Component() {}
	virtual void receive(int message) = 0;
};

class ContainerObject
{
public:
	void send(int message)
	{
		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			if (components_[i] != nullptr)
			{
				components_[i]->receive(message);
			}
		}
	}

private:
	static const int MAX_COMPONENTS = 10;
	Component* components_[MAX_COMPONENTS];
};
