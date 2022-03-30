#pragma once
// ����� �����͸� �����ϴ� ť Ŭ����
#include "binaryNode.h"
#include <stdlib.h>
inline void error(const char* str) {
	fprintf(stderr, "%s\n", str);
	exit(1);
}
const int maxQueueSize = 100;

class circularQueue {
	int front;
	int rear;
	binaryNode* data[maxQueueSize];
public:
	circularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % maxQueueSize == front; }
	void enqueue(binaryNode* n) {
		if (isFull()) { error("Error: ť�� ��ȭ�����Դϴ�.\n"); }
		else {
			rear = (rear + 1) % maxQueueSize;
			data[rear] = n;
		}
	}
	binaryNode* dequeue() {
		if (isEmpty()) { error("Error: ť�� ��������Դϴ�.\n"); }
		else {
			front = (front + 1) % maxQueueSize;
			return data[front];
		}
	}
};