#pragma once

#include "renderer.h"
#include <random>

std::random_device seed;
std::mt19937 randomEngine(seed());

class AppleEngine {
	int spawnDelay = 5;//ticks
	int spawnTimer = 0;
	Renderer& rend;
	Point arenaSize;

	std::uniform_int_distribution<int> randX;
	std::uniform_int_distribution<int> randY;
	bool* applesTemp;

public:

	AppleEngine(Renderer& rend, Point arenaSize) :rend(rend), arenaSize(arenaSize), randX(0, arenaSize.x), randY(0, arenaSize.y)
	{
		applesTemp = new bool[arenaSize.x * arenaSize.y];
		for (int i = 0; i < arenaSize.x * arenaSize.y; i++)
		{
			applesTemp[i] = false;
		}
	}
	~AppleEngine()
	{
		delete[] applesTemp;
	}

	void Update() {
		spawnTimer++;
		if (spawnTimer >= spawnDelay) {
			int x = randX(randomEngine);
			int y = randY(randomEngine);

			applesTemp[y * arenaSize.x + x] = true;

			spawnTimer = 0;
		}
	}

	void Draw() {

		for (int x = 0; x < arenaSize.x; x++)
		{
			for (int y = 0; y < arenaSize.y; y++)
			{
				if (applesTemp[y * arenaSize.x + x])
					rend.DrawCharacter('a', Point(x, y));
			}
		}
	}

	bool AppleCheck(Point position) {

		if (applesTemp[position.y * arenaSize.x + position.x])
		{
			applesTemp[position.y * arenaSize.x + position.x] = false;
			return true;
		}

		return false;
	}

};