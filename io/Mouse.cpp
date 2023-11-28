#include"Mouse.h"


double Mouse::x = 0;
double Mouse::y = 0;
double Mouse::dx = 0;
double Mouse::dy = 0;
double Mouse::lastX = 0;
double Mouse::lastY = 0;
bool Mouse::firstMouse = true;
bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = {};
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = {};



void Mouse::cursorPosCallback(GLFWwindow* window, double mouseX, double mouseY) {
	x = mouseX;
	y = mouseY;
	if (firstMouse) {
		firstMouse = false;
		lastX = x;
		lastY = y;
	}
	dx = x - lastX;
	dy = y - lastY;
	lastX = x;
	lastY = y;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	buttons[button] = action != GLFW_RELEASE;
	buttonsChanged[button] = action != GLFW_REPEAT;
}

double Mouse::getMouseX() {
	return x;
}

double Mouse::getMouseY() {
	return y;
}

double Mouse::getMouseDX() {
	double dx_ = dx;
	dx = 0;
	return dx_;
}

double Mouse::getMouseDY() {
	double dy_ = dy;
	dy = 0;
	return dy_;
}

bool Mouse::getButton(int button) {
	return buttons[button];
}

bool Mouse::getButtonChanged(int button) {
	bool changed = buttonsChanged[button];
	buttonsChanged[button] = false;
	return changed;
}

bool Mouse::buttonWentUp(int button) {
	return getButtonChanged(button) && !getButton(button);
}

bool Mouse::buttonWentDown(int button) {
	return getButtonChanged(button) && getButton(button);
}