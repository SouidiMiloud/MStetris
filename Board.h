#ifndef BOARD_H
#define BOARD_H


#include"gameobjects/Cell.h"
#include"assets/Shader.h"
#include<map>


class Shape;
class Player;
class Outline;
class GridRow;
enum ShapeType;

class Board
{
public:
	Board();
	~Board();

	static const float MARGIN;
	static const int HORIZ_CELLS;
	static const int VERT_CELLS;

	static std::vector<GridRow*> rows;

	static bool isCellFree(CellCoord cell);
	static void updateColor(std::vector<CellCoord>& cells, Color color);
	static void updateRowsContents(Shape* shape);
	static void checkCompletedRows(Shape* shape);
	Shape* generateNewShape(ShapeType type, Color color);
	void render();
	static void clear();

private:
	static Color nextColor;
	static std::map<ShapeType, std::vector<CellCoord>> shapeCellsPos;

	static bool isFailed(Shape* shape);
	static void destroyRow(int row);

	static void makeBoard();
};

#endif // !BOARD_H