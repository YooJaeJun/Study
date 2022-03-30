#pragma once
#include "circularQueue.h"

class circularDeque : public circularQueue {
public:
	circularDeque() {
	}
	void addRear(int val) {
		enqueue(val);
	}
	int deleteFront() {
		return dequeue();
	}
	int getFront() {
		return peek();
	}
	void addFront(int val) {
		if (isFull()) {
			error("µ¦ÀÌ °¡µæ Ã¡½À´Ï´Ù.");
		}
		else {
			data[front] = val;
			front = (front - 1 + maxSize) % maxSize;	//
		}
	}
	void deleteRear() {
		if (isEmpty()) {
			error("µ¦ÀÌ °ø¹é");
		}
		else {
			int ret = data[rear];
			rear = (rear - 1 + maxSize) % maxSize;
		}
	}
	int gerRear() {
		if (isEmpty()) {
			error("µ¦ÀÌ °ø¹é");
		}
		else {
			return data[rear];
		}
	}
	virtual void display() final {
		printf("µ¦ÀÇ ³»¿ë: ");
		int maxi = (front < rear) ? rear : rear + maxSize;
		for (int i = front + 1; i <= maxi; i++) {
			printf("%d ", data[i % maxSize]);
		}
		printf("\n");
	}
};