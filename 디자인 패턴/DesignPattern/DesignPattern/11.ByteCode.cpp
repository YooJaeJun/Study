#include <bits/stdc++.h>
using namespace std;

class Expression
{
public:
	virtual ~Expression() {}
	virtual double evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
	NumberExpression(double value) : value_(value) {}
	virtual double evaluate() { return value_; }

private:
	double value_;
};

class AdditionExpression : public Expression
{
public:
	AdditionExpression(Expression* left, Expression* right)
		: left_(left), right_(right) {}

	virtual double evaluate()
	{
		double left = left_->evaluate();
		double right = right_->evaluate();

		return left + right;
	}

private:
	Expression* left_;
	Expression* right_;
};

enum Instruction
{
	INST_SET_HEALTH = 0x00,
	INST_SET_WISDOM = 0X01,
	INST_SET_AGILITY = 0X02,
	INST_PLAY_SOUND = 0X03,
	INST_SPAWN_PARTICLES = 0X04,
	INST_LITERAL,
	INST_GET_HEALTH,
	INST_GET_WISDOM,
	INST_GET_AGILITY,
	INST_ADD,
};

class VM
{
public:
	VM() : stackSize_(0) {}

	void interpret(char bytecod[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			char instruction = bytecode[i];

			switch (instruction)
			{
			case INST_SET_HEALTH:
				int amount = pop();
				int wizard = pop();
				setHealth(0, 100);
				break;
			case INST_SET_WISDOM:
				break;
			case INST_SET_AGILITY:
				break;
			case INST_PLAY_SOUND:
				playSound(pop());
				break;
			case INST_SPAWN_PARTICLES:
				spawnParticles(pop());
				break;
			case INST_LITERAL:
				// 바이트코드에서 다음 바이트 값을 읽는다.
				int value = bytecode[++i];
				push(value);
				break;
			case INST_GET_HEALTH:
				int wizard = pop();
				push(getHealth(wizard));
				break;
				break;
			case INST_GET_WISDOM:
				break;
			case INST_GET_AGILITY:
				break;
			case INST_ADD:
				int b = pop();
				int a = pop();
				push(a + b);
				break;
				break;
			default:
				break;
			}
		}
	}

private:
	void push(int value)
	{
		assert(stackSize_ < MAX_STACK);
		stack_[stackSize_++] = value;
	}

	int pop()
	{
		assert(stackSize_ > 0);
		return stack_[--stackSize_];
	}

private:
	static const int MAX_STACK = 128;
	int stackSize_;
	int stack_[MAX_STACK];
};


enum ValueType
{
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING,
};

struct Value
{
	ValueType type;
	union
	{
		int intValue;
		double doubleValue;
		char* stringValue;
	};
};


class Value
{
public:
	virtual ~Value() {}
	virtual ValueType type() = 0;
	virtual int asInt()
	{
		assert(false);
		return 0;
	}
};

class IntValue : public Value
{
public:
	IntValue(int value) : value_(value) {}

	virtual ValueType type() { return TYPE_INT; }
	virtual int asInt() { return value_; }

private:
	int value_;
};