#include"Retry.h"



Retry::Retry(float width, float height, Color color) : Symbol(width, height, color) {

}

Retry::~Retry() {
	Symbol::~Symbol();
}


void Retry::build(Position center) {
	
	int sectors = 20;
	float stepAngle = 2 * Global::PI / sectors;
	int filledSectors = 18;
	for (int i = 0; i < filledSectors; i++) {
		float xOut = center.x + width * cos(i * stepAngle);
		float yOut = center.y + width * sin(i * stepAngle);
		addVertex({ xOut, yOut });

		float xIn = center.x + (width - thickness) * cos(i * stepAngle);
		float yIn = center.y + (width - thickness) * sin(i * stepAngle);
		addVertex({ xIn, yIn });

		if (i != filledSectors - 1)
			fillIndices(2 * i, 2 * i + 1, 2 * i + 3, 2 * (i + 1));
	}
	makeArrow(center);
	setup();
}

void Retry::makeArrow(Position center) {
	float arrowWidth = 0.02f;
	int size = getVerticesSize();
	Position position = { center.x + width - thickness / 2, center.y - thickness };
	addVertex(position);
	addVertex({ position.x + arrowWidth, position.y + arrowWidth });
	addVertex({ position.x - arrowWidth, position.y + arrowWidth });
	fillIndices(size, size + 1, size + 2);
}