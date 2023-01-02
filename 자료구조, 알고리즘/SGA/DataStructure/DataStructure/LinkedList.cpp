#include <iostream>
#include "LinkedList.h"
using namespace std;

typedef LinkedList<int> List;

int main()
{
	List::Node* node = List::Create(1);

	List* list = new List(node);
	list->Push(List::Create(2));
	list->Push(List::Create(3));
	list->Push(List::Create(4));
	list->Push(List::Create(5));

	list->Print(list->Head());

	cout << '\n';

	list->Insert(4, List::Create(10));

	list->Print(list->Head());

	return 0;
}