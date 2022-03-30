#pragma once
#include "student.h"
using namespace std;


inline void error(const char* s) {
	printf("%s", s);
	exit(1);
}

class node : public student {
	node* link;
public:
	node(int id, const char* name, const char* dept)
		: student(id, name, dept) {
		link = nullptr;
	}
	~node() {}
	node* getLink() { return link; }
	void setLink(node* p) { link = p; }
};
