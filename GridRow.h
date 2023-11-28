#ifndef GRIDROW_H
#define GRIDROW_H

#include"Board.h"

class GridRow
{
public:
	GridRow(float y);
	~GridRow();

	bool isFull();
	bool isEmpty();
	void addElement();
	void removeElement();
	void affectRow(GridRow* row);
	void clear();
	void destroy();
	void updateCellColor(int index, Color& color);
	bool isCellFree(int index);

	void makeRow(float y);
	void render();

private:
	static const int MAX_ELEMENTS;
	int occupiedCells;

	std::vector<Cell*> cells;
};

#endif // !GRIDROW_H
