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

	//void dispose()
	//{
	//	if (this == nullptr) return;
	//	left->dispose();
	//	right->dispose();
	//	delete this;
	//}

	//void inOrder()
	//{
	//	if (this == nullptr) return;
	//	left->inOrder();
	//	cout << data << ' ';
	//	right->inOrder();
	//}

	//void preOrder()
	//{
	//	if (this == nullptr) return;
	//	cout << data << ' ';
	//	left->preOrder();
	//	right->preOrder();
	//}

	//void postOrder()
	//{
	//	if (this == nullptr) return;
	//	left->postOrder();
	//	right->postOrder();
	//	cout << data << ' ';
	//}

	//void levelOrder()
	//{
	//	queue<T> q;
	//	Node<T> n;

	//	q.push(data);
	//	while (false == q.empty())
	//	{
	//		n = q.front();
	//		q.pop();
	//		cout << n.data << ' ';
	//		if (n.left) q.push(n.left->data);
	//		if (n.right) q.push(n.right->data);
	//	}
	//}

	//void printGraphViz()
	//{
	//	if (this == nullptr) return;

	//	if (left != nullptr) cout << '\t' << data << " => " << left->data << '\n';
	//	left->printGraphViz();

	//	if (right != nullptr) cout << '\t' << data << " => " << right->data << '\n';
	//	right->printGraphViz();
	//}

	//Node* insertLeft(int value)
	//{
	//	left = new Node<T>(value);
	//	return left;
	//}

	//Node* insertRight(int value)
	//{
	//	right = new Node<T>(value);
	//	return right;
	//}

	//int noOfNodes()
	//{
	//	if (this == nullptr) return 0;
	//	else return left->noOfNodes() + right->noOfNodes() + 1;
	//}

	//int noOfLeafNode()
	//{
	//	if (this == nullptr) return 0;
	//	else if (left == nullptr && right == nullptr) return 1;
	//	else return left->noOfLeafNode() + right->noOfLeafNode();
	//}

	//int noOfInternalNodes()
	//{
	//	if (this == nullptr) return 0;
	//	else if (left == nullptr && right == nullptr) return 0;
	//	else if (left != nullptr && right != nullptr) return left->noOfInternalNodes() + right->noOfInternalNodes() + 1;
	//}

	//int height()
	//{
	//	if (this == nullptr) return 0;
	//	else return 1 + max(left->height(), right->height());
	//}


	// this가 nullptr일 때 클래스 안에서 this를 생성할 수 없어 결국 인자로 받음

	Node* BST_recursiveSearch(Node* root, T e)
	{
		if (root == nullptr) return nullptr;	// leaf 노드에서 하위 노드가 없는 경우
		if (e == root->data) return this;
		else if (e < root->data) return this->BST_recursiveSearch(root->left, e);
		else return this->BST_recursiveSearch(root->right, e);
	}

	Node* BST_iterativeSearch(Node* root, T e)
	{
		while (root)
		{
			if (e == root->data) return root;
			else if (e < root->data) root = root->left;
			else root = root->right;
		}
		return nullptr;
	}

	Node* BST_recursiveInsert(Node* root, T e)
	{
		if (root == nullptr)
		{
			root = new Node(e);
		}
		else if (e < root->data)
		{
			root->left = this->BST_recursiveInsert(root->left, e);
		}
		else
		{
			root->right = this->BST_recursiveInsert(root->right, e);
		}
		return root;
	}

	Node* BST_findMin(Node* node)		// 오른쪽 서브 트리의 가장 작은 값
	{
		if (node == nullptr) return nullptr;

		if (node->left) this->BST_findMin(node->left);
		else return node;
	}

	Node* BST_findMax(Node* node)
	{
		if (this == nullptr) return nullptr;

		if (node->right) this->BST_findMax(node->right);
		else return node;
	}

	Node* BST_recursiveDelete(Node* root, T e)
	{
		if (root == nullptr) return this;
		else if (e == root->data)
		{
			Node* temp;
			if (root->left && root->right)	// 자식 노드 2개
			{
				temp = this->BST_findMin(root->right);	// 오른쪽 서브 트리의 가장 작은 노드를 옮긴다.
				root->data = temp->data;
				root->right = this->BST_recursiveDelete(root->right, temp->data);
			}
			else  // 자식 노드가 1개거나 0개
			{
				temp = root;
				if (root->left == nullptr)
				{
					root = root->right;
				}
				else if (root->right == nullptr)
				{
					root = root->left;
				}
				free(temp);
			}
		}
		else if (e < root->data)
		{
			root->left = this->BST_recursiveDelete(root->left, e);
		}
		else if (e > root->data)
		{
			root->right = this->BST_recursiveDelete(root->right, e);
		}

		return root;
	}

	void printGraphViz(Node* node)
	{
		if (node == nullptr) return;

		if (node->left != nullptr) cout << '\t' << node->data << " => " << node->left->data << '\n';
		this->printGraphViz(node->left);

		if (node->right != nullptr) cout << '\t' << node->data << " => " << node->right->data << '\n';
		this->printGraphViz(node->right);
	}	
	
	void dispose(Node* node)
	{
		if (node == nullptr) return;
		this->dispose(node->left);
		this->dispose(node->right);
		delete node;
	}
};

int main()
{
	Node<int>* bst = nullptr;

	bst = bst->BST_recursiveInsert(bst, 31);
	bst->BST_recursiveInsert(bst, 16);
	bst->BST_recursiveInsert(bst, 45);
	bst->printGraphViz(bst);
	cout << '\n';

	bst->BST_recursiveInsert(bst, 24);
	bst->BST_recursiveInsert(bst, 7);
	bst->printGraphViz(bst);
	cout << '\n';

	bst->BST_recursiveInsert(bst, 19);
	bst->BST_recursiveInsert(bst, 29);
	bst->printGraphViz(bst);
	cout << '\n';

	// 트리에서 항목 삭제
	bst = bst->BST_recursiveDelete(bst, 7);
	bst->printGraphViz(bst);
	cout << '\n';

	bst = bst->BST_recursiveDelete(bst, 16);
	bst->printGraphViz(bst);
	cout << '\n';

	bst = bst->BST_recursiveDelete(bst, 24);
	bst->printGraphViz(bst);
	cout << '\n';

	bst = bst->BST_recursiveDelete(bst, 31);
	bst->printGraphViz(bst);
	cout << '\n';

	bst->dispose(bst);
	bst = nullptr;
}