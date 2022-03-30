#include <stdlib.h>
#include <crtdbg.h>
#include <Turboc.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define _CRTDBG_MAP_ALLOC
using namespace std;

class NameCard
{
protected:
	char name_[10];
	char tel_[15];
	char addr_[32];

public:
	NameCard() {}
	NameCard(char * name, char * tel, char * addr) {
		myStrInit(name, tel, addr);
	}

	char* GetName() {
		return name_;
	}
	char* GetTel() {
		return tel_;
	}
	char* GetAddr() {
		return addr_;
	}
	void myStrInit(char * name, char * tel, char * addr) {

		size_t len_name = strlen(name);
		size_t len_tel = strlen(tel);
		size_t len_addr = strlen(addr);

		for (size_t i = 0; i != len_name; i++) {
			name_[i] = name[i];
		}
		for (size_t i = 0; i != len_tel; i++) {
			tel_[i] = tel[i];
		}
		for (size_t i = 0; i != len_addr; i++) {
			addr_[i] = addr[i];
		}
	}
};

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char ch;
	unsigned i;
	char name[10];
	char tel[15];
	char addr[32];
	vector<NameCard> nc;
	auto it = nc.begin();
	for (;;) {
		printf("����� �Է��ϼ���(1:����, 2:�߰�, 3:����, Q:����) > ");
		ch = _getch();
		printf("\n");
		if (ch == 'Q' || ch == 'q') {
			break;
		}
		switch (ch) {
		case '1':
			if (nc.size() == 0) {
				printf("��ϵ� ������ �����ϴ�.\n");
			}
			else {
				for (i = 0, it = nc.begin(); it != nc.end(); i++, it++) {
					printf("%d, �̸�:%s, ��ȭ:%s, �ּ�:%s\n", i, (*it).GetName(),
						(*it).GetTel(), (*it).GetAddr());
				}
			}
			break;
		case '2':
			printf("�̸��� �Է��ϼ���(9��) : "); gets_s(name);
			printf("��ȭ��ȣ�� �Է��ϼ���(14��) : "); gets_s(tel);
			printf("�ּҸ� �Է��ϼ���(31��) : "); gets_s(addr);
			nc.push_back(NameCard(name, tel, addr));
			break;
		case '3':
			printf("������ ��ȣ�� �Է��ϼ��� : "); scanf_s("%d", &i);
			if (i < nc.size()) {
				it = nc.begin() + i;
				nc.erase(it);
			}
			else {
				printf("��ϵ��� ���� ��ȣ�Դϴ�.\n");
			}
			break;
		}
	}
}