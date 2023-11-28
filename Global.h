#ifndef GLOBAL_H
#define GLOBAL_H


#include"assets/Shader.h"

struct Position {
	float x;
	float y;
	Position operator+(const Position& pos) {
		return {x += pos.x, y += pos.y};
	}
};
struct Color {
	float r;
	float g;
	float b;
	const float* toFloatPtr() {
		return &r;
	}
	bool operator==(const Color& col) {
		return r == col.r && g == col.g && b == col.b;
	}
	bool operator!=(const Color& col) {
		return r != col.r || g != col.g || b != col.b;
	}
};

class Shape;

class Global
{
public:

	static int sceneWidth;
	static int sceneHeight;
	static Shader* shader;
	static GLFWwindow* window;
	static Shape* shape;
	static const Color WHITE;
	static const double PI;

	static void clearResources();
};

#endif // !GLOBAL_H
