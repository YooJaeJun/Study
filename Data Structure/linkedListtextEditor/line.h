#pragma once
#include <iostream>
//#include <cstring>

const int maxCharPerLine = 1000;
class line {
	char data[maxCharPerLine];
public:
	line(char* line) {
		if (line != nullptr) {
			strcpy_s(data, line);
		}
	}
	void print(FILE* fp = stdout) { fprintf(fp, "%s", data); }
	bool hasData(char* str) { return strcmp(str, data) == 0; }
};