#pragma once

struct location2D {
	int row;
	int col;
	location2D(int r = 0, int c = 0) {
		row = r;
		col = c;
	}
	bool isNeighbor(location2D& p) {
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1)));
	}
};