#include <iostream>
#include "LinkedList.h"
using namespace std;

Node* Create(DataType data)
{
	Node* node = new Node();

	node->Data = data;
	node->NextNode = NULL;

	return node;
}

void Destroy(Node* node)
{
	delete node;
	node = NULL;
}

void Push(Node** head, Node* node)
{
	if ((*head) != NULL)
	{
		Node* tail = (*head);

		while (tail->NextNode != NULL)
			tail = tail->NextNode;

		tail->NextNode = node;
	}
	else
	{
		*head = new Node();
	}
}

void Insert(Node* current, Node* node)
{
	node->NextNode = current->NextNode;
	current->NextNode = node;
}

void InsertHead(Node** current, Node* head)
{
	if (*current == NULL)
	{
		*current = head;
	}
	else
	{
		head->NextNode = *current;
		*current = head;
	}
}

void Remove(Node** head, Node* remove)
{
}

Node* GetNode(Node* head, int location)
{
	return nullptr;
}

int GetNodeCount(Node* head)
{
	return 0;
}




////////////////////////
// Template LinkedList
//////////////////////// 
/*
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
*/