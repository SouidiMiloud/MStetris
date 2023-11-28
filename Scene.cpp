#include"Scene.h"


Outline* Scene::outline;
Board* Scene::board;


void Scene::render() {
	board->render();
	outline->render();
	NextShapeGrid::render();
	Player::renderScore();
}

void Scene::clearResources() {
	delete(board);
	delete(outline);
	NextShapeGrid::clearResources();
	Player::clearResources();
}

void Scene::initializeComponents() {
	board = new Board();
	outline = new Outline();
	outline->makeOutline();
	NextShapeGrid::makeGrid();
	NextShapeGrid::generateNewShape();
	Player::initializeNumber();
}

Shape* Scene::generateNewShape() {

	Shape* shape = board->generateNewShape(NextShapeGrid::getShapeType(), NextShapeGrid::getColor());
	NextShapeGrid::generateNewShape();
	return shape;
}

void Scene::reload() {
	board->clear();
	Player::reset();
	Shape::reset();
	glfwSetCursor(Global::window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
}