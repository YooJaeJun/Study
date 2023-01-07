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

	// Print
	{
		Node* current = GetNode(node, 2);
		newNode = Create(1000);

		Insert(current, newNode);

		int count = GetNodeCount(node);
		for (int i = 0; i < count; i++)
		{
			Node* current2 = GetNode(node, i);
			cout << "List[" << i << "] : " << current2->Data << endl;
		}
		cout << "-----------------------------------" << endl << endl;
	}

	// Remove
	{
		Node* remove = GetNode(node, 3);
		Remove(&node, remove);

		int count = GetNodeCount(node);
		for (int i = 0; i < count; i++)
		{
			Node* current2 = GetNode(node, i);
			cout << "List[" << i << "] : " << current2->Data << endl;
		}
		cout << "-----------------------------------" << endl << endl;
	}

	// Remove All
	{
		int count = GetNodeCount(node);

		for (int i = 0; i < count; i++)
		{
			Node* current = GetNode(node, 0);

			if (current)
			{
				Remove(&node, current);
				Destroy(current);
			}
		}

		for (int i = 0; i < count; i++)
		{
			Node* current2 = GetNode(node, i);
			if (current2)
			{
				cout << "List[" << i << "] : ";
				cout << current2->Data << endl;
			}
		}
		cout << "-----------------------------------" << endl << endl;
	}


	return 0;
}