#include"Button.h"


Color Button::normalColor = { 0.7f, 0.7f, 1 };
Color Button::hoverColor = { 0.5f, 0.5f, 1 };
Button* Button::hoveredButton;

Button::Button(Position center, float width, float height, Symbol* symbol, void (*onClick)(void)) {
	this->center = center;
	this->onClick = onClick;
	this->symbol = symbol;
	this->width = width;
	this->height = height;
	color = normalColor;

	buildButton();
}

Button::~Button() {
	delete(symbol);
	GameObject::~GameObject();
}

bool Button::isHovered() {
	float x = 2 * Mouse::getMouseX() / Global::sceneWidth - 1;
	float y = 1 - 2 * Mouse::getMouseY() / Global::sceneHeight;
	
	if (x <= center.x + width / 2 && x >= center.x - width / 2
				&& y <= center.y + height / 2 && y >= center.y - height / 2) {
		hoveredButton = this;
		return true;
	}
	return false;
}

void Button::checkClick() {
	if (isHovered()) {
		color = hoverColor;
		glfwSetCursor(Global::window, glfwCreateStandardCursor(GLFW_HAND_CURSOR));
		if (Mouse::buttonWentDown(GLFW_MOUSE_BUTTON_LEFT))
			onClick();
		return;
	}
	if (hoveredButton == this) {
		glfwSetCursor(Global::window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
		color = normalColor;
		hoveredButton = nullptr;
	}
}

void Button::render() {
	Global::shader->passColor("color", color);
	GameObject::render();

	symbol->render();
}



void Button::buildButton() {
	addVertex({ center.x - width / 2, center.y - height / 2 });
	addVertex({ center.x + width / 2, center.y - height / 2 });
	addVertex({ center.x + width / 2, center.y + height / 2 });
	addVertex({ center.x - width / 2, center.y + height / 2 });

	fillIndices(0, 1, 2, 3);
	setup();

	symbol->build(center);
}