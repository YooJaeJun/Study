#pragma once
#include <cstdio>
#include <cstdlib>
#include <assert.h>
using namespace std;

const int maxSize = 10;

inline void error(const char s[]) {
	printf("%s", s);
	exit(1);
}

class circularQueue {
protected:
	int front;
	int rear;
	int data[maxSize];
public:
	circularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % maxSize == front; }
	void enqueue(int val) {
		if (isFull()) {
			error(" error: 큐가 포화상태입니다\n");
		}
		else {
			rear = (rear + 1) % maxSize;
			data[rear] = val;
		}
	}
	int dequeue() {
		if (isEmpty()) {
			error(" error: 큐가 공백 상태입니다.\n");
		}
		else {
			front = (front + 1) % maxSize;
			return data[front];
		}
	}
	int peek() {
		if (isEmpty()) {
			error(" error: 큐가 공백 상태입니다.\n");
		}
		else {
			return data[(front + 1) % maxSize];
		}
	}
	void display() {
		printf("큐: ");
		int maxi = (front < rear) ? rear : rear + maxSize;
		for (int i = front + 1; i <= maxi; i++) {
			printf("%d ", data[i % maxSize]);
		}
		printf("\n");
	}
};