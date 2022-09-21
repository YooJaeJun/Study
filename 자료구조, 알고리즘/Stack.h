#pragma once
#include <iostream>

typedef unsigned long Item;

class Stack
{
private:
	enum { MAX = 10 };
	Item items[MAX];
	Item top;
public:
	Stack();
	const Item& getTop() const;
	bool isempty() const;
	bool isfull() const;
	bool push(const Item& item);
	bool pop(Item& item);
};