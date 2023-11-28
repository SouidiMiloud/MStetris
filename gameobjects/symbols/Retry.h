#ifndef RETRY_H 
#define RETRY_H 

#include"Symbol.h"

class Retry : public Symbol
{
public:
	Retry(float width, float height, Color color);
	~Retry();

	void build(Position center) override;

private:
	void makeArrow(Position position);
};

#endif // !RETRY_H
