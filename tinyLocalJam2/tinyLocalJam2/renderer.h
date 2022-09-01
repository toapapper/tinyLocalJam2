#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
//#include <curses.h>




class Point {

public:
	int x, y;

	Point(): x(0), y(0){}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

};




class Renderer {

private:
	Point _size;
	int _fontSize = 10;
	//std::vector<std::vector<char>> drawCalls;

	char* pixels;
	HANDLE hOut;

	void ClearDrawCalls() {
		for (int i = 0; i < _size.x * _size.y; i++) {
			pixels[i] = ' ';
		}
	}


public:
	Renderer(Point size){
		_size = size;

		//Set console window size
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions

		MoveWindow(console, r.left, r.top, 600, 600, TRUE);
		//end 

		setFontSize(10);
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		//init drawCalls
		pixels = new char[_size.x * _size.y];

		ClearDrawCalls();

	}
	~Renderer() {
		delete[] pixels;
	}

	void DrawCharacter(char character, Point position) {
		if (position.x < 0 || position.x > _size.x || position.y < 0 || position.y > _size.y)
			return;

		pixels[_size.x * position.y + position.x] = character;
	}
	
	void setFontSize(int size) {
		static CONSOLE_FONT_INFOEX  fontex;
		fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		
		GetCurrentConsoleFontEx(hOut, 0, &fontex);
		fontex.FontWeight = size;
		fontex.dwFontSize.X = size;
		fontex.dwFontSize.Y = size;
		SetCurrentConsoleFontEx(hOut, NULL, &fontex);
	}

	void cls()
	{
		COORD cursorPosition;
		cursorPosition.X = 0;
		cursorPosition.Y = 0;
		SetConsoleCursorPosition(hOut, cursorPosition);
	}

	

	void Update() {
		std::string str = "";

		cls();

		//Draw everything
		for (int y = -1; y < _size.y + 1; y++) {
			for (int x = -1; x < _size.x + 1; x++) {
				if (x == -1 || x == _size.x || y == -1 || y == _size.y) {
					str.push_back('=');
				}
				else {
					str.push_back(pixels[x + _size.x * y]);
				}
			}
			str.push_back('\n');
		}
		std::cout << str << std::endl;

		ClearDrawCalls();
	}

};

