#ifndef BUTTON_H
#define BUTTON_H

#include"../gameobjects/symbols/Symbol.h"
#include"../io/Mouse.h"

class Button : public GameObject
{
public:
	Button(Position center, float width, float height, Symbol* symbol, void (*onClick)(void));
	~Button();

	void render() override;
	void checkClick();
	void (*onClick)(void);

private:
	Position center;
	static Color normalColor;
	static Color hoverColor;
	Color color;
	float width;
	float height;
	Symbol* symbol;
	static Button* hoveredButton;

	bool isHovered();
	void buildButton();
};

#endif // !BUTTON_H
