// tinyLocalJam2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "renderer.h"
#include <chrono>
#include <thread>
#include "GameObject.h"
#include "Apples.h"

int main()
{
	Point canvasSize(60, 30);
	Renderer rend(canvasSize);
	AppleEngine* apples = new AppleEngine(rend, canvasSize);

	GameObject player1(Point(5, 5), 5, 5, RIGHT, canvasSize, P1, apples);
	GameObject player2(Point(55, 25), 5, 5, LEFT, canvasSize, P2, apples);

	int maxDelay = 100, minDelay = 50;
	unsigned char gameSpeed = maxDelay;

	while (true) {

		player1.Update();
		player2.Update();
		player1.PlayerCollisionCheck(player2);
		player2.PlayerCollisionCheck(player1);
		player1.Draw(rend);
		player2.Draw(rend);
		apples->Draw();

		if (player1.dead && player2.dead) {
			rend.ClearScreen();
			std::cout << "================== NO ONE WINS :|  ==================" << std::endl;
			break;
		}
		else if (player1.dead) {
			rend.ClearScreen();
			std::cout << "==================PLAYER 2 WINS! (The X-snake) ==================" << std::endl;
			break;
		}
		else if (player2.dead) {
			rend.ClearScreen();
			std::cout << "==================PLAYER 1 WINS! (The O-snake)==================" << std::endl;
			break;
		}

		if (gameSpeed > minDelay) {
			gameSpeed--;
		}

		apples->Update();
		rend.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed));
	}

	char a;
	std::cin >> a;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
