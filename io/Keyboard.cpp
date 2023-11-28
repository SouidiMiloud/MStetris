#include"Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = {};
bool Keyboard::keysChanged[GLFW_KEY_LAST] = {};

void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keys[key] = action != GLFW_RELEASE;
	keysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::getKey(int key) {
	return keys[key];
}

bool Keyboard::getKeyChanged(int key) {
	bool changed = keysChanged[key];
	keysChanged[key] = false;
	return changed;
}

bool Keyboard::keyWentUp(int key) {
	return !getKey(key) && getKeyChanged(key);
}

bool Keyboard::keyWentDown(int key) {
	return getKey(key) && getKeyChanged(key);
}