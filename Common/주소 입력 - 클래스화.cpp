#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Turboc.h>

class NameCard
{
private:
	char name[10];
	char tel[15];
	char addr[32];
	unsigned size;
	unsigned num;
	unsigned growby;
	NameCard * ar;

public:

	NameCard() {}
	NameCard(unsigned asize, unsigned agrowby) : size(asize), growby(agrowby), num(0) {
		Init(size);
	}
	void Init(unsigned size) {
		ar = (NameCard*)malloc(size * sizeof(NameCard));
	}
	void Clear() {
		if (ar)
			free(ar);
	}
	void Delete(unsigned idx) {
		for (unsigned i = idx; i != num; i++) {
			ar[i] = ar[i + 1];
		}
		num--;
		size--;
	}
	void Insert(int idx, NameCard value) {
		unsigned need;
		need = num + 1;
		if (need > size) {
			size = need + growby;
			Init(size);
		}
		ar[idx] = value;
		num++;
	}
	void Append(NameCard value) {
		Insert(num, value);
	}
	void DumpArray(char *sMark) {
		printf("%16s => ũ��=%02d, ����=%02d : ", sMark, size, num);
		for (unsigned i = 0; i < num; i++) {
			printf("%2d ", ar[i]);
		}
		printf("\n");
	}
	char* GetNameIdx(int idx) {
		return ar[idx].name;
	}
	char* GetTelIdx(int idx) {
		return ar[idx].tel;
	}
	char* GetAddrIdx(int idx) {
		return ar[idx].addr;
	}
	unsigned GetNum() {
		return num;
	}
	unsigned GetSize() {
		return size;
	}
	unsigned GetGrowby() {
		return growby;
	}
	NameCard GetArIdx(int idx) {
		return ar[idx];
	}
	char* GetName() {
		return name;
	}
	char* GetTel() {
		return tel;
	}
	char* GetAddr() {
		return addr;
	}
};

void main()
{
	char ch;
	unsigned i;
	NameCard nc(10, 5);
	for (;;) {
		printf("����� �Է��ϼ���(1:����, 2:�߰�, 3:����, Q:����) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q') {
			break;
		}
		switch (ch) {
		case '1':
			if (nc.GetNum() == 0) {
				printf("��ϵ� ������ �����ϴ�.\n");
			}
			else {
				for (i = 0; i < nc.GetNum(); i++) {
					printf("%d, �̸�:%s, ��ȭ:%s, �ּ�:%s\n", i, nc.GetNameIdx(i),
						nc.GetTelIdx(i), nc.GetAddrIdx(i));
				}
			}
			break;
		case '2':
			printf("�̸��� �Է��ϼ���(9��) : "); gets_s(nc.GetName(), 9);
			printf("��ȭ��ȣ�� �Է��ϼ���(14��) : "); gets_s(nc.GetTel(), 14);
			printf("�ּҸ� �Է��ϼ���(31��) : "); gets_s(nc.GetAddr(), 31);
			nc.Append(nc);
			break;
		case '3':
			printf("������ ��ȣ�� �Է��ϼ��� : "); scanf_s("%d", &i);
			if (i < nc.GetNum()) {
				nc.Delete(i);
			}
			else {
				printf("��ϵ��� ���� ��ȣ�Դϴ�.\n");
			}
			break;
		}
	}
	nc.Clear();

	_CrtDumpMemoryLeaks();
}