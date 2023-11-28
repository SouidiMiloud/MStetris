#include"Quit.h"



Quit::Quit(float width, float height, Color color) : Symbol(width, height, color){

}

Quit::~Quit() {
	Symbol::~Symbol();
}


void Quit::build(Position center) {
	auto buildSegment = [&](int coeff)->void {
		int size = getVerticesSize();
		addVertex({ center.x - width / 2, center.y + coeff * height / 2 });
		addVertex({ center.x - width / 2 + thickness, center.y + coeff * height / 2});
		addVertex({ center.x + width / 2, center.y - coeff * height / 2 });
		addVertex({ center.x + width / 2 - thickness, center.y - coeff * height / 2});
		fillIndices(size, size + 1, size + 2, size + 3);
	};
	buildSegment(1);
	buildSegment(-1);
	setup();
}