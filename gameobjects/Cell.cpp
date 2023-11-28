#include"Cell.h"


float Cell::size;

Cell::Cell(Position center, Color color){

	this->color = color;
	makeCell(center);
}

Cell::~Cell(){
	GameObject::~GameObject();
}

void Cell::render() {
	Global::shader->passColor("color", color);
	GameObject::render();
}

void Cell::setColor(Color color) {
	this->color = color;
}

Color Cell::getColor() {
	return color;
}

float Cell::getSize() {
	return size;
}

void Cell::setSize(float size) {
	Cell::size = size;
}

void Cell::clear() {
	setColor(Global::WHITE);
}

bool Cell::isFree() {
	return color == Global::WHITE;
}

void Cell::makeCell(Position center) {
	
	addVertex({center.x - size / 2, center.y - size / 2});
	addVertex({center.x + size / 2, center.y - size / 2});
	addVertex({center.x + size / 2, center.y + size / 2});
	addVertex({center.x - size / 2, center.y + size / 2});

	fillIndices(0, 1, 2, 3);

	setup();
}