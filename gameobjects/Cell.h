#ifndef CELL_H
#define CELL_H


#include"../Global.h"
#include"GameObject.h"

struct CellCoord
{
	int row;
	int col;

	bool operator==(CellCoord& cell) {
		return row == cell.row && col == cell.col;
	}
};

class Cell : public GameObject
{
public:
	Cell(Position center, Color color);
	~Cell();

	void render();
	void setColor(Color color);
	Color getColor();
	void clear();
	static float getSize();
	static void setSize(float size);
	bool isFree();

private:
	static float size;
	Color color;

	void makeCell(Position center);
};

#endif // !CELL_H
