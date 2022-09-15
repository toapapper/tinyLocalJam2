// tinyLocalJam2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "renderer.h"
#include <chrono>
#include <thread>
#include "GameObject.h"
#include "Apples.h"
#include "windows.h"

#define ARENA_WIDTH 20
#define ARENA_HEIGHT 20

void Game();
void AnimateDeadPlayer(GameObject& aPlayer, GameObject& anotherPlayer, Renderer& aRend);

bool playing = true;
int p1Wins = 0;
int p2Wins = 0;

const Point arenaSize(ARENA_WIDTH, ARENA_HEIGHT);


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
	Renderer rend(arenaSize);
	rend.ClearScreen();

	int hyperMode = 0;

	std::cout << "**********WELCOME TO SNAKE FORTNITE BATTLE ROYAL!***********" << std::endl << std::endl;

	if (p1Wins > 0 || p2Wins > 0)
	{
		//\x1B[36mTEXTHÄR\033[0m
		std::cout << "\nWins: \x1B[36m P1: " << p1Wins << "\033[0m \x1B[33m P2: " << p2Wins << "\033[0m" << '\n' << std::endl;
	}

	std::cout << "\n ---Menu:---" << std::endl;
	std::cout << "1. \x1B[36mPlay!!!!\033[0m" << std::endl;
	std::cout << "2. \x1B[91mHYPER MODE!!!!\033[0m (play 10 rounds back to back)" << std::endl;
	std::cout << "3. Instructions" << std::endl;
	std::cout << "4. \x1B[32mExit\033[0m" << std::endl;
	
	int input;
	std::cin >> input;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}
	else if (input == 1)
	{
		//Just continue
	}
	else if (input == 2)
	{
		hyperMode = 10;
	}
	else if (input == 3)
	{
		std::cout << "INSTRUCTIONS: " << std::endl;
		std::cout << "P1 \x1B[36m(Oooooo, top left)\033[0m controls:movement = WASD" << std::endl;
		std::cout << "			dash = Left shift" << std::endl << std::endl;
		std::cout << "P2 \x1B[33m(Xxxxxx, bottom rigth)\033[0m controls:movement = arrow keys (or IJKL)" << std::endl;
		std::cout << "			dash = Right shift" << std::endl;
		std::cout << "-SPACE to pause\n" << std::endl;
		std::cout << "-You die when you bash your head into anything.\n" << std::endl;
		std::cout << "-Try to get in the way of each other. The one who lives, wins\n" << std::endl;
		std::cout << "-Eat apples to grow larger\n" << std::endl;
		std::cout << "-The dash jumps you forward by 5 steps instantly.\n" << std::endl;
		std::cout << "-Dash is only available after eating an apple. To dash again you need to eat another apple\n" << std::endl;
		std::cout << "\n\n\n\n\x1B[90mA tip for the skilled player: \nThe drawn border is one tile too small in all directions \nmeaning that you can move hidden below the wall.\033[0m" << std::endl;
		system("pause");
		return;
	}
	else if (input == 4)
	{
		playing = false;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}

	std::cin.clear();
	std::cin.ignore(10000, '\n');

	//STart game after this

	AppleEngine apples(rend);
	GameObject player1(Point(5, 5), 5, 5, RIGHT, arenaSize, P1, apples);
	GameObject player2(Point(ARENA_WIDTH - 5, ARENA_HEIGHT - 5), 5, 5, LEFT, arenaSize, P2, apples);

	int maxDelay = 100, minDelay = 50;
	unsigned char gameSpeed = maxDelay;

	while (true)
	{
		auto start = std::chrono::steady_clock::now();
		//player1.Update(player2);
		player2.Update(player1);
		player1.Draw(rend);
		player2.Draw(rend);
		apples.Draw();

		if (GetAsyncKeyState(VK_SPACE)) //Pause
		{
			system("pause");
		}

		if (player1.dead && player2.dead)
		{
			//rend.ClearScreen();
			std::cout << "\x1B[32m==================No one WINS! ==================\033[0m" << std::endl;
			std::cout << "Press ESC to continue" << std::endl;
			AnimateDeadPlayer(player1, player2, rend);
			if (hyperMode > 0)
			{
				hyperMode--;

				apples.Reset();
				player1.Reset();
				player2.Reset();
			}
			else
			{
				break;
			}
		}
		else if (player1.dead)
		{
			p2Wins++;
			//rend.ClearScreen();
			std::cout << "\x1B[33m==================PLAYER 2 WINS! (The X-snake) ==================\033[0m" << std::endl;
			if (hyperMode > 0)
			{
				std::string temp = (hyperMode >= 10) ? "" : " ";
				std::cout << "Games left: " << temp << hyperMode << " Wins: \x1B[36m P1: " << p1Wins << "\033[0m \x1B[33m P2: " << p2Wins << "\033[0m" << std::endl;
			}
			std::cout << "Press ESC to continue" << std::endl;
			AnimateDeadPlayer(player1, player2, rend);
			if (hyperMode > 0)
			{
				hyperMode--;

				apples.Reset();
				player1.Reset();
				player2.Reset();
			}
			else
			{
				break;
			}
		}
		else if (player2.dead)
		{
			p1Wins++;
			std::cout << "\x1B[36m==================PLAYER 1 WINS! (The O-snake) ==================\033[0m" << std::endl;
			if (hyperMode > 0)
			{
				std::string temp = (hyperMode >= 10) ? "" : " ";
				std::cout << "Games left: " << temp << hyperMode << " Wins: \x1B[36m P1: " << p1Wins << "\033[0m \x1B[33m P2: " << p2Wins << "\033[0m" << std::endl;
			}
			std::cout << "Press ESC to continue" << std::endl;
			AnimateDeadPlayer(player2, player1, rend);
			if (hyperMode > 0)
			{
				hyperMode--;

				apples.Reset();
				player1.Reset();
				player2.Reset();
			}
			else
			{
				break;
			}
		}

		if (gameSpeed > minDelay)
		{
			gameSpeed--;
		}

		apples.Update();
		rend.Update();

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
		std::this_thread::sleep_for(std::chrono::milliseconds(gameSpeed)-duration);
	}

	//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void AnimateDeadPlayer(GameObject& aPlayer,GameObject& anotherPlayer, Renderer& aRend)
{
	while (true)
	{
		aPlayer.Draw(aRend);
		anotherPlayer.Draw(aRend);
		aRend.Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
	}
}