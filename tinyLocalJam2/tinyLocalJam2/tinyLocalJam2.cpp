// tinyLocalJam2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "renderer.h"
#include <chrono>
#include <thread>
#include "GameObject.h"
#include "Apples.h"
#include "windows.h"

void Game();
void AnimateDeadPlayer(GameObject& aPlayer, GameObject& anotherPlayer, Renderer& aRend);

bool playing = true;
int p1Wins = 0;
int p2Wins = 0;

int main()
{
	SetConsoleOutputCP(1252);
	while (playing)
	{
		Game();
	}
}



void Game()
{

	Point canvasSize(30, 30);
	Renderer rend(canvasSize);
	rend.ClearScreen();

	int hyperMode = 0;

	std::cout << "************WELCOME TO SNAKE FORTNITE BATTLE ROYAL!****************" << std::endl << std::endl;

	if (p1Wins > 0 || p2Wins > 0)
	{
		//\x1B[36m(Oooooo, top left)\033[0m
		std::cout << "\nWins: \x1B[36m P1: " << p1Wins << "\033[0m \x1B[33m P2: " << p2Wins << "\033[0m" << '\n' << std::endl;
	}

	std::cout << "P1 \x1B[36m(Oooooo, top left)\033[0m controls:movement = WASD" << std::endl;
	std::cout << "			dash = Left shift" << std::endl << std::endl;
	std::cout << "P2 \x1B[33m(Xxxxxx, bottom rigth)\033[0m controls:movement = arrow keys" << std::endl;
	std::cout << "			dash = Right shift" << std::endl << std::endl;

	std::cout << "Dash is only available after eating an apple. \nTo dash again you need to eat another apple" << std::endl;
	std::cout << "\n\nwrite anything to start or write x to exit" << std::endl;
	std::cout << "write h to enter \x1B[91mHYPER MODE!!!!\033[0m" << std::endl;
	
	char b;
	std::cin >> b;
	if (b == 'x')
	{
		playing = false;
		return;
	}
	else if (b == 'h')
	{
		hyperMode = 10;
	}
		

	//STart game after this

	AppleEngine* apples = new AppleEngine(rend, canvasSize);



	GameObject player1(Point(5, 5), 5, 5, RIGHT, canvasSize, P1, apples);
	GameObject player2(Point(25, 25), 5, 5, LEFT, canvasSize, P2, apples);

	int maxDelay = 100, minDelay = 50;
	unsigned char gameSpeed = maxDelay;

	while (true)
	{

		player1.Update();
		player2.Update();
		player1.PlayerCollisionCheck(player2);
		player2.PlayerCollisionCheck(player1);
		player1.Draw(rend);
		player2.Draw(rend);
		apples->Draw();

		if (player1.dead && player2.dead)
		{
			//rend.ClearScreen();
			std::cout << "\x1B[32m==================No one WINS! ==================\033[0m" << std::endl;
			std::cout << "write anything to continue" << std::endl;
			break;
		}
		else if (player1.dead)
		{
			p2Wins++;
			//rend.ClearScreen();
			std::cout << "\x1B[33m==================PLAYER 2 WINS! (The X-snake) ==================\033[0m" << std::endl;
			std::cout << "write anything to continue" << std::endl;
			AnimateDeadPlayer(player1, player2, rend);
			break;
		}
		else if (player2.dead)
		{
			p1Wins++;
			//rend.ClearScreen();
			std::cout << "\x1B[36m==================PLAYER 1 WINS! (The O-snake) ==================\033[0m" << std::endl;
			std::cout << "write anything to continue" << std::endl;
			AnimateDeadPlayer(player2, player1, rend);
			break;
		}
		//while (true)
		//{
		//	//TODO: Animate characters after game over...


		//}
		if (gameSpeed > minDelay)
		{
			gameSpeed--;
		}

		apples->Update();
		rend.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed));
	}

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	std::cout << '\a' << std::endl;

	char a;
	std::cin >> a;
}

void AnimateDeadPlayer(GameObject& aPlayer,GameObject& anotherPlayer, Renderer& aRend)
{
	while (true)
	{
		aPlayer.Draw(aRend);
		anotherPlayer.Draw(aRend);
		aRend.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			break;
		}
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
