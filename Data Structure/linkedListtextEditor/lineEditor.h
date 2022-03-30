#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "linkedList.h"
class lineEditor : public linkedList {
public:
	void display(FILE* fp = stdout) {
		int i = 0;
		for (node* p = getHead(); p != nullptr; p = p->getLink(), i++) {
			fprintf(stderr, "%d: ", i);
			p->print(fp);
		}
	}
	void insertLine() {
		int position;
		char line[maxCharPerLine];
		printf("입력행 번호: ");
		scanf_s("%d", &position);
		printf("입력행 내용: ");
		fflush(stdin);
		fgets(line, maxCharPerLine, stdin);
		insert(position, new node(line));
	}
	void deleteLine() {
		printf("삭제행 번호: ");
		int position;
		scanf_s("%d", &position);
		delete remove(position);
	}
	void replaceLine() {
		int position;
		char line[maxCharPerLine];
		printf("변경행 번호: ");
		scanf_s("%d", &position);
		printf("변경행 내용: ");
		fflush(stdin);
		fgets(line, maxCharPerLine, stdin);
		replace(position, new node(line));
	}
	void loadFile(const char* fname) {
		FILE* fp = fopen(fname, "r");
		if (fp != nullptr) {
			char line[maxCharPerLine];
			while (fgets(line, maxCharPerLine, fp)) {
				insert(size(), new node(line));
			}
			fclose(fp);
		}
	}
	void storeFile(const char* fname) {
		FILE* fp = fopen(fname, "w");
		if (fp != nullptr) {
			display(fp);
			fclose(fp);
		}
	}
};