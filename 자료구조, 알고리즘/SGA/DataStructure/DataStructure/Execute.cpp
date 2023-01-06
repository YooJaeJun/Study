#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
	Node* node = NULL;
	for (int i = 0; i < 5; i++)
	{
		Node* temp = Create(i);
		Push(&node, temp);
	}

	Node* newNode = NULL;
	{
		newNode = Create(-1);
		InsertHead(&node, newNode);

		newNode = Create(-2);
		InsertHead(&node, newNode);

		int a = 0;
	}


	return 0;
}