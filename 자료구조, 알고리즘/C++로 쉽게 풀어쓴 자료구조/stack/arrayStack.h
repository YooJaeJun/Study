#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

/// <summary>
/// ����
/// </summary>
const int arrMax = 100;

inline void error(const char s[]) {
	printf("%s", s);
	exit(1);
}

class arrayStack {
public:
	arrayStack() : top(-1) {
	}
	void push(int item) {
		if (isFull()) {
			error("���� ���� �ʰ�\n");
		}
		data[++top] = item;
	}
	int pop() {
		if (isEmpty()) {
			error("���� ����\n");
		}
		return data[top--];
	}
	int peek() {
		if (isEmpty()) {
			error("���� ����\n");
		}
		return data[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top + 1 == arrMax;
	}
	void display() {
		for (int i = 0; i <= top; i++) {
			printf("data[%d] = %d\n", i, data[i]);
		}
	}
private:
	int top;
	int data[arrMax];
};