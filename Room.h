#pragma once
#include "utils.hpp"

using namespace sf;

class Room : IntRect
{
private:
	

public:
	int x1;
	int x2;
	int y1;
	int y2;
	bool corridor;
	Vector2i centerPoint;
	Room(IntRect rect);
	~Room();

	//Accessors

	//Modifiers

	//Functions
	const bool &intersects(const Room &room);
};

