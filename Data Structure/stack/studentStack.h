#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "student.h"
/// <summary>
/// �л� ����
/// </summary>
inline void error(const char* s) {
	printf("%s", s);
	exit(1);
}


class studentStack {
public:
	studentStack() : top(-1) {
		for (student& elem : data) {
			elem = { 0, "", "" };
		}
	}
	void push(const student& stu) {
		if (isFull()) {
			error("���� ���� �ʰ�\n");
		}
		data[++top] = stu;
	}
	student pop() {
		if (isEmpty()) {
			error("���� ����\n");
		}
		return data[top--];
	}
	student peek() {
		if (isEmpty()) {
			error("���� ����\n");
		}
		return data[top--];
	}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top + 1 == studentMax;
	}
	void display() {
		for (int i = 0; i <= top; i++) {
			data[i].display();
		}
	}
private:
	int top;
	student data[studentMax];
};
