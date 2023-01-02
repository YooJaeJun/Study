#include <bits/stdc++.h>
using namespace std;


class Unit
{
	friend class Grid;

public:
	Unit(Grid* grid, double x, double y)
		: grid_(grid), x_(x), y_(y), prev_(nullptr), next_(nullptr)
	{
		grid_->add(this);
	}
	void move(double x, double y)
	{
		grid_->move(this, x, y);
	}

private:
	double x_, y_;
	Grid* grid_;
	Unit* prev_;
	Unit* next_;
};

// 격자
class Grid
{
public:
	Grid()
	{
		// 격자를 싹 지운다.
		for (int x = 0; x < NUM_CELLS; x++)
		{
			for (int y = 0; y < NUM_CELLS; y++)
			{
				cells_[x][y] = nullptr;
			}
		}
	}

	void add(Unit* unit)
	{
		// 어느 칸에 들어갈지를 결정한다.
		int cellX = (int)(unit->x_ / Grid::CELL_SIZE);
		int cellY = (int)(unit->y_ / Grid::CELL_SIZE);

		// 칸에 들어 있는 리스트의 맨 앞에 추가한다.
		unit->prev_ = nullptr;
		unit->next_ = cells_[cellX][cellY];
		cells_[cellX][cellY] = unit;

		if (unit->next_ != nullptr)
		{
			unit->next_->prev_ = unit;
		}
	}

	void handleMelee()
	{
		for (int x = 0; x < NUM_CELLS; x++)
		{
			for (int y = 0; y < NUM_CELLS; y++)
			{
				handleCell(x, y);
			}
		}
	}

	void handleCell(int x, int y)
	{
		Unit* unit = cells_[x][y];
		while (unit != nullptr)
		{
			// 이 칸에 들어있는 다른 유닛을 처리한다.
			handleUnit(unit, unit->next_);

			// 주변 칸에 들어있는 유닛들도 확인한다.
			if (x > 0) handleUnit(unit, cells_[x - 1][y]);
			if (y > 0) handleUnit(unit, cells_[x][y - 1]);
			if (x > 0 && y > 0) handleUnit(unit, cells_[x - 1][y - 1]);
			if (x > 0 && y < NUM_CELLS - 1) handleUnit(unit, cells_[x - 1][y + 1]);

			unit = unit->next_;
		}
	}

	void handleUnit(Unit* unit, Unit* other)
	{
		while (other != nullptr)
		{
			if (distance(unit, other) < ATTACK_DISTANCE)
			{
				handleAttack(unit, other);
			}
			other = other->next_;
		}
	}

	void move(Unit* unit, double x, double y)
	{
		// 유닛이 어느 칸에 있었는지를 확인한다.
		int oldCellX = (int)(unit->x_ / Grid::CELL_SIZE);
		int oldCellY = (int)(unit->y_ / Grid::CELL_SIZE);

		// 유닛이 어느 칸으로 가야 하는지를 확인한다.
		int cellX = (int)(x / Grid::CELL_SIZE);
		int cellY = (int)(y / Grid::CELL_SIZE);

		unit->x_ = x;
		unit->y_ = y;

		// 칸이 바뀌지 않았다면 더 할 일이 없다.
		if (oldCellX == cellX && oldCellY == cellY)
		{
			return;
		}

		// 이전 칸에 들어있는 리스트에서 유닛을 제거한다.
		if (unit->prev_ != nullptr)
		{
			unit->prev_->next_ = unit->next_;
		}
		if (unit->next_ != nullptr)
		{
			unit->next_->prev_ = unit->prev_;
		}

		// 유닛이 칸에 들어있는 리스트의 머리였다면 머리를 바꿔준다.
		if (cells_[oldCellX][oldCellY] == unit)
		{
			cells_[oldCellX][oldCellY] = unit->next_;
		}

		// 새로 들어갈 칸에 추가한다.
		add(unit);
	}

	static const int NUM_CELLS = 10;
	static const int CELL_SIZE = 20;

private:
	Unit* cells_[NUM_CELLS][NUM_CELLS];
};