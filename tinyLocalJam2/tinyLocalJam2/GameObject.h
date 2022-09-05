#pragma once

#include "renderer.h"
#include "windows.h"
#include "Apples.h"
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
	std::vector<Point> positions;
	Point parentPos;
	Point startPos;
	Point boardSize;
	PlayerSelection playerSelection;
	AppleEngine* apples;

	bool boostAvailable = false;
	bool startInvincibility = true;

public:
	bool dead = false;

	GameObject(Point startPos, int length, int speed, playerDirection dir, Point boardSize, PlayerSelection playerSelection, AppleEngine* apples):apples(apples) {
		this->startPos = startPos;
		this->length = length;
		this->speed = speed;
		this->myDirection = dir;
		this->boardSize = boardSize;
		this->playerSelection = playerSelection;

		positions = std::vector<Point>(length);

		for (int i = 0; i < length; i++) {
			positions[i] = startPos;
		}

		//positions[0] = startPos;
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
		if (size <= length)
		{
			length = size;
		}
		else
		{

			for (int i = 0; i < size - length; i++)
			{
				positions.push_back(positions[length-1]);
			}
			length = size;
		}
	}

	void Boost() {
		Move(5);
		boostAvailable = false;
	}

	void PlayerInput() {

		switch (playerSelection)
		{
		case P1:

			if (GetAsyncKeyState(VK_LSHIFT) && boostAvailable) {
				Boost();
			}
			else if (GetAsyncKeyState('A') < 0 && myDirection != RIGHT) {
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
			if (GetAsyncKeyState(VK_RSHIFT) && boostAvailable) {
				Boost();
			}
			else if ((GetAsyncKeyState(VK_LEFT) < 0 || GetAsyncKeyState('J') < 0) && myDirection != RIGHT) {
				myDirection = LEFT;
			}
			else if ((GetAsyncKeyState(VK_RIGHT) < 0 || GetAsyncKeyState('L') < 0) && myDirection != LEFT) {
				myDirection = RIGHT;
			}
			else if ((GetAsyncKeyState(VK_UP) < 0 || GetAsyncKeyState('I') < 0) && myDirection != DOWN) {
				myDirection = UP;
			}
			else if (GetAsyncKeyState(VK_DOWN) < 0 && myDirection != UP) {
				myDirection = DOWN;
			}
			break;
		}

		Move(1);
	}


	void PlayerCollisionCheck(GameObject other) {
		for (int i = 0; i < other.positions.size(); i++)
		{
			if (positions[0] == other.positions[i])
			{
				Die();
			}
		}
		if (startInvincibility)
			return;
		for (int i = 1; i < length; i++)
		{
			if (positions[0] == positions[i])
			{
				Die();
			}
		}
	}

	void Die() {

		dead = true;
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
		else {
			if (apples->AppleCheck(positions[0])) {
				ChangeSize(length + 1);
				boostAvailable = true;
			}
		}
		return true;
	}

	void Move(int speed) {
		switch (myDirection)
		{
		case LEFT:
			if (CollisionCheck()) {
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x -= speed;
			}
			break;
		case RIGHT:
			if (CollisionCheck()) {
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x += speed;
			}
			break;
		case UP:
			if (CollisionCheck()) {
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y -= speed;
			}
			break;
		case DOWN:
			if (CollisionCheck()) {
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y += speed;
			}
			break;
		default:
			break;
		}

		startInvincibility = false;
	}

	void Update() {
		
		PlayerInput();
	}

	void Draw(Renderer& rend) {
		switch (playerSelection) {

		case P1:
			for (int i = 0; i < length; i++) {
				if(i == 0)
					rend.DrawCharacter('O', positions[i]);
				else
					rend.DrawCharacter('o', positions[i]);

			}
			break;
		case P2:
			for (int i = 0; i < length; i++) {
				if(i == 0)
					rend.DrawCharacter('X', positions[i]);
				else
					rend.DrawCharacter('x', positions[i]);
			}
			break;
		}
	}
};