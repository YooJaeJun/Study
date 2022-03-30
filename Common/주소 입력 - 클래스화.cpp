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
		printf("%16s => 크기=%02d, 개수=%02d : ", sMark, size, num);
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
		printf("명령을 입력하세요(1:보기, 2:추가, 3:삭제, Q:종료) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q') {
			break;
		}
		switch (ch) {
		case '1':
			if (nc.GetNum() == 0) {
				printf("등록된 내용이 없습니다.\n");
			}
			else {
				for (i = 0; i < nc.GetNum(); i++) {
					printf("%d, 이름:%s, 전화:%s, 주소:%s\n", i, nc.GetNameIdx(i),
						nc.GetTelIdx(i), nc.GetAddrIdx(i));
				}
			}
			break;
		case '2':
			printf("이름을 입력하세요(9자) : "); gets_s(nc.GetName(), 9);
			printf("전화번호를 입력하세요(14자) : "); gets_s(nc.GetTel(), 14);
			printf("주소를 입력하세요(31자) : "); gets_s(nc.GetAddr(), 31);
			nc.Append(nc);
			break;
		case '3':
			printf("삭제할 번호를 입력하세요 : "); scanf_s("%d", &i);
			if (i < nc.GetNum()) {
				nc.Delete(i);
			}
			else {
				printf("등록되지 않은 번호입니다.\n");
			}
			break;
		}
	}
	nc.Clear();

	_CrtDumpMemoryLeaks();
}