#include"GridRow.h"


const int GridRow::MAX_ELEMENTS = Board::HORIZ_CELLS;

GridRow::GridRow(float y) {
	occupiedCells = 0;
	makeRow(y);
}

GridRow::~GridRow() {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		delete(cells[i]);
	}
}

bool GridRow::isFull() {
	return occupiedCells == MAX_ELEMENTS;
}

bool GridRow::isEmpty() {
	return occupiedCells == 0;
}

void GridRow::addElement() {
	occupiedCells++;
}

void GridRow::removeElement() {
	occupiedCells--;
}

void GridRow::affectRow(GridRow* row) {
	for (int i = 0; i < MAX_ELEMENTS; i++)
		cells[i]->setColor(row->cells[i]->getColor());
	occupiedCells = row->occupiedCells;
}

void GridRow::destroy() {

}

void GridRow::clear() {
	for (int i = 0; i < MAX_ELEMENTS; i++)
		cells[i]->setColor(Global::WHITE);
	occupiedCells = 0;
}

void GridRow::render() {
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		cells[i]->render();
	}
}

void GridRow::updateCellColor(int index, Color& color) {
	cells[index]->setColor(color);
}

bool GridRow::isCellFree(int index) {
	return cells[index]->isFree();
}


void GridRow::makeRow(float y) {
	float x = -MAX_ELEMENTS / 2.0f * Cell::getSize();
	for (int i = 0; i < MAX_ELEMENTS; i++) {
		cells.push_back(new Cell({ x, y }, Global::WHITE));
		x += Cell::getSize() + Board::MARGIN;
	}
}