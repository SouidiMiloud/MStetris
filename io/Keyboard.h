#ifndef KEYBOARD_H
#define KEYBOARD_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Keyboard
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);
	static bool getKey(int key);

private:
	static bool getKeyChanged(int key);
	static bool keys[];
	static bool keysChanged[];
};
#endif // !KEYBOARD_H
