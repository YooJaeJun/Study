#include "arrayList.h"

void main() {
	arrayList list;
	list.insert(0, 10);
	list.insert(0, 20);
	list.insert(1, 30);
	list.insert(list.size(), 40);
	list.insert(2, 50);
	list.display();

	list.remove(2);
	list.remove(list.size() - 1);
	list.remove(0);
	list.replace(1, 90);
	list.display();

	list.clear();
	list.display();
}