#include"Segment.h"


float Segment::thickness = 0.005f;


Segment::Segment(Position vertex1, Position vertex2, SegmentType type, int coeff) {
	
	addVertex(vertex1);
	addVertex(vertex2);
	if(type == VERTICAL){
		addVertex({ vertex2.x + coeff * thickness, vertex2.y });
		addVertex({ vertex1.x + coeff * thickness, vertex1.y });
	}
	else {
		addVertex({ vertex2.x, vertex2.y + coeff * thickness });
		addVertex({ vertex1.x, vertex1.y + coeff * thickness });
	}
	fillIndices(0, 1, 2, 3);
	setup();
}

Segment::~Segment() {
	GameObject::~GameObject();
}

void Segment::setColor(Color color) {
	this->color = color;
}

Color Segment::getColor() {
	return color;
}