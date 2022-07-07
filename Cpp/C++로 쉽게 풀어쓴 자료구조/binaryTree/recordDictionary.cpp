#include "recordDictionary.h"
#include <conio.h>
void help() {
	printf("[����] i-�߰� d-���� w-�ܾ�˻� m-�ǹ̰˻� p-��� q-���� =>");
}

void main() {
	char command;
	char word[80];
	char meaning[200];
	recordDictionary tree;
	do {
		help();
		command = _getche();
		printf("\n");
		switch (command) {
		case 'i': 
			printf(" > ���� �ܾ�: "); gets_s(word);
			printf(" > �ܾ� ����: "); gets_s(meaning);
			tree.insert(new recordBinaryNode(word, meaning));
			break;
		case 'd': printf(" > ���� �ܾ�: "); gets_s(word);
			tree.remove(word);
			break;
		case 'p':
			tree.printAllWords();
			printf("\n");
			break;
		case 'w':
			printf(" > �˻� �ܾ�: "); gets_s(word);
			tree.searchWord(word);
			break;
		case 'm':
			printf(" > �˻� �ǹ�: "); gets_s(word);
			tree.searchMeaning(word);
			break;
		}
	} while (command != 'q');
}