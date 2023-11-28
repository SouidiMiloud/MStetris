#ifndef MOUSE_H
#define MOUSE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Mouse
{
public:
	static void cursorPosCallback(GLFWwindow* window, double mouseX, double mouseY);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static double getMouseX();
	static double getMouseY();
	static double getMouseDX();
	static double getMouseDY();
	static bool getButton(int button);
	static bool getButtonChanged(int button);
	static bool buttonWentUp(int button);
	static bool buttonWentDown(int button);
private:
	static double x;
	static double y;
	static double lastX;
	static double lastY;
	static double dx;
	static double dy;
	static bool firstMouse;
	static bool buttons[];
	static bool buttonsChanged[];
};

#endif // !MOUSE_H
