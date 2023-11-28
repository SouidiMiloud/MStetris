#ifndef SYMBOL_H
#define SYMBOL_H

#include"../GameObject.h"

class Symbol : public GameObject
{
public:
	Symbol(float width, float height, Color color);
	~Symbol();

	void render() override;
	virtual void build(Position center);

protected:
	float width;
	float height;
	static float thickness;
	Color color;
};

#endif // !SYMBOL_H
