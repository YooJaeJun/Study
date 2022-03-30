#include <queue>
using namespace std;

/*
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


void main() {
	queue<vec2i> q;
	q.push({ 1, 0 });
	while (false == q.empty()) {
		vec2i v = q.front();
		q.pop();
		int x = v.x();
		int y = v.y();
		printf("(%d,%d) ", x, y);
		if (map[x][y] == 'x') {
			printf("¹Ì·Î Å½»ö ²ý");
			return;
		}
		else {
			map[x][y] = '.';
			if (isNeighbor(x + 1, y) && isValid(x + 1, y)) {
				q.push({ x + 1, y });
			}
			if (isNeighbor(x - 1, y) && isValid(x - 1, y)) {
				q.push({ x - 1, y });
			}
			if (isNeighbor(x, y + 1) && isValid(x, y + 1)) {
				q.push({ x, y + 1 });
			}
			if (isNeighbor(x, y - 1) && isValid(x, y - 1)) {
				q.push({ x, y - 1 });
			}
		}
	}
	printf("¹Ì·Î Å½»ö ½ÇÆÐ");
}
*/