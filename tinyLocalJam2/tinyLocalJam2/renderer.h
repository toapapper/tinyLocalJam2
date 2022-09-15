#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>




class Point {

public:
	int x, y;

	constexpr Point(): x(0), y(0){}

	Point(int x, int y) noexcept:x(x),y(y) {}
	Point(const Point& other) noexcept:x(other.x), y(other.y) {}
	Point(Point&& other) noexcept:x(other.x),y(other.y){}
	~Point() = default;

	const bool operator==(const Point& rhs) noexcept
	{
		return rhs.x == x && rhs.y == y;
	}

	Point& operator=(const Point& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	Point& operator=(Point&& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}

};


class Renderer {

private:
	Point _size;
	int _fontSize = 10;

	char* pixels;
	HANDLE hOut;


	std::string* str;


	void ClearDrawCalls() {
		for (int i = 0; i < _size.x * _size.y; i++) {
			pixels[i] = ' ';
		}
	}


public:
	Renderer(Point size){
		_size = size;
		str = new std::string(5000, ' ');


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

	void ClearScreen() {
		system("cls");
	}

	void DrawCharacter(char character, Point position) {
		if (position.x < 0 || position.x >= _size.x || position.y < 0 || position.y >= _size.y)
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
		str->clear();

		cls();

		//Draw everything
		for (int y = 0; y < _size.y; y++) {
			for (int x = 0; x < _size.x; x++) {
				if (x == 0 || x == _size.x - 1 || y == 0 || y == _size.y - 1) {
					str->append("\033[3;100;30m");
					str->push_back(' ');
					str->push_back(' ');
					str->append("\033[0m");
				}
				else {
					GameSpecificCharCheck(*str, pixels[x + _size.x * y]);
					str->push_back(' ');
				}
			}
			str->push_back('\n');
		}
		std::cout << *str << std::endl;
		str->clear();

		ClearDrawCalls();
	}

	//Ugly hack to add colour to this game
	void GameSpecificCharCheck(std::string& aStr, char character)
	{
		if (character == 'a' || character == '¤' || character == '*')
		{
			aStr.append("\x1B[31m"); //bright red
			aStr.push_back(character);
			aStr.append("\033[0m");
		}
		else if (character == 'x')
		{
			aStr.append("\x1B[33m"); //yellow
			aStr.push_back(character);
			aStr.append("\033[0m");
		}
		else if (character == 'X')
		{
			aStr.append("\x1B[93m"); //bright yellow
			aStr.push_back(character);
			aStr.append("\033[0m");
		}
		else if (character == 'o')
		{ 
			aStr.append("\x1B[36m"); //cyan
			aStr.push_back(character);
			aStr.append("\033[0m");
		}
		else if (character == 'O')
		{
			aStr.append("\x1B[96m"); //bright cyan
			aStr.push_back(character);
			aStr.append("\033[0m");
		}
		else
		{
			aStr.push_back(character);
		}
	}

};

