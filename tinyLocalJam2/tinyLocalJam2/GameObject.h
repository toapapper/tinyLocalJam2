#pragma once

#include "renderer.h"
#include "windows.h"
#include "Apples.h"
#include <vector>

enum playerDirection {
	LEFT, RIGHT, UP, DOWN
};

enum PlayerSelection{P1,P2,COUNT};

class GameObject {

	int length;
	int speed;
	int score;
	playerDirection myDirection;
	playerDirection startDirection;
	std::vector<Point> positions;
	Point parentPos;
	Point startPos;
	Point boardSize;
	PlayerSelection playerSelection;
	AppleEngine& apples;

	bool boostAvailable = false;
	bool isAnimating = false;

public:
	bool isAlive = true;
	bool dead = false;

	GameObject(Point startPos, int length, int speed, playerDirection dir, Point boardSize, PlayerSelection playerSelection, AppleEngine& apples):apples(apples) {
		this->startPos = startPos;
		this->length = length;
		this->speed = speed;
		this->myDirection = dir;
		startDirection = dir;
		this->boardSize = boardSize;
		this->playerSelection = playerSelection;

		positions = std::vector<Point>(length);

		for (int i = 0; i < length; i++) {
			positions[i] = startPos;
		}

		//positions[0] = startPos;
		GetStartPositions();
	}

	~GameObject()
	{
		positions.clear();
	}

	void Reset()
	{
		for (Point& pos : positions)
		{
			pos = startPos;
		}

		boostAvailable = false;
		isAlive = true;
		dead = false;
		isAnimating = false;

		ChangeSize(5);


		myDirection = startDirection;
		GetStartPositions();
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

	void ChangeSize(int size) {//Changes Size to the specified number
		if (size == 0)
			return;
		if (size <= length)
		{
			positions.resize(size);
			length = size;
		}
		else
		{
			positions.resize(size);
			for (int i = length; i < size; i++)
			{
				Point pos(positions[i]);
				positions[i] = pos;
			}
			length = size;
		}
	}

	void Boost(const GameObject& other) {
		Move(5, other);
		boostAvailable = false;
	}

	void PlayerInput(const GameObject& other) {

		switch (playerSelection)
		{
		case P1:

			if (GetAsyncKeyState(VK_LSHIFT) && boostAvailable) {
				Boost(other);
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
				Boost(other);
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

		Move(1, other);
	}


	bool PlayerCollisionCheck(const GameObject& other) {
		for (int i = 0; i < other.positions.size(); i++)
		{
			if (positions[0] == other.positions[i])
			{
				return true;
			}
		}
		for (int i = 1; i < length; i++)
		{
			if (positions[0] == positions[i])
			{
				return true;
			}
		}
		return false;
	}

	void Die() {
		isAlive = false;
		dead = true;
	}

	bool CollisionCheck(const GameObject& other) {
		if (PlayerCollisionCheck(other))
		{
			Die();
			return false;
		}
		else if (positions[0].x <= 0 && myDirection == LEFT) {
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
			if (apples.AppleCheck(positions[0])) {
				ChangeSize(length + 1);
				boostAvailable = true;
			}
		}
		return true;
	}

	void Move(int speed, const GameObject& other) {

		if (CollisionCheck(other))
		{
			switch (myDirection)
			{
			case LEFT:
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x -= speed;

				break;
			case RIGHT:

				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].x += speed;

				break;
			case UP:
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y -= speed;

				break;
			case DOWN:
				for (int i = length - 1; i > 0; i--)
				{
					positions[i] = positions[i - 1];
				}
				positions[0].y += speed;
				break;
			default:
				break;
			}
		}
	}

	void Update(const GameObject& other) {
		
		PlayerInput(other);
	}

	void Draw(Renderer& rend) {
		switch (playerSelection) {

		case P1:
			if (isAlive)
			{
				for (int i = 0; i < length; i++) {
					if(i == 0)
						rend.DrawCharacter('O', positions[i]);
					else
						rend.DrawCharacter('o', positions[i]);
				}
			}
			else
			{
				if (isAnimating == false)
				{
					for (int i = 0; i < length; i++)
					{
						rend.DrawCharacter('*', positions[i]);
					}
					isAnimating = true;
				}
				else
				{
					for (int i = 0; i < length; i++)
					{
						rend.DrawCharacter('¤', positions[i]);
					}
					isAnimating = false;
				}
			}
			break;
		case P2:
			if (isAlive)
			{
				for (int i = 0; i < length; i++) {
					if(i == 0)
						rend.DrawCharacter('X', positions[i]);
					else
						rend.DrawCharacter('x', positions[i]);
				}
			}
			else
			{
				if (isAnimating == false)
				{
					for (int i = 0; i < length; i++)
					{
						rend.DrawCharacter('*', positions[i]);
					}
					isAnimating = true;
				}
				else
				{
					for (int i = 0; i < length; i++)
					{
						rend.DrawCharacter('¤', positions[i]);
					}
					isAnimating = false;
				}
			}
			break;
		}
	}
};