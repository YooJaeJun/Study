#include "studentQueue.h"
void main() {
	studentQueue que;
	que.enqueue(new node(100, "�̹���", "�İ�"));
	que.enqueue(new node(200, "�迹��", "��ȣ"));
	que.enqueue(new node(300, "������", "����"));
	que.display();
	delete que.dequeue();
	que.display();
}