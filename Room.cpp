#include "Room.h"

Room::Room(IntRect rect)
{
	this->x1 = rect.left;
	this->x2 = rect.left + rect.width;
	this->y1 = rect.top;
	this->y2 = rect.top + rect.height;

	this->centerPoint = Vector2i(floor((x1 + x2) / 2), floor((y1 + y2) / 2));
	this->corridor = false;
}


Room::~Room()
{
}

const bool & Room::intersects(const Room & room)
{
	return (x1 <= room.x2 && x2 >= room.x1 &&
		y1 <= room.y2 && y2 >= room.y1);
}

