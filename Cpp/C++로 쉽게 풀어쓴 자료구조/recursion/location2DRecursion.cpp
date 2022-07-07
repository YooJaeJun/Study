#include <iostream>
#include "location2DRecursion.h"
using namespace std;

const int maxSize = 6;
char map[maxSize][maxSize] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

bool isValidLoc(int r, int c) {
	if (r < 0 || c < 0 || r >= maxSize || c >= maxSize) {
		return false;
	}
	else {
		return map[r][c] == '0' || map[r][c] == 'x';
	}
}

location2D locEntry, locExit;	// �Ա��� �ⱸ ��ġ
bool done = false;	// Ž�� ���� ����

// ��ȯ���� ������ �̷� Ž�� �Լ�
void searchRecur(location2D pt) {
	printf("(%d,%d) ", pt.row, pt.col);
	if (done) { return; }
	if (pt == locExit) {
		done = true;
		return;
	}
	int r = pt.row;
	int c = pt.col;
	map[r][c] = '5';

	// �� ���� �̿��� ���� ��ȯ ȣ��
	if (isValidLoc(r - 1, c)) { searchRecur(location2D(r - 1, c)); }
	if (isValidLoc(r + 1, c)) { searchRecur(location2D(r + 1, c)); }
	if (isValidLoc(r, c - 1)) { searchRecur(location2D(r, c - 1)); }
	if (isValidLoc(r, c + 1)) { searchRecur(location2D(r, c + 1)); }
}

void main() {
	locEntry.set(1, 0);
	locExit.set(4, 5);
	searchRecur(locEntry);
	if (done) { printf("\n ==> �ⱸ�� Ž����.\n"); }
	else { printf("\n ==> �ⱸ�� ã�� ������.\n"); }
}