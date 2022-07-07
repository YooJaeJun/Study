#include "binaryTree.h"
/*
void main() {
	binaryTree tree;
	binaryNode* d = new binaryNode('D', nullptr, nullptr);
	binaryNode* e = new binaryNode('E', nullptr, nullptr);
	binaryNode* b = new binaryNode('B', d, e);
	binaryNode* f = new binaryNode('F', nullptr, nullptr);
	binaryNode* c = new binaryNode('C', f, nullptr);
	binaryNode* a = new binaryNode('A', b, c);
	tree.setRoot(a);

	tree.inorder();
	tree.preorder();
	tree.postorder();
	tree.levelorder();
	printf("\n");

	printf("����� ���� = %d\n", tree.getCount());
	printf("�ܸ��� ���� = %d\n", tree.getLeafCount());
	printf("Ʈ���� ���� = %d\n", tree.getHeight());

	
	binaryTree tree2;
	//		+
	//	*		-
	//3   2   5   6
	binaryNode* n1 = new binaryNode(3, nullptr, nullptr);
	binaryNode* n2 = new binaryNode(2, nullptr, nullptr);
	binaryNode* n3 = new binaryNode('*', n1, n2);
	binaryNode* n4 = new binaryNode(5, nullptr, nullptr);
	binaryNode* n5 = new binaryNode(6, nullptr, nullptr);
	binaryNode* n6 = new binaryNode('-', n4, n5);
	binaryNode* n7 = new binaryNode('+', n3, n6);
	tree2.setRoot(n7);
	printf("��� ��� = %d\n", tree2.evaluate());


	binaryTree tree3;
	binaryNode* m4 = new binaryNode(200, nullptr, nullptr);
	binaryNode* m5 = new binaryNode(500, nullptr, nullptr);
	binaryNode* m3 = new binaryNode(100, m4, m5);
	binaryNode* m2 = new binaryNode(50, nullptr, nullptr);
	binaryNode* m1 = new binaryNode(0, m2, m3);
	tree3.setRoot(m1);
	printf("���͸� �뷮 ��� ��� = %d KB\n", tree3.calcSize());
}
*/