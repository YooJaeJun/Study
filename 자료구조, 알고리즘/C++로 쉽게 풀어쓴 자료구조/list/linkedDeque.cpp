#include "linkedDeque.h"
void main() {
	linkedDeque deq;
	for (int i = 1; i < 10; i++) {
		if (i % 2) deq.addFront(new node2(i));
		else deq.addRear(new node2(i));
	}
	deq.display();
	delete deq.deleteFront();
	delete deq.deleteRear();
	delete deq.deleteFront();
	deq.display();
}