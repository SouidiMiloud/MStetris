#ifndef QUIT_H
#define QUIT_H

#include"Symbol.h"

class Quit : public Symbol
{
public:
	Quit(float width, float height, Color color);
	~Quit();

	void build(Position center) override;

private:
};

#endif // !QUIT_H
