#pragma once


#include "renderer.h"
#include <random>

std::random_device seed;
std::mt19937 randomEngine(seed());

#ifndef ARENA_WIDTH
#define ARENA_WIDTH 30
#endif

#ifndef ARENA_HEIGHT
#define ARENA_HEIGHT 30
#endif

class AppleEngine {
	int spawnDelay = 5;//ticks
	int spawnTimer = 0;
	Renderer& rend;
	//Point arenaSize;

	std::uniform_int_distribution<int> randX;
	std::uniform_int_distribution<int> randY;
	bool apples[ARENA_WIDTH * ARENA_HEIGHT] = {false};

public:

	AppleEngine(Renderer& rend) :rend(rend), randX(0, ARENA_WIDTH - 1), randY(0, ARENA_HEIGHT - 1)
	{
		//apples = new bool[arenaSize.x * arenaSize.y];
		for (int i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
		{
			apples[i] = false;
		}
	}
	~AppleEngine()
	{
	}

	void Reset()
	{
		for (int i = 0; i < ARENA_WIDTH * ARENA_HEIGHT; i++)
		{
			apples[i] = false;
		}
	}

	void Update() {
		spawnTimer++;
		if (spawnTimer >= spawnDelay) {
			int x = randX(randomEngine);
			int y = randY(randomEngine);

			apples[y * ARENA_WIDTH + x] = true;

			spawnTimer = 0;
		}
	}

	void Draw() {
		for (int x = 0; x < ARENA_WIDTH; x++)
		{
			for (int y = 0; y < ARENA_HEIGHT; y++)
			{
				if (apples[y * ARENA_WIDTH + x])
					rend.DrawCharacter('a', Point(x, y));
			}
		}
	}

	bool AppleCheck(Point position) {
		if (apples[position.y * ARENA_WIDTH + position.x])
		{
			apples[position.y * ARENA_WIDTH + position.x] = false;
			return true;
		}

		return false;
	}

};