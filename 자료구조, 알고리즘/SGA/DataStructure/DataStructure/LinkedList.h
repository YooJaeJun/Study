#pragma once
#include <iostream>
using namespace std;

typedef int DataType;

struct Node
{
	DataType Data;
	Node* NextNode;
};

Node* Create(DataType data);
void Destroy(Node* node);

void Push(Node** head, Node* node);
void Insert(Node* current, Node* node);
void InsertHead(Node** current, Node* head);

void Remove(Node** head, Node* remove);
Node* GetNode(Node* head, int location);

int GetNodeCount(Node* head);



////////////////////////
// Template LinkedList
//////////////////////// 
/*
template<typename T>
class LinkedList
{
public:
	struct Node
	{
		T Data;
		Node* Next;
	};

public:
	static Node* Create(T data)
	{
		Node* node = new Node();

		node->Data = data;
		node->Next = NULL;

		return node;
	}

	static void Destroy(Node* node)
	{
		delete node;
		node = NULL;
	}

public:
	LinkedList(Node* head)
	{
		this->head = head;
	}

	Node* Head() { return head; }

	void Push(Node* node)
	{
		Node* tail = head;

		while (tail->Next)
			tail = tail->Next;

		tail->Next = node;
	}

	void Insert(Node* current, Node* node)
	{
		node->Next = current->Next;
		current->Next = node;
	}

	void Insert(int index, Node* node)
	{
		Node* current = head;
		current = GetNode(index);
		Insert(current, node);
	}

	Node* GetNode(int index)
	{
		Node* current = head;
		
		while (current && (--index))
			current = current->Next;

		return current;
	}

	int GetNodeCount()
	{
		int count = 0;
		Node* current = head;

		while (current)
		{
			current = current->Next;
			count++;
		}

		return count;
	}

	void Print(Node* node = NULL)
	{
		if (node == NULL)
			return;

		cout << node->Data << endl;

		Print(node->Next);
	}

private:
	Node* head;
};
*/