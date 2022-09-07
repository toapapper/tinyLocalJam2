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

public:
	bool* apples;

	AppleEngine(Renderer& rend, Point arenaSize) :rend(rend), arenaSize(arenaSize), randX(0, arenaSize.x), randY(0, arenaSize.y)
	{
		apples = new bool[arenaSize.x * arenaSize.y];
		for (int i = 0; i < arenaSize.x * arenaSize.y; i++)
		{
			apples[i] = false;
		}
	}
	~AppleEngine()
	{
		delete[] apples;
	}

	void Update() {
		spawnTimer++;
		if (spawnTimer >= spawnDelay) {
			int x = randX(randomEngine);
			int y = randY(randomEngine);

			apples[y * arenaSize.x + x] = true;

			spawnTimer = 0;
		}
	}

	void Draw() {
		for (int i = 0; i < arenaSize.x * arenaSize.y; i++)
		{
			if (apples[i])
				rend.DrawCharacter('a', Point((i % arenaSize.x), (i - i % arenaSize.x) / arenaSize.x));
		}
	}

	bool AppleCheck(Point position) {

		if (apples[position.y * arenaSize.x + position.x])
		{
			apples[position.y * arenaSize.x + position.x] = false;
			return true;
		}

		return false;
	}

};