#include "renderer.h"
#include "windows.h"

enum playerDirection {
	LEFT, RIGHT, UP, DOWN, COUNT
};

class GameObject {

	int length;
	int speed;
	playerDirection myDirection;
	Point* positions = new Point[length];
	Point parentPos;
	Point startPos;


public:
	GameObject(Point startPos, int length, int speed, playerDirection dir) {
		this->startPos = startPos;
		this->length = length;
		this->speed = speed;
		this->myDirection = dir;
		positions[0] = startPos;
		GetStartPositions();
	}


	void GetStartPositions() {
		for (size_t i = 1; i < length; i++)
		{
			if (myDirection == RIGHT)
				positions[i].x = positions[0].x - i;
			else
				positions[i].x = positions[0].x + i;

		}
	}


	void IncreaseInSize(int value) {
		length += value;
		Point* tempArray = new Point[length];
		for (size_t i = 0; i < length -1; i++)
		{
			tempArray[i] = positions[i]; 
		}
		tempArray[length - 1] = tempArray[length - 2];
		delete positions;
		positions = tempArray;
	}


	void PlayerInput() {
		if (GetKeyState('A') && myDirection != RIGHT) {
			myDirection = LEFT;
		}
		else if (GetKeyState('D') && myDirection != LEFT) {
			myDirection = RIGHT;
		}
		else if (GetKeyState('W') && myDirection != DOWN) {
			myDirection = UP;
		}
		else if (GetKeyState('S') && myDirection != UP) {
			myDirection = DOWN;
		}
		Move();
	}

	void Die() {

	}

	bool CollisionCheck() {
		if (positions[0].x <= 0 && myDirection == LEFT) {
			Die();
			return false;
		}
		else if (positions[0].x >= 99 && myDirection == RIGHT) {
			Die();
			return false;
		}
		else if (positions[0].y <= 0 && myDirection == UP) {
			Die();
			return false;
		}
		else if (positions[0].y >= 99 && myDirection == DOWN) {
			Die();
			return false;
		}
		return true;
	}

	void Move() {
		switch (myDirection)
		{
		case LEFT:
			if (CollisionCheck()) {
				positions[0].x--;
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
			}
			break;
		case RIGHT:
			if (CollisionCheck()) {
				positions[0].x++;
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
			}
			break;
		case UP:
			if (CollisionCheck()) {
				positions[0].y--;
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
			}
			break;
		case DOWN:
			if (CollisionCheck()) {
				positions[0].y++;
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
			}
			break;
		default:
			break;
		}
	}

	void Update() {
		
		PlayerInput();
	}

	void Draw() {

	}
};