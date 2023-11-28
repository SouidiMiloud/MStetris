#include"Symbol.h"


float Symbol::thickness = 0.015f;

Symbol::Symbol(float width, float height, Color color) {
	this->width = width;
	this->height = height;
	this->color = color;
}

Symbol::~Symbol() {
	GameObject::~GameObject();
}

void Symbol::render() {
	Global::shader->passColor("color", color);
	GameObject::render();
}

void Symbol::build(Position center) {
	
}