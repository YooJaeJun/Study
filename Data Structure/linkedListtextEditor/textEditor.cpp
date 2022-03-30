#include "lineEditor.h"

void usage() {
	printf("[메뉴선택] i-입력, d-삭제, r-변경, p-출력, l-파일읽기, s-저장, q-종료=> ");
}
void main() {
	char command;
	lineEditor editor;
	do {
		usage();
		command = getchar();
		switch (command) {
		case 'd': editor.deleteLine();	break;
		case 'i': editor.insertLine();	break;
		case 'r': editor.replaceLine();	break;
		case 'l': editor.loadFile("Test.txt");	break;
		case 's': editor.storeFile("Test.txt");	break;
		case 'p': editor.display();	break;
		case 'q': break;
		}
		fflush(stdin);
	} while (command != 'q');
}