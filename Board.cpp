#include"Board.h"
#include"Shape.h"
#include"Player.h"
#include"gameobjects/Outline.h"
#include"GridRow.h"


Color Board::nextColor;
const float Board::MARGIN = 0.003f;
const int Board::HORIZ_CELLS = 10;
const int Board::VERT_CELLS = 20;
std::vector<GridRow*> Board::rows(VERT_CELLS);

std::map<ShapeType, std::vector<CellCoord>> Board::shapeCellsPos = {
	{I_SHAPE, {{-4,HORIZ_CELLS / 2},{-3,HORIZ_CELLS / 2},{-2,HORIZ_CELLS / 2},{-1,HORIZ_CELLS / 2}}},
	{O_SHAPE, {{-2,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2},{-1,HORIZ_CELLS / 2 - 1},{-1,HORIZ_CELLS / 2}}},
	{T_SHAPE, {{-3,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2 - 1},{-1,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2}}},
	{Z_SHAPE, {{-3,HORIZ_CELLS / 2},{-2,HORIZ_CELLS / 2},{-2,HORIZ_CELLS / 2 - 1},{-1,HORIZ_CELLS / 2 - 1}}},
	{S_SHAPE, {{-3,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2},{-1,HORIZ_CELLS / 2}}},
	{J_SHAPE, {{-3,HORIZ_CELLS / 2},{-2,HORIZ_CELLS / 2},{-1,HORIZ_CELLS / 2},{-1,HORIZ_CELLS / 2 - 1}}},
	{L_SHAPE, {{-3,HORIZ_CELLS / 2 - 1},{-2,HORIZ_CELLS / 2 - 1},{-1,HORIZ_CELLS / 2 - 1},{-1,HORIZ_CELLS / 2}}}
};


Board::Board(){

	Cell::setSize(1.5f / VERT_CELLS);

	makeBoard();
}

Board::~Board(){
	for (int i = 0; i < VERT_CELLS; i++) {
		delete(rows[i]);
	}
}

void Board::render() {
	for (int i = 0; i < VERT_CELLS; i++) {
		rows[i]->render();
	}
}

Shape* Board::generateNewShape(ShapeType type, Color color) {
	
	return new Shape(shapeCellsPos[type], color, type);

}

void Board::updateRowsContents(Shape* shape) {
	for (CellCoord cell : shape->cells) {
		rows[cell.row]->addElement();
	}
}

void Board::checkCompletedRows(Shape* shape) {
	int rowAbove = shape->getRowOfCellAbove();
	int rowBelow = shape->getRowOfCellBelow();
	if (isFailed(shape)) return;
	updateRowsContents(shape);
	for(int row = rowBelow; row >= rowAbove; row--) {
		if (rows[row]->isFull()) {
			destroyRow(row);
			row++;
			rowAbove++;
		}
	}
}

bool Board::isFailed(Shape* shape) {
	if (shape->getRowOfCellAbove() < 0) {
		Player::endGame();
		return true;
	}
	return false;
}

void Board::clear() {
	for (GridRow* row : rows)
		row->clear();
}

void Board::destroyRow(int row) {
	while (row > 0 && !rows[row]->isEmpty()) {
		rows[row]->affectRow(rows[row - 1]);
		row--;
	}
	rows[row]->clear();
	Player::updateScore();
}

void Board::updateColor(std::vector<CellCoord>& cells, Color color) {
	for (CellCoord cell : cells) {
		if (cell.row < 0)
			continue;
		rows[cell.row]->updateCellColor(cell.col, color);
	}
}

bool Board::isCellFree(CellCoord cell) {
	return rows[cell.row]->isCellFree(cell.col);
}




void Board::makeBoard() {
	Position position = { -HORIZ_CELLS / 2.0f * Cell::getSize(), 0.85f };
	Outline::topLeftPos = { position.x - Cell::getSize() / 2, position.y - Cell::getSize() / 2 };
	for (int i = 0; i < VERT_CELLS; i++) {
		position.y -= Cell::getSize() + MARGIN;
		rows[i] = new GridRow(position.y);
	}
	float rightX = position.x + HORIZ_CELLS * (Cell::getSize() + MARGIN) - Cell::getSize() / 2;
	Outline::bottomRightPos = { rightX, position.y - Cell::getSize() / 2 };
}