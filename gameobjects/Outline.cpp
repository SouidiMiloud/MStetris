#include"Outline.h"


float Outline::thickness = 0.04f;
Color Outline::color = { 0.3f, 0.35f, 0.35f };
Position Outline::topLeftPos;
Position Outline::bottomRightPos;


Outline::~Outline() {
	GameObject::~GameObject();
}

void Outline::render() {
	Global::shader->passColor("color", color);
	GameObject::render();
}




void Outline::makeOutline() {
	makeOutlineSide({ topLeftPos.x, topLeftPos.y + thickness },
		{ topLeftPos.x, bottomRightPos.y - thickness }, -1, 0);
	
	makeOutlineSide(bottomRightPos, { bottomRightPos.x, topLeftPos.y }, 1, 0);
	makeOutlineSide(topLeftPos, { bottomRightPos.x, topLeftPos.y }, 0, 1);
	makeOutlineSide(bottomRightPos, {topLeftPos.x, bottomRightPos.y}, 0, -1);
	
	Position topRight = { bottomRightPos.x + 0.35f, topLeftPos.y };
	makeOutlineSide({ bottomRightPos.x, topLeftPos.y }, topRight, 0, 1);
	makeOutlineSide(bottomRightPos, { topRight.x, bottomRightPos.y }, 0, -1);
	makeOutlineSide({ topRight.x - thickness, topRight.y }, { topRight.x - thickness, bottomRightPos.y }, 1, 0);

	setup();
}

void Outline::makeOutlineSide(Position pos1, Position pos2, int coeffX, int coeffY) {
	int size = getVerticesSize();
	addVertex(pos1);
	addVertex({ pos1.x + coeffX * thickness, pos1.y + coeffY * thickness });
	addVertex({ pos2.x + coeffX * thickness, pos2.y + coeffY * thickness });
	addVertex(pos2);
	fillIndices(size, size + 1, size + 2, size + 3);
}