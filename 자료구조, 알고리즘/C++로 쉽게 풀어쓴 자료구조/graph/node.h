#pragma once
#include <cstdio>
class node {
protected:
	int id;		// 정점의 id
	node* link;	// 다음 노드의 포인터
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