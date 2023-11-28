#include"Shape.h"


int Shape::timer = 0;
int Shape::TIMER_LIMIT = 25;
const int Shape::TIMER_LIMIT_DROP = 1;
const int Shape::DROP_UNITS = 3;
const int Shape::centerIndex = 1;
int Shape::dropUnits = 0;
bool Shape::stoped;
bool Shape::droppingMode;


void Shape::reset() {
	timer = 0;
	TIMER_LIMIT = 25;
	dropUnits = 0;
	stoped = false;
	droppingMode = false;
}

Shape::Shape(std::vector<CellCoord> cells, Color color, ShapeType type){
	stoped = false;
	droppingMode = false;
	this->cells = cells;
	this->color = color;
	this->type = type;
}

Shape::~Shape(){
	
}

void Shape::moveDown() {
	if (timer++ < (droppingMode ? TIMER_LIMIT_DROP : TIMER_LIMIT))
		return;
	std::vector<CellCoord> newCells = cells;
	for (int i = 0; i < cells.size(); i++)
		newCells[i].row++;
	if (!canMove(newCells)) {
		Board::checkCompletedRows(this);
		stoped = true;
		return;
	}
	Board::updateColor(cells, Global::WHITE);
	cells = newCells;
	Board::updateColor(cells, color);
	if (droppingMode && ++dropUnits > DROP_UNITS) 
		droppingMode = false;
	timer = 0;
}

void Shape::rotate() {
	if (type == O_SHAPE)
		return;
	std::vector<CellCoord> tmpCells(cells.size());
	for (int i = 0; i < cells.size(); i++) {
		if (!canRotate(tmpCells, i))
			return;
	}
	Board::updateColor(cells, Global::WHITE);
	cells = tmpCells;
	Board::updateColor(cells, color);
}

void Shape::drop() {
	droppingMode = true;
	dropUnits = 0;
}

void Shape::moveHorizontally(Direction direction) {
	int step = (direction == RIGHT ? 1 : -1);
	std::vector<CellCoord> newCells = cells;
	for (int i = 0; i < cells.size(); i++)
		newCells[i].col += step;
	if (!canMove(newCells))
		return;
	Board::updateColor(cells, Global::WHITE);
	cells = newCells;
	Board::updateColor(cells, color);
}

bool Shape::canMove(std::vector<CellCoord>& newCells) {
	for (int i = 0; i < newCells.size(); i++) {
		if (isMovedCellOutOfBoard(newCells[i]))
			return false;
		if (newCells[i].row < 0) continue;
		if(!Board::isCellFree(newCells[i])){
			if (!doesMovedCellBelongToCells(newCells[i]))
				return false;
		}
	}
	return true;
}

bool Shape::doesMovedCellBelongToCells(CellCoord& movedCell) {
	for (CellCoord& cell : cells) {
		if (movedCell == cell)
			return true;
	}
	return false;
}

bool Shape::isMovedCellOutOfBoard(CellCoord& movedCell) {
	return (movedCell.row >= Board::VERT_CELLS
		|| movedCell.col >= Board::HORIZ_CELLS
		|| movedCell.col < 0
	);
}

bool Shape::canRotate(std::vector<CellCoord>& newCells, int index) {
	int rowDiff = cells[index].row - cells[centerIndex].row;
	int colDiff = cells[index].col - cells[centerIndex].col;
	newCells[index].row = cells[centerIndex].row + colDiff;
	newCells[index].col = cells[centerIndex].col - rowDiff;

	if (isMovedCellOutOfBoard(newCells[index]))
		return false;
	if (newCells[index].row < 0) return true;
	if(!Board::isCellFree(newCells[index]))
		return doesMovedCellBelongToCells(newCells[index]);
	return true;
}

int Shape::getRowOfCellAbove() {
	int upperRow = cells[0].row;
	for (CellCoord cell : cells) {
		if (cell.row < upperRow)
			upperRow = cell.row;
	}
	return upperRow;
}

int Shape::getRowOfCellBelow() {
	int lowerRow = cells[0].row;
	for (CellCoord cell : cells) {
		if (cell.row > lowerRow)
			lowerRow = cell.row;
	}
	return lowerRow;
}