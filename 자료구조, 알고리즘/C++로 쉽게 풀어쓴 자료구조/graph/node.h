#pragma once
#include <cstdio>
class node {
protected:
	int id;		// ������ id
	node* link;	// ���� ����� ������
public:
	node(int i, node* l = nullptr)
		: id(i), link(l) {}
	~node() {
		if (link != nullptr) { delete link; }
	}
	int getId() { return id; }
	node* getLink() { return link; }
	void setLink(node* l) { link = l; }
};