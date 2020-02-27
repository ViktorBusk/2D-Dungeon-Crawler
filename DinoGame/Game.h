#pragma once
#include "Hero.h"
#include "Dungeon.h"
#include "AllEnemies.h"
#include "utils.hpp"
#include "Editor.h"
#include "PreLoad.h"
#include "Weapon.h"
#include "Wall.h"
#include "Floor.h"

using namespace sf;

class Game
{

private:
	RenderWindow *window;
	Clock clock;
	Font *font;
	Dungeon *map;
	float FPS;
	Grid *worldGrid;

	struct LevelData {
		float mapScale = 8;
		Vector2i mapSize = Vector2i(50, 50);
		unsigned int maxNrOfRooms = 200;
		Vector2i roomSize = Vector2i(3, 5);
	};

	Hero *player;
	std::vector<Object*> entites;
	std::vector<Tile*> staticEntities;

	//Camera
	Object* cameraFollow;

	Editor* editor;

	LevelData levelData;
	float dt;
	float multiplier;
	float framerateLimit;
	void init();
	void initEditor();
	void initGrid();
	void startLoop();
	void pollEvents();
	void updateClock();
	void printFPS();
	void updateView(const Vector2f &targetPos);
	void ensureBounds(Object* entity);
	void clearEntityVec();
	void addObjectToWorldGrid(Object* object);
	void clearWorldGrid();

	
public:
	Game();
	~Game();
	void start();
};
