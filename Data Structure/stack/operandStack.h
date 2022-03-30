#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
/// <summary>
/// 사칙연산 후위 표기 수식
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
			error("스택 범위 초과\n");
		}
		data[++top] = item;
	}
	double pop() {
		if (isEmpty()) {
			error("스택 없음\n");
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