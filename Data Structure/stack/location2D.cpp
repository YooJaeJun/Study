#include <iostream>
#include <stack>
#include <vector>
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

struct coord {
	int x_;
	int y_;
	coord(int x, int y) : x_(x), y_(y) {}
	const int x() const { return x_; }
	const int y() const { return y_; }
};

bool isNeighbor(int x, int y) {
	return map[x][y] == '0' || map[x][y] == 'e' || map[x][y] == 'x';
}

bool isValid(int x, int y) {
	return x >= 0 && y >= 0 && x < maxSize && y < maxSize;
}

void main() {
	stack<coord> st;
	st.push(coord(1, 0));

	while (!st.empty()) {
		int x = st.top().x();
		int y = st.top().y();
		st.pop();
		if (map[x][y] == 'x') {
			printf("(%d,%d)\n", x, y);
			printf("미로 탐색 끗");
			return;
		}
		else if (map[x][y] == '0' || map[x][y] == 'e') {
			printf("(%d,%d)\n", x, y);
			map[x][y] = 'c';	//check 처리
			if (isValid(x, y + 1) && isNeighbor(x, y + 1)) {
				st.push(coord(x, y + 1));
			}
			if (isValid(x, y - 1) && isNeighbor(x, y - 1)) {
				st.push(coord(x, y - 1));
			}
			if (isValid(x + 1, y) && isNeighbor(x + 1, y)) {
				st.push(coord(x + 1, y));
			}
			if (isValid(x - 1, y) && isNeighbor(x - 1, y)) {
				st.push(coord(x - 1, y));
			}
		}
	}
	printf("미로 탐색 실패");
}






/// 답지
/*
#include <iostream>
#include <stack>
#include "location2D.h"
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
// (r,c)가 갈 수 있는 위치인지를 검사하는 함수
// (r,c)가 배열 안에 있고, 값이 갈 수 있는 위치 '0'이거나 출구 'x'이어야 함.
bool isValidLoc(int r, int c) {
	if (r < 0 || c < 0 || r >= maxSize || c >= maxSize) {
		return false;
	}
	else {
		return map[r][c] == '0' || map[r][c] == 'x';
	}
}

void main() {
	stack<location2D> locStack;
	location2D entry(1, 0);
	locStack.push(entry);

	while (locStack.empty() == false) {
		location2D here = locStack.top();
		locStack.pop();

		int r = here.row;
		int c = here.col;
		printf("(%d,%d) ", r, c);
		if (map[r][c] == 'x') {
			printf(" 미로 탐색 성공\n");
			return;
		}
		else {
			map[r][c] = '.';	//현재 위치 지나옴 처리.
			if (isValidLoc(r - 1, c)) { locStack.push(location2D(r - 1, c)); }
			if (isValidLoc(r + 1, c)) { locStack.push(location2D(r + 1, c)); }
			if (isValidLoc(r, c - 1)) { locStack.push(location2D(r, c - 1)); }
			if (isValidLoc(r, c + 1)) { locStack.push(location2D(r, c + 1)); }
		}
	}
	printf("미로 탐색 실패!\n");
}
*/