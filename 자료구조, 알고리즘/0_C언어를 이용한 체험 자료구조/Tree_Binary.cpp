#include <iostream>
#include <string>
#include <queue>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node* left;
	Node* right;

public:
	Node() : data(0), left(nullptr), right(nullptr)
	{}

	Node(T e) : data(e), left(nullptr), right(nullptr)
	{}

	Node(T e, Node* left, Node* right) :
		data(e), left(left), right(right)
	{}

	void dispose()
	{
		if (this == nullptr) return;
		left->dispose();
		right->dispose();
		delete this;
	}

	void inOrder()
	{
		if (this == nullptr) return;
		left->inOrder();
		cout << data << ' ';
		right->inOrder();
	}

	void preOrder()
	{
		if (this == nullptr) return;
		cout << data << ' ';
		left->preOrder();
		right->preOrder();
	}

	void postOrder()
	{
		if (this == nullptr) return;
		left->postOrder();
		right->postOrder();
		cout << data << ' ';
	}

	void levelOrder()
	{
		queue<T> q;
		Node<T> n;

		q.push(data);
		while (false == q.empty())
		{
			n = q.front();
			q.pop();
			cout << n.data << ' ';
			if (n.left) q.push(n.left->data);
			if (n.right) q.push(n.right->data);
		}
	}

	void printGraphViz()
	{
		if (this == nullptr) return;
		
		if (left != nullptr) cout << '\t' << data << " => " << left->data << '\n';
		left->printGraphViz();

		if (right != nullptr) cout << '\t' << data << " => " << right->data << '\n';
		right->printGraphViz();
	}

	Node* insertLeft(int value)
	{
		left = new Node<T>(value);
		return left;
	}

	Node* insertRight(int value)
	{
		right = new Node<T>(value);
		return right;
	}

	int noOfNodes()
	{
		if (this == nullptr) return 0;
		else return left->noOfNodes() + right->noOfNodes() + 1;
	}

	int noOfLeafNode()
	{
		if (this == nullptr) return 0;
		else if(left == nullptr && right == nullptr) return 1;
		else return left->noOfLeafNode() + right->noOfLeafNode();
	}

	int noOfInternalNodes()
	{
		if (this == nullptr) return 0;
		else if (left == nullptr && right == nullptr) return 0;
		else if (left != nullptr && right != nullptr) return left->noOfInternalNodes() + right->noOfInternalNodes() + 1;
	}

	int height()
	{
		if (this == nullptr) return 0;
		else return 1 + max(left->height(), right->height());
	}
};

/*
void main()
{
	Node<int> n1(2);
	Node<int> n2(3);
	Node<int> n3(1, &n1, &n2);

	Node<int>* root = &n3;

	cout << root->data << ' ';
	cout << root->left->data << ' ';
	cout << root->right->data << '\n';
	root->printGraphViz();

	
	root = new Node<int>(1);
	root->left = new Node<int>(2);
	root->right = new Node<int>(3);

	Node<int>* t = root->left;
	t->left = new Node<int>(4);
	t->right = new Node<int>(5);

	t = root->right;
	t->left = new Node<int>(6);
	t->right = new Node<int>(7);

	root->inOrder();
	cout << '\n';
	root->printGraphViz();
	root->dispose();


	root = nullptr;
	root = new Node<int>(1);
	root->insertLeft(2);
	root->insertRight(3);

	t = nullptr;
	t = root->left;
	t->insertLeft(4);
	t->insertRight(5);

	t = root->right;
	t->insertLeft(6);
	t->insertRight(7);

	root->inOrder();
	cout << '\n';
	root->printGraphViz();
	root->dispose();
}
*/

/*
void main()
{
	Node<int> n1(20);
	Node<int> n2(30);
	Node<int> n3(10, &n1, &n2);

	Node<int>* root = &n3;

	Node<int> n4(40);
	Node<int> n5(50);

	n1.left = &n4;
	n1.right = &n5;

	root->inOrder(); cout << '\n';
	root->preOrder(); cout << '\n';
	root->postOrder(); cout << '\n';
	root->levelOrder(); cout << '\n';

	root->printGraphViz();
}
*/

int main()
{
	Node<int> n1(20);
	Node<int> n2(30);
	Node<int> n3(10, &n1, &n2);

	Node<int>* root = &n3;

	Node<int> n4(40);
	Node<int> n5(50);

	n1.left = &n4;
	n1.right = &n5;

	cout << "No of Nodes: " << root->noOfNodes() << '\n';
	cout << "No of Internal Nodes: " << root->noOfInternalNodes() << '\n';
	cout << "No of Leaf Nodes: " << root->noOfLeafNode() << '\n';
	cout << "Height of Trees: " << root->height() << '\n';
}