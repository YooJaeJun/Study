#define _CRT_SECURE_NO_WARNINGS
#include "Turboc.h"
//��� ����ü
struct Node
{
	char name[10];
	char tel[15];
	char addr[32];
	Node *prev;
	Node *next;
};
Node *head;
//���� ����Ʈ �ʱ�ȭ - �Ӹ��� �Ҵ��Ѵ�.
void InitList()
{
	head = (Node*)malloc(sizeof(Node));
	head->prev = NULL;
	head->next = NULL;
}
//������ ����� �����ʿ� �����Ѵ�.
Node *InsertNodeRight(Node *Target, Node *aNode)
{
	Node *New;
	Node *Right;
	New = (Node*)malloc(sizeof(Node));
	*New = *aNode;
	Right = Target->next;
	New->next = Right;
	New->prev = Target;
	Target->next = New;
	if (Right) {
		Right->prev = New;
	}
	return New;
}
//������ ����� ���ʿ� �����Ѵ�.
Node *InsertNodeLeft(Node *Target, Node *aNode)
{
	Node *Left;
	Left = Target->prev;
	if (Left) {
		return InsertNodeRight(Left, aNode);
	}
	return NULL;
}
//���� ���� ��带 �߰��Ѵ�.
void AppendNode(Node *aNode)
{
	Node *tail;
	for (tail = head; tail->next; tail = tail->next) { ; }
	InsertNodeRight(tail, aNode);
}
//�ܼ� ���� ����Ʈ�ʹ� �޸� �ڱ� �ڽ��� ���� �� �ִ�.
BOOL DeleteNode(Node *Target)
{
	Node *Left, *Right;
	//����� ���� �� ����
	if (Target == NULL || Target == head) {
		return FALSE;
	}
	Left = Target->prev;
	Right = Target->next;
	Left->next = Right;
	if (Right) {
		Right->prev = Left;
	}
	free(Target);
	return TRUE;
}
//idx��° ��带 ã�´�.
Node *FindNodeByIndex(int idx)
{
	Node *Now;
	int Index = 0;
	for (Now = head->next; Now; Now = Now->next) {
		if (Index == idx) {
			return Now;
		}
		Index++;
	}
	return NULL;
}
//����� �������� ���Ѵ�.
int GetNodeIndex(Node *Target)
{
	Node *Now;
	int Index = 0;
	for (Now = head->next; Now; Now = Now->next) {
		if (Now == Target) {
			return Index;
		}
		Index++;
	}
	return -1;
}
//����� ������ �����Ѵ�.
int GetListCount()
{
	Node *Now;
	int Count = 0;
	for (Now = head->next; Now; Now = Now->next) {
		Count++;
	}
	return Count;
}
//���� ����Ʈ�� ��� ���� �Ӹ��� �����Ѵ�.
void UnInitList()
{
	while (DeleteNode(head->next)) { ; }
	free(head);
	head = NULL;
}
// �̸����� ��带 ã�´�.
Node *FindNode(Node *Start, Node *aNode)
{
	Node *Now;
	for (Now = Start->next; Now; Now = Now->next) {
		if (strcmp(Now->name, aNode->name) == 0) {
			return Now;
		}
	}
	return Now;
}
void main()
{
	char ch;
	Node *Now;
	Node Temp;
	InitList();
	for (;;) {
		printf("����� �Է��ϼ���(1:����, 2:�߰�, 3:����, Q:����) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q') {
			break;
		}
		switch (ch) {
		case '1':
			if (head->next == NULL) {
				printf("��ϵ� ������ �����ϴ�.\n");
			}
			else {
				Now = head->next;
				do {
					printf("�̸�:%s, ��ȭ:%s, �ּ�:%s\n", Now->name,
						Now->tel, Now->addr);
					Now = Now->next;
				} while (Now);
			}
			break;
		case '2':
			printf("�̸��� �Է��ϼ���(9��) : "); gets_s(Temp.name);
			printf("��ȭ��ȣ�� �Է��ϼ���(14��) : "); gets_s(Temp.tel);
			printf("�ּҸ� �Է��ϼ���(31��) : "); gets_s(Temp.addr);
			AppendNode(&Temp);
			break;
		case '3':
			printf("������ ����� �̸��� �Է��ϼ��� : "); gets_s(Temp.name);
			Now = FindNode(head, &Temp);
			if (Now != NULL) {
				DeleteNode(Now);
			}
			else {
				printf("��ϵ��� ���� ����Դϴ�.\n");
			}
			break;
		}
	}
	UnInitList();
}