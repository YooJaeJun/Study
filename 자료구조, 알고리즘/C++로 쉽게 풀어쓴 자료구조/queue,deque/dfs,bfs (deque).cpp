#include <deque>
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

struct vec2i {
	int x_;
	int y_;
	vec2i(int x, int y) : x_(x), y_(y) {}
	const int x() const { return x_; }
	const int y() const { return y_; }
};

bool isNeighbor(int x, int y) {
	return map[x][y] == '0' || map[x][y] == 'e' || map[x][y] == 'x';
}

bool isValid(int x, int y) {
	return x >= 0 && y >= 0 && x < maxSize&& y < maxSize;
}


/// dfs
/*
void main() {
	deque<vec2i> dq;
	dq.push_front({ 1, 0 });
	while (false == dq.empty()) {
		vec2i v = dq.front();
		dq.pop_front();
		int x = v.x();
		int y = v.y();
		printf("(%d,%d) ", x, y);
		if (map[x][y] == 'x') {
			printf("미로 탐색 성공쓰");
			return;
		}
		else {
			map[x][y] = '.';
			if (isNeighbor(x + 1, y) && isValid(x + 1, y)) {
				dq.push_front({ x + 1, y });
			}
			if (isNeighbor(x - 1, y) && isValid(x - 1, y)) {
				dq.push_front({ x - 1, y });
			}
			if (isNeighbor(x, y + 1) && isValid(x, y + 1)) {
				dq.push_front({ x, y + 1 });
			}
			if (isNeighbor(x, y - 1) && isValid(x, y - 1)) {
				dq.push_front({ x, y - 1 });
			}
		}
	}
	printf("미로 탐색 실패");
}
*/

/// bfs
void main() {
	deque<vec2i> dq;
	dq.push_front({ 1,0 });
	while (false == dq.empty()) {
		int x = dq.front().x();
		int y = dq.front().y();
		printf("(%d,%d) ", x, y);
		dq.pop_front();
		if (map[x][y] == 'x') {
			printf("미로 탐색 성공");
			return;
		}
		else {
			map[x][y] = '.';
			if (isNeighbor(x - 1, y) && isValid(x - 1, y)) {
				dq.push_back({ x - 1, y });
			}
			if (isNeighbor(x + 1, y) && isValid(x + 1, y)) {
				dq.push_back({ x + 1, y });
			}
			if (isNeighbor(x, y - 1) && isValid(x, y - 1)) {
				dq.push_back({ x, y - 1 });
			}
			if (isNeighbor(x, y + 1) && isValid(x, y + 1)) {
				dq.push_back({ x, y + 1 });
			}
		}
	}
	printf("미로 탐색 실패");
}