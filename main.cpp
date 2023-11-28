#include"Scene.h"
#include"Player.h"

#include<chrono>
#include<thread>

#include"ui/Button.h"
#include"gameobjects/symbols/Quit.h"
#include"gameobjects/symbols/Retry.h"



void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void exit();
void retry();
void manageButtons();

std::vector<Button*> buttons;

int WinMain() {
	std::cout << "hello opengl developer" << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	Global::sceneWidth = mode->height * 0.9f;
	Global::sceneHeight = mode->height * 0.9f;

	Global::window = glfwCreateWindow(Global::sceneWidth, Global::sceneHeight, "SOUIDI_TETRIS", NULL, NULL);
	if (Global::window == NULL) {
		std::cout << "failed to create the scene!" << std::endl;
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(Global::window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to initialize glad" << std::endl;
		return 0;
	}
	glViewport(0, 0, Global::sceneWidth, Global::sceneHeight);
	glfwSetKeyCallback(Global::window, Keyboard::keyCallback);
	glfwSetMouseButtonCallback(Global::window, Mouse::mouseButtonCallback);
	glfwSetCursorPosCallback(Global::window, Mouse::cursorPosCallback);
	glfwSetFramebufferSizeCallback(Global::window, framebufferSizeCallback);

	Global::shader = new Shader();

	//glm::mat4 projection = glm::mat4(static_cast<float>(Global::sceneHeight) / Global::sceneWidth, 0, 0, 0,
	//									0, 1, 0, 0,
	//									0, 0, 1, 0,
	//									0, 0, 0, 1
	//	);

	float projection[16] = { static_cast<float>(Global::sceneHeight) / Global::sceneWidth, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};


	Scene::initializeComponents();

	Global::shape = Scene::generateNewShape();

	Quit quitSymbol = Quit(0.07f, 0.09f, { 1, 0, 0 });
	Retry retrySymbol = Retry(0.05f, 0.09f, { 0.2f, 0.6f, 0.2f });

	buttons.push_back(new Button({ 0.15f, 0.3f}, 0.25f, 0.15f, &quitSymbol, exit ));
	buttons.push_back(new Button({ -0.15f, 0.3f }, 0.25f, 0.15f, & retrySymbol, retry ));

	const double targetFps = 40.0;
	const double micSecondsPerFrame = 1e6 / targetFps;
	while (!glfwWindowShouldClose(Global::window)) {

		auto start = std::chrono::high_resolution_clock::now();

		if (Keyboard::keyWentDown(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(Global::window, true);
		
		glClearColor(0.1f, 0.1f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		Global::shader->activate();
		Global::shader->passMatrix("projection", projection);

		Player::play(Global::shape);

		Scene::render();
		manageButtons();
		if (Shape::stoped) {
			delete(Global::shape);
			Global::shape = Scene::generateNewShape();
		}

		glfwSwapBuffers(Global::window);
		glfwPollEvents();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		double sleepTime = micSecondsPerFrame - duration.count();
		if (sleepTime > 0)
			std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(sleepTime)));
	}
	for (Button* button : buttons)
		delete(button);
	delete(Global::shader);
	Scene::clearResources();
	delete(Global::shape);
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	Global::sceneWidth = width;
	Global::sceneHeight = height;
}

void manageButtons() {
	if (!Player::isGameOver())
		return;
	for (Button* button : buttons) {
		button->render();
		button->checkClick();
	}
}

void exit() {
	glfwSetWindowShouldClose(Global::window, true);
}

void retry() {
	Scene::reload();
	delete(Global::shape);
	Global::shape = Scene::generateNewShape();
}