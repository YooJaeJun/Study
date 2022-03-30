#pragma once
#include <cstdio>
#include <cstring>
const int maxWordSize = 40;
const int maxMeaningSize = 200;

class record {
	char word[maxWordSize];
	char meaning[maxWordSize];
public:
	record(const char* w = "", const char* m = "") {
		set(w, m);
	}
	void set(const char* w, const char* m) {
		strcpy_s(word, w);
		strcpy_s(meaning, m);
	}
	int compare(record* n) { return compare(n->word); }
	int compare(const char* w) { return strcmp(w, word); }
	int compareMeaning(const char* m) { return strcmp(meaning, m); }
	void display() { printf("%12s : %-40s\n", word, meaning); }
	void copy(record* n) { set(n->word, n->meaning); }
};