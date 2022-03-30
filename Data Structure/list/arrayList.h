#pragma once
#include <iostream>

const int maxListSize = 100;


inline void error(const char* s) {
	printf("%s", s);
	exit(1);
}

class arrayList {
	int data[maxListSize];
	int length;
public:
	arrayList() { length = 0; }
	void insert(int pos, int e) {
		if (!isFull() && pos >= 0 && pos <= length) {
			for (int i = length; i > pos; i--) {
				data[i] = data[i - 1];
			}
			data[pos] = e;
			length++;
		}
		else { error("��ȭ���� ���� or ������ġ ����"); }
	}
	void remove(int pos) {
		if (!isEmpty() && pos >= 0 && pos < length) {
			for (int i = pos + 1; i < length; i++) {
				data[i - 1] = data[i];
			}
			length--;
		}
		else { error("������� ���� or ������ġ ����"); }
	}
	int getEntry(int pos) { return data[pos]; }
	bool isEmpty() { return length == 0; }
	bool isFull() { return length == maxListSize; }
	bool find(int item) {
		for (int i = 0; i != length; i++) {
			if (data[i] == item) { return true; }
		}
		return false;
	}
	void replace(int pos, int e) {
		data[pos] = e;
	}
	int size() { return length; }
	void display() {
		printf("[�迭�α����Ѹ���Ʈ ��ü �׸� �� = %d] : ", size());
		for (int i = 0; i != size(); i++) {
			printf("[%d] ", data[i]);
		}
		printf("\n");
	}
	void clear() { length = 0; }
};