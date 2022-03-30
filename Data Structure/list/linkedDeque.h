#pragma once
#include "dblLinkedList.h"
class linkedDeque : public dblLinkedList {
public:
	void addFront(node2* n) { insert(0, n); }
	node2* deleteFront() { return remove(0); }
	node2* getFront() { return getEntry(0); }
	void addRear(node2* n) { insert(size(), n); }
	node2* deleteRear() { return remove(size() - 1); }
	node2* getRear() { return getEntry(size() - 1); }
};