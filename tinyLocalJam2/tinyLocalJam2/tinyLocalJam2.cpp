// tinyLocalJam2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "renderer.h"
#include <chrono>
#include <thread>
#include "GameObject.h"

int main()
{
	Point canvasSize(60, 30);
	Renderer rend(canvasSize);
	rend.DrawCharacter('O', Point(40, 20));
	Point pos(10, 10);

	GameObject player1(Point(10, 10), 5, 5, RIGHT, canvasSize, P1);

	while (true) {
		rend.DrawCharacter('O', pos);
		pos.x++;

		player1.Update();
		player1.Draw(rend);

		rend.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

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
