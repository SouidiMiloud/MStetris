#ifndef DIGIT_H
#define DIGIT_H

#include"Segment.h"


//                0
//				 ___
//				| 6 |
//			   5|___| 1
//              |   |
//			   4|___| 2
//				  3


class Digit
{
public:
	Digit(Position center);
	~Digit();

	static Color enableColor;
	static Color disableColor;

	void render();
	void displayDigit(int digit);
private:
	int flashingCounter;
	static const int FLASHING_DELAY;
	static const Color flashingColor;
	static float width;
	std::vector<Segment*> segments;
	static const std::vector<int> maskValues;

	void flashDigit();
	void makeDigit(Position center);
};

#endif // !DIGIT_H
