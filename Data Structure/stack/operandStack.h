#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
/// <summary>
/// ��Ģ���� ���� ǥ�� ����
/// </summary>

const int operandMax = 100;
inline void error(const char* s) {
	printf("%s", s);
	exit(1);
}
class operandStack {
public:
	operandStack() {
		top = -1;
	}
	void push(double item) {
		if (isFull()) {
			error("���� ���� �ʰ�\n");
		}
		data[++top] = item;
	}
	double pop() {
		if (isEmpty()) {
			error("���� ����\n");
		}
		return data[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top + 1 == operandMax;
	}
	void display() {
		for (int i = 0; i <= top; i++) {
			printf("data[%d] = %d\n", i, data[i]);
		}
	}
private:
	int top;
	int data[operandMax];
};