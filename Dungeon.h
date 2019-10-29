#pragma once
#include "Room.h"
#include "Grid.h"

class Dungeon
{
private:
	unsigned int maxNrOfRooms;
	Vector2i roomSize;

	Grid *grid;
	int tilesPerCell;
	std::vector<Room> rooms;
	std::vector<Vector2i> corners;
	
	void init();
	void createRoom(const Room &room);
	void placeRooms();
	void placeCorridors();
	
	void connect2Rooms(const Room &room1, const Room &room2);
	void vCorridor(const Vector2i &startPoint, const Vector2i &endPoint);
	void hCorridor(const Vector2i &startPoint, const Vector2i &endPoint);
	void setCorners();

public:
	
	Dungeon(Vector2i size, float scale, unsigned int maxNrOfRooms, Vector2i RoomSize);
	~Dungeon();
	void generate();
	int rand2i(int a, int b);
	inline const Vector2i &getGridSize() const { return this->grid->getSize(); }
	inline const int &getTilesPerCell() const { return this->tilesPerCell; }
	void draw(RenderWindow *window);
};

