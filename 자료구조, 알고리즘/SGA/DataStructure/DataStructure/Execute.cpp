#include <iostream>
#include "DLinkedList.h"
using namespace std;

int main()
{
	Node* node = NULL;
	for (int i = 0; i < 5; i++)
	{
		Node* temp = Create(i);
		Push(&node, temp);
	}
	

}