#include"Digit.h"
#include<iostream>

Color Digit::enableColor = { 1, 1, 1 };
Color Digit::disableColor = { 0.2f, 0.2f, 0.2f };
float Digit::width = 0.033f;
const int Digit::FLASHING_DELAY = 20;
const Color Digit::flashingColor = { 0, 1, 0 };

const std::vector<int> Digit::maskValues = {
	63,						//0111111b       0
	6,						//0000110b       1
	91,						//1011011b       2
	79,						//1001111b       3
	102,					//1100110b       4
	109,					//1101101b       5
	125,					//1111101b       6
	7,						//0000111b       7
	127,					//1111111b       8
	111						//1101111b       9
};


Digit::Digit(Position center) {

	flashingCounter = 0;
	makeDigit(center);
}

Digit::~Digit() {
	for (Segment* segment : segments)
		delete(segment);
}

void Digit::displayDigit(int digit) {
	int mask = maskValues[digit];
	for (int i = 0; i < segments.size(); i++) 
		segments[i]->setColor(((mask >> i) & 1) ? flashingColor : disableColor);
	flashingCounter = 0;
}

void Digit::flashDigit() {
	if (flashingCounter > FLASHING_DELAY)
		return;
	if (flashingCounter++ != FLASHING_DELAY)
		return;
	for (Segment* segment : segments) {
		if (segment->getColor() != disableColor)
			segment->setColor(enableColor);
	}
}

void Digit::render() {
	flashDigit();
	for (int i = 0; i < segments.size(); i++) {
		Global::shader->passColor("color", segments[i]->getColor());
		segments[i]->render();
	}
}






void Digit::makeDigit(Position center) {
	segments.push_back(new Segment({ center.x - width / 2, center.y + width },
		{ center.x + width / 2, center.y + width }, HORIZONTAL, 1));

	segments.push_back(new Segment({ center.x + width / 2, center.y + width },
		{ center.x + width / 2, center.y + Segment::thickness }, VERTICAL, 1));

	segments.push_back(new Segment({ center.x + width / 2, center.y },
		{ center.x + width / 2, center.y - width }, VERTICAL, 1));

	segments.push_back(new Segment({ center.x - width / 2, center.y - width },
		{ center.x + width / 2, center.y - width }, HORIZONTAL, -1));

	segments.push_back(new Segment({ center.x - width / 2, center.y },
		{ center.x - width / 2, center.y - width }, VERTICAL, -1));

	segments.push_back(new Segment({center.x - width / 2, center.y + width},
		{ center.x - width / 2, center.y + Segment::thickness }, VERTICAL, -1));

		segments.push_back(new Segment({ center.x - width / 2, center.y },
		{center.x + width / 2, center.y}, HORIZONTAL, 1));
}