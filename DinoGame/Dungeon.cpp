#include "Dungeon.h"
#include "Graph.h"

Dungeon::Dungeon(Vector2i size, float scale, unsigned int maxNrOfRooms, Vector2i roomSize)
{
	this->grid = new Grid(size, scale, false);
	this->maxNrOfRooms = maxNrOfRooms;
	this->roomSize = roomSize;
	this->tilesPerCell = 5;
}

Dungeon::~Dungeon()
{
	delete this->grid;
}

void Dungeon::init()
{
	
}

int Dungeon::rand2i(int a, int b)
{
	int r = rand() % 2;
	if (r == 0)
		return a;
	else
		return b;
}

void Dungeon::placeRooms()
{
	for(int i = 0; i <this->maxNrOfRooms; i++)
	{	
		int width = this->roomSize.x + (rand() % (roomSize.y - roomSize.x + 1));
		int heigth = this->roomSize.x + (rand() % (roomSize.y - roomSize.x + 1));
		int x = rand() % (this->grid->getSize().x - width - 1) + 1;
		int y = rand() % (this->grid->getSize().y - heigth - 1) + 1;

		Room newRoom(IntRect(x, y, width, heigth));

		bool failed = false;
		for (auto &otherRoom : this->rooms)
		{
			if (newRoom.intersects(otherRoom))
			{
				failed = true;
				break;
			}
		}
		if (!failed)
		{
			this->createRoom(newRoom);
			this->rooms.push_back(newRoom);
		}
	}
}

void Dungeon::placeCorridors()
{
	Graph g(rooms.size());
	unsigned int jStart = 0;
	for (size_t i = 0; i < rooms.size(); i++)
	{
		for (size_t j = jStart; j < rooms.size(); j++)
		{
			if (&rooms[i] == &rooms[j]) continue;
			int weight = Utils::distance2i(rooms[i].centerPoint, rooms[j].centerPoint);
			g.AddWeightedEdge(i, j, weight);
		}
		jStart++;
	}
	g.kruskal();
	for (size_t i = 0; i < g.getT().size(); i++)
	{
		int i1 = g.getT()[i].second.first;
		int i2 = g.getT()[i].second.second;
		this->connect2Rooms(this->rooms[i1], this->rooms[i2]);
	}
}

void Dungeon::generate()
{
	//Place all Rooms
	this->placeRooms();
	//Use Kruskal's to find MST with the rooms as nodes
	this->placeCorridors();
	//Set the type for each corner
	this->setCorners();
	//Update the texture for the gridMap
	this->grid->updateTexture();
}

void Dungeon::connect2Rooms(const Room &room1,const Room &room2)
{
	Vector2i intersectPoint;
	intersectPoint.x = rand2i(room1.centerPoint.x, room2.centerPoint.x);
	if (intersectPoint.x = room1.centerPoint.x) intersectPoint.y = room2.centerPoint.y;
	else intersectPoint.y = room1.centerPoint.y;

	if (intersectPoint.x == room1.centerPoint.x)
	{
		this->vCorridor(room1.centerPoint, intersectPoint);
		this->hCorridor(intersectPoint, room2.centerPoint);
	}
	else
	{
		this->hCorridor(room1.centerPoint, intersectPoint);
		this->vCorridor(intersectPoint, room2.centerPoint);
	}
	this->corners.push_back(intersectPoint);
	this->grid->cells[intersectPoint.x][intersectPoint.y].setType(Cell::corner);
}

void Dungeon::vCorridor(const Vector2i & startPoint, const Vector2i & endPoint)
{
	int start;
	int end;
	if (startPoint.y < endPoint.y)
	{
		start = startPoint.y;
		end = endPoint.y;
	}
	else
	{
		start = endPoint.y;
		end = startPoint.y;
	}

	for (size_t y = start+1; y < end; y++)
	{
		Cell* c = &this->grid->cells[startPoint.x][y];
		//Vertical path
		if (c->getType() == Cell::none)
			c->setType(Cell::vCorridor);
	}
}

void Dungeon::hCorridor(const Vector2i & startPoint, const Vector2i & endPoint)
{
	int start;
	int end;
	if (startPoint.x < endPoint.x)
	{
		start = startPoint.x;
		end = endPoint.x;
	}
	else
	{
		start = endPoint.x;
		end = startPoint.x;
	}
	for (size_t x = start+1; x < end; x++)
	{
		Cell* c = &this->grid->cells[x][startPoint.y];
		//Horizontal path
		if (c->getType() == Cell::none)
			c->setType(Cell::hCorridor);
	}
}

void Dungeon::setCorners()
{
	for (Vector2i &corner : corners)
	{
		Cell* c = &this->grid->cells[corner.x][corner.y];
		Cell* U = &this->grid->cells[corner.x][corner.y-1];
		Cell* D = &this->grid->cells[corner.x][corner.y+1];
		Cell* L = &this->grid->cells[corner.x-1][corner.y];
		Cell* R = &this->grid->cells[corner.x+1][corner.y];

		//Corners
		if (R->getType() != Cell::none && U->getType() != Cell::none)
			c->setType(Cell::vR_hUp);
		if (L->getType() != Cell::none && U->getType() != Cell::none)
			c->setType(Cell::vL_hUp);
		if (R->getType() != Cell::none && D->getType() != Cell::none)
			c->setType(Cell::vR_hD);
		if (L->getType() != Cell::none && D->getType() != Cell::none)
			c->setType(Cell::vL_hD);
		//3 Openings
		if (L->getType() != Cell::none && U->getType() != Cell::none && R->getType() != Cell::none)
			c->setType(Cell::vL_hUp_vR);
		if (U->getType() != Cell::none && R->getType() != Cell::none && D->getType() != Cell::none)
			c->setType(Cell::hUp_vR_hD);
		if (L->getType() != Cell::none && D->getType() != Cell::none && R->getType() != Cell::none)
			c->setType(Cell::vL_hD_vR);
		if (U->getType() != Cell::none && L->getType() != Cell::none && D->getType() != Cell::none)
			c->setType(Cell::hUp_vL_hD);
		//4 Openings
		if (U->getType() != Cell::none && L->getType() != Cell::none && D->getType() != Cell::none && R->getType() != Cell::none)
		{
			c->setType(Cell::vR_hUp_hD_vR);
		}
	}
	for (size_t i = 0; i < this->rooms.size(); i++)
	{
		this->createRoom(rooms[i]);
	}
}

void Dungeon::createRoom(const Room &room)
{
	for (size_t x = room.x1; x < room.x2; x++)
	{
		for (size_t y = room.y1; y < room.y2; y++)
		{
			this->grid->cells[x][y].setType(Cell::room);
		}
	}
}

void Dungeon::draw(RenderWindow * window)
{
	this->grid->draw(window);
}

void Dungeon::setPosition(const Vector2f & pos)
{
	this->grid->setPosition(pos);
}

