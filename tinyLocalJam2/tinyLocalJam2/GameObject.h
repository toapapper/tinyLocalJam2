#include "renderer.h"
#include "windows.h"
//#include <iostream>

enum playerDirection {
	LEFT, RIGHT, UP, DOWN
};

enum PlayerSelection{P1,P2,COUNT};

class GameObject {

	int length;
	int speed;
	int score;
	playerDirection myDirection;
	Point* positions = new Point[length];
	Point parentPos;
	Point startPos;
	Point boardSize;
	PlayerSelection playerSelection;


public:
	GameObject(Point startPos, int length, int speed, playerDirection dir, Point boardSize, PlayerSelection playerSelection) {
		this->startPos = startPos;
		this->length = length;
		this->speed = speed;
		this->myDirection = dir;
		this->boardSize = boardSize;
		this->playerSelection = playerSelection;
		positions[0] = startPos;
		GetStartPositions();
	}

	void GainScore(int value) {
		score += value;
	}

	void GetStartPositions() {
		for (int i = 1; i < length; i++)
		{
			if (myDirection == RIGHT)
				positions[i].x = positions[0].x - i;
			else
				positions[i].x = positions[0].x + i;

			positions[i].y = startPos.y;
		}
	}

	void ChangeSize(int size) {//TODO
		if (size == 0)
			return;
		else if (size < 0 && size <= -length) {
			if (length == 1)
				return;
			length = 1;
		}
		else
			length += size;


		Point* tempArray = new Point[length];
		for (int i = 0; i < length -1; i++)
		{
			tempArray[i] = positions[i]; 
		}
		tempArray[length - 1] = tempArray[length - 2];
		delete positions;
		positions = tempArray;
	}


	void PlayerInput() {

		switch (playerSelection)
		{
		case P1:
			if (GetAsyncKeyState('A') < 0 && myDirection != RIGHT) {
				myDirection = LEFT;
			}
			else if (GetAsyncKeyState('D') < 0 && myDirection != LEFT) {
				myDirection = RIGHT;
			}
			else if (GetAsyncKeyState('W') < 0 && myDirection != DOWN) {
				myDirection = UP;
			}
			else if (GetAsyncKeyState('S') < 0 && myDirection != UP) {
				myDirection = DOWN;
			}
			break;
		case P2:
			if (GetAsyncKeyState('J') < 0 && myDirection != RIGHT) {
				myDirection = LEFT;
			}
			else if (GetAsyncKeyState('L') < 0 && myDirection != LEFT) {
				myDirection = RIGHT;
			}
			else if (GetAsyncKeyState('I') < 0 && myDirection != DOWN) {
				myDirection = UP;
			}
			else if (GetAsyncKeyState('K') < 0 && myDirection != UP) {
				myDirection = DOWN;
			}
			break;
		}

		Move();
	}

	void Die() {
		ChangeSize((length - 2) * -1);
	}

	bool CollisionCheck() {
		if (positions[0].x <= 0 && myDirection == LEFT) {
			Die();
			return false;
		}
		else if (positions[0].x >= boardSize.x && myDirection == RIGHT) {
			Die();
			return false;
		}
		else if (positions[0].y <= 0 && myDirection == UP) {
			Die();
			return false;
		}
		else if (positions[0].y >= boardSize.y && myDirection == DOWN) {
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
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x--;
			}
			break;
		case RIGHT:
			if (CollisionCheck()) {
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x++;
			}
			break;
		case UP:
			if (CollisionCheck()) {
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y--;
			}
			break;
		case DOWN:
			if (CollisionCheck()) {
				for (int i = length; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y++;
			}
			break;
		default:
			break;
		}
	}

	void Update() {
		
		PlayerInput();
	}

	void Draw(Renderer& rend) {
		for (int i = 0; i < length; i++) {
			rend.DrawCharacter('O', positions[i]);
		}
	}
};