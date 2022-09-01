#pragma once


class Point {

public:
	int x, y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

};

class Renderer {


	void DrawCharacter(char character, Point position);
	
	void Update() {

	}

};

class DrawCall {
	char character;
	Point position;


};