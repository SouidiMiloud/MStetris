#include"Global.h"
#include"Shape.h"


int Global::sceneWidth;
int Global::sceneHeight;
Shader* Global::shader;
GLFWwindow* Global::window;
Shape* Global::shape;
const Color Global::WHITE = { 1, 1, 1 };
const double Global::PI = 3.1415926536;

void Global::clearResources() {
	delete(shape);
	delete(shader);
	delete(window);
}