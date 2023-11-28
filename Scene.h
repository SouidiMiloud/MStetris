#ifndef SCENE_H
#define SCENE_H

#include"gameobjects/Outline.h"
#include"gameobjects/NextShapeGrid.h"
#include"Player.h"

class Scene
{
public:
	static void render();
	static void clearResources();
	static void initializeComponents();
	static Shape* generateNewShape();
	static void reload();

private:
	static Outline* outline;
	static Board* board;
	static ShapeType currentShapeType;
	static ShapeType nextShapeType;
};

#endif // !SCENE_H
