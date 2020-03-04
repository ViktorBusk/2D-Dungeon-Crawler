#pragma once
#include "GUI.h"
#include "AllEntities.h"
#include "AllTiles.h"

class Spawner : public GUI
{
private:
	void init();
	void initType();
	std::string type;
	Vector2i types;
	bool shouldPickUp;
	std::vector<std::vector<IntRect>> textureRects;
	
	//Static spawner variables
	static std::string chosenType;
	static Vector2i chosenTypes;
	static Vector2f constSpawnerPos;
	static Vector2f constSpawnerTextPos;
	static Vector2f spriteRect;
	static Sprite* spritePtr;
	static Vector2f* constSizePtr;
	static Text *chosenText;
	static bool inited;
	static bool shouldSpawn;
	
protected:

public:
	static unsigned int spawnAmount;
	static void drawCurrentType(RenderWindow *window);
	static void changeCurrentType(Spawner* spawner);
	static void updateSpawn(const float & dt, const float & multiplier, const Vector2f & mousePos);
	Spawner(Vector2f pos, Texture* texture, std::string type, GUI* parent, Vector2i types = Vector2i(0, 0));
	virtual ~Spawner();

	virtual void show();
	virtual void hide();
	virtual void draw(RenderWindow * window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
	static void spawn(const Vector2f &pos);
	
};

	

