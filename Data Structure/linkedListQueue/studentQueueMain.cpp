#include "studentQueue.h"
void main() {
	studentQueue que;
	que.enqueue(new node(100, "이미희", "컴공"));
	que.enqueue(new node(200, "김예린", "간호"));
	que.enqueue(new node(300, "윾재준", "법학"));
	que.display();
	delete que.dequeue();
	que.display();
}