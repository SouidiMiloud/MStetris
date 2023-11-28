#include"NextShapeGrid.h"


std::vector<std::vector<Cell*>> NextShapeGrid::cells(4, std::vector<Cell*>(2));
ShapeType NextShapeGrid::shapeType;
Color NextShapeGrid::shapeColor;

std::map<ShapeType, std::vector<CellCoord>> NextShapeGrid::shapeCellsPos = {
	{I_SHAPE, {{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }}},
	{O_SHAPE, {{ 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }}},
	{T_SHAPE, {{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 1, 1 }}},
	{Z_SHAPE, {{ 0, 1 }, { 1, 1 }, { 1, 0 }, { 2, 0 }}},
	{S_SHAPE, {{ 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }}},
	{J_SHAPE, {{ 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 }}},
	{L_SHAPE, {{ 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }}}
};

std::vector<ShapeType> NextShapeGrid::shapeTypes = { I_SHAPE, O_SHAPE, T_SHAPE, Z_SHAPE, S_SHAPE, J_SHAPE, L_SHAPE };
std::vector<Color> NextShapeGrid::colors = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };


void NextShapeGrid::makeGrid() {
	float y = 0.3f;
	for (int i = 0; i < cells.size(); i++) {
		float x = Outline::bottomRightPos.x + 3 * Cell::getSize() / 2;
		y -= Cell::getSize() + Board::MARGIN;
		for (int j = 0; j < cells[i].size(); j++) {
			cells[i][j] = new Cell({ x, y }, Global::WHITE);
			x += Cell::getSize() + Board::MARGIN;
		}
	}
}

void NextShapeGrid::generateNewShape() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> randomShapeColor(0, NextShapeGrid::colors.size() - 1);
	std::uniform_int_distribution<int> randomShapeType(0, NextShapeGrid::shapeTypes.size() - 1);

	shapeColor = colors[randomShapeColor(mt)];
	shapeType = shapeTypes[randomShapeType(mt)];
	placeNewShape();
}

void NextShapeGrid::placeNewShape() {
	clear();
	std::vector<CellCoord> cellsCoords = shapeCellsPos[shapeType];
	for (CellCoord cell : cellsCoords)
		cells[cell.row][cell.col]->setColor(shapeColor);
}

void NextShapeGrid::clear() {
	for (std::vector<Cell*> cells_ : cells) {
		for (Cell* cell : cells_)
			cell->clear();
	}
}

ShapeType NextShapeGrid::getShapeType() {
	return shapeType;
}
Color NextShapeGrid::getColor() {
	return shapeColor;
}

void NextShapeGrid::render() {
	for (std::vector<Cell*> cells_ : cells) {
		for (Cell* cell : cells_) {
			if (cell->isFree()) continue;
			cell->render();
		}
	}
}

void NextShapeGrid::clearResources() {
	for (std::vector<Cell*> row : cells) {
		for (Cell* cell : row) {
			delete(cell);
		}
	}
}