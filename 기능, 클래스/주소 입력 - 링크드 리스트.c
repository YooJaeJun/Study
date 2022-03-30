#define _CRT_SECURE_NO_WARNINGS
#include "Turboc.h"
//노드 구조체
struct Node
{
	char name[10];
	char tel[15];
	char addr[32];
	Node *prev;
	Node *next;
};
Node *head;
//연결 리스트 초기화 - 머리를 할당한다.
void InitList()
{
	head = (Node*)malloc(sizeof(Node));
	head->prev = NULL;
	head->next = NULL;
}
//지정한 노드의 오른쪽에 삽입한다.
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
//지정한 노드의 왼쪽에 삽입한다.
Node *InsertNodeLeft(Node *Target, Node *aNode)
{
	Node *Left;
	Left = Target->prev;
	if (Left) {
		return InsertNodeRight(Left, aNode);
	}
	return NULL;
}
//제일 끝에 노드를 추가한다.
void AppendNode(Node *aNode)
{
	Node *tail;
	for (tail = head; tail->next; tail = tail->next) { ; }
	InsertNodeRight(tail, aNode);
}
//단순 연결 리스트와는 달리 자기 자신을 지울 수 있다.
BOOL DeleteNode(Node *Target)
{
	Node *Left, *Right;
	//헤더는 지울 수 없음
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
//idx번째 노드를 찾는다.
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
//노드의 순서값을 구한다.
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
//노드의 개수를 조사한다.
int GetListCount()
{
	Node *Now;
	int Count = 0;
	for (Now = head->next; Now; Now = Now->next) {
		Count++;
	}
	return Count;
}
//연결 리스트의 모든 노드와 머리를 해제한다.
void UnInitList()
{
	while (DeleteNode(head->next)) { ; }
	free(head);
	head = NULL;
}
// 이름으로 노드를 찾는다.
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
		printf("명령을 입력하세요(1:보기, 2:추가, 3:삭제, Q:종료) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q') {
			break;
		}
		switch (ch) {
		case '1':
			if (head->next == NULL) {
				printf("등록된 내용이 없습니다.\n");
			}
			else {
				Now = head->next;
				do {
					printf("이름:%s, 전화:%s, 주소:%s\n", Now->name,
						Now->tel, Now->addr);
					Now = Now->next;
				} while (Now);
			}
			break;
		case '2':
			printf("이름을 입력하세요(9자) : "); gets_s(Temp.name);
			printf("전화번호를 입력하세요(14자) : "); gets_s(Temp.tel);
			printf("주소를 입력하세요(31자) : "); gets_s(Temp.addr);
			AppendNode(&Temp);
			break;
		case '3':
			printf("삭제할 사람의 이름을 입력하세요 : "); gets_s(Temp.name);
			Now = FindNode(head, &Temp);
			if (Now != NULL) {
				DeleteNode(Now);
			}
			else {
				printf("등록되지 않은 사람입니다.\n");
			}
			break;
		}
	}
	UnInitList();
}