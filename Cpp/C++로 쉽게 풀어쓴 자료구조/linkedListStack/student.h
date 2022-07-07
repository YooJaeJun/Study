#pragma once
#include <iostream>

const int studentMax = 100;
class student {
public:
	student(int i = 0, const char* n = "", const char* d = "") {
		set(i, n, d);
	}
	void set(int i, const char* n, const char* d) {
		id = i;
		if (n != nullptr) {
			strcpy_s(name, n);
		}
		if (d != nullptr) {
			strcpy_s(dept, d);
		}
	}
	void display() {
		printf("Id: %d / 이름: %s / 설명: %s\n", id, name, dept);
	}
public:
	int id;
	char name[studentMax];
	char dept[studentMax];
};