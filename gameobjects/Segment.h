#ifndef SEGMENT_H
#define SEGMENT_H

#include"GameObject.h"

enum SegmentType {
	HORIZONTAL,
	VERTICAL
};

class Segment : public GameObject
{
public:
	Segment(Position vertex1, Position vertex2, SegmentType type, int coeff);
	~Segment();

	static float thickness;
	void setColor(Color color);
	Color getColor();

private:
	Color color;
};

#endif // !SEGMENT_H
