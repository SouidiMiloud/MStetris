#ifndef SHAPE_H
#define SHAPE_H

#include"Board.h"
#include<algorithm>

enum Direction {
	RIGHT,
	LEFT
};

enum ShapeType {
	I_SHAPE,
	O_SHAPE,
	T_SHAPE,
	Z_SHAPE,
	S_SHAPE,
	J_SHAPE,
	L_SHAPE
};

class Shape
{
public:
	Shape(std::vector<CellCoord> cells, Color color, ShapeType type);
	~Shape();

	std::vector<CellCoord> cells;
	Color color;
	static bool stoped;
	static int TIMER_LIMIT;

	void moveDown();
	void rotate();
	void moveHorizontally(Direction direction);
	void drop();
	int getRowOfCellAbove();
	int getRowOfCellBelow();
	static void reset();

private:
	static int timer;
	static const int TIMER_LIMIT_DROP;
	ShapeType type;
	static bool droppingMode;
	static const int DROP_UNITS;
	static int dropUnits;
	static const int centerIndex;

	bool canRotate(std::vector<CellCoord>& newCells, int index);
	bool canMove(std::vector<CellCoord>& newCells);
	bool doesMovedCellBelongToCells(CellCoord& movedCell);
	bool isMovedCellOutOfBoard(CellCoord& movedCell);
};

#endif // !SHAPE_H