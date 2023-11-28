#include"Player.h"


int Player::score = 0;
bool Player::pause = false;
bool Player::gameOver = false;
int Player::counterLevelChange = 0;
int Player::level = 1;
int Player::COUNTER_LEVEL_CHANGE = 300;
const int Player::DIFFERENCE_BETWEEN_TWO_LEVELS = 2;
std::vector<Digit*> Player::number;


void Player::reset() {
	score = 0;
	displayScore();
	pause = false;
	gameOver = false;
	counterLevelChange = 0;
	level = 1;
	COUNTER_LEVEL_CHANGE = 300;
}

Player::~Player() {
	
}

void Player::clearResources() {
	for (Digit* digit : number) {
		delete(digit);
	}
}

void Player::play(Shape* shape) {
	if (pause || gameOver) return;
	if (Keyboard::keyWentDown(GLFW_KEY_UP))
		shape->rotate();
	shape->moveDown();
	if (Keyboard::keyWentDown(GLFW_KEY_RIGHT))
		shape->moveHorizontally(RIGHT);
	if (Keyboard::keyWentDown(GLFW_KEY_LEFT))
		shape->moveHorizontally(LEFT);
	if (Keyboard::keyWentDown(GLFW_KEY_DOWN))
		shape->drop();
	if (Keyboard::keyWentDown(GLFW_KEY_SPACE))
		Player::pauseGame();
	manageLevel();
}

void Player::manageLevel() {
	if (counterLevelChange++ > COUNTER_LEVEL_CHANGE) {
		counterLevelChange = 0;
		COUNTER_LEVEL_CHANGE += 7 * ++level;
		Shape::TIMER_LIMIT -= DIFFERENCE_BETWEEN_TWO_LEVELS;
	}
}

void Player::initializeNumber() {
	float x = Board::HORIZ_CELLS / 2 * (Cell::getSize() + Board::MARGIN);
	Position digitPos = { x + 0.225f, 0.65f };
	float digitsDistance = 0.052f;
	for (int i = 0; i < 4; i++) {
		number.push_back(new Digit(digitPos));
		digitPos.x -= digitsDistance;
		number[i]->displayDigit(0);
	}
}

void Player::renderScore() {
	for (int i = 0; i < number.size(); i++)
		number[i]->render();
}

void Player::updateScore() {
	score += level;
	displayScore();
}

void Player::displayScore() {
	int tmpScore = score;
	for (int i = 0; i < 4; i++) {
		number[i]->displayDigit(tmpScore % 10);
		tmpScore /= 10;
	}
}

void Player::pauseGame() {
	pause = !pause;
}

void Player::endGame() {
	gameOver = true;
}

bool Player::isGameOver() {
	return gameOver;
}