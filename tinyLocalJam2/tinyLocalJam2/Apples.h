#pragma once

#include "renderer.h"
#include <random>


class AppleEngine {
	int spawnDelay = 5;//ticks
	int spawnTimer = 0;
	Renderer& rend;
	Point arenaSize;
	std::uniform_int_distribution<unsigned> randX;
	std::uniform_int_distribution<unsigned> randY;
	std::default_random_engine aaaX;

public:
	std::vector<Point> apples;

	AppleEngine(Renderer& rend, Point arenaSize) :rend(rend), arenaSize() {
			randX = std::uniform_int_distribution<unsigned>(0, arenaSize.x);
			randX = std::uniform_int_distribution<unsigned>(0, arenaSize.x);
			randY = std::uniform_int_distribution<unsigned>(0, arenaSize.y);

			unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
			aaaX = std::default_random_engine(seed);
	}
	~AppleEngine(){}

	void Update() {
		spawnTimer++;
		if (spawnTimer >= spawnDelay) {
			int x = randX(aaaX);
			int y = randY(aaaX);

			apples.push_back(Point(x, y));

			spawnTimer = 0;
		}
	}

	void Draw() {
		for (Point apple : apples) {
			rend.DrawCharacter('a', apple);
		}
	}

	bool AppleCheck(Point position) {
		int i = 0;
		for (; i < apples.size(); i++) {
			if (apples[i] == position) {
				apples[i] = Point(-1, -1);
				return true;
			}
		}


		return false;
	}

};