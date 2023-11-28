#ifndef OUTLINE_H
#define OUTLINE_H

#include"../Board.h"
#include"../Global.h"


class Outline : public GameObject
{
public:
	~Outline();

	static Position topLeftPos;
	static Position bottomRightPos;

	void render() override;
	void makeOutline();
private:
	static Color color;
	static float thickness;

	void makeOutlineSide(Position pos1, Position pos2, int coeffX, int coeffY);
};

#endif // !OUTLINE_H
