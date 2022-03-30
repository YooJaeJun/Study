#include "lineEditor.h"

void usage() {
	printf("[�޴�����] i-�Է�, d-����, r-����, p-���, l-�����б�, s-����, q-����=> ");
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