#ifndef NEXTSHAPEGRID_H
#define NEXTSHAPEGRID_H

#include"Outline.h"
#include"Cell.h"
#include"../Shape.h"
#include<map>
#include<random>


class NextShapeGrid
{
public:
	static void makeGrid();
	static void generateNewShape();
	static void render();
	static void clearResources();
	static ShapeType getShapeType();
	static Color getColor();

private:
	static ShapeType shapeType;
	static Color shapeColor;
	static std::vector<ShapeType> shapeTypes;
	static std::vector<Color> colors;
	static std::map<ShapeType, std::vector<CellCoord>> shapeCellsPos;
	static std::vector<std::vector<Cell*>> cells;
	static void placeNewShape();
	static void clear();
};

#endif // !NEXTSHAPEGRID_H
