#pragma once
#include "GUI.h"
#include "AllEntities.h"

class Spawner : public GUI
{
private:
	void init();
	void initType();
	std::string type;
	bool shouldSpawn;
	std::vector<Object*> *entitesPtr;
	std::vector<std::vector<IntRect>> textureRects;

protected:

public:
	static unsigned int spawnAmount;
	Spawner(Vector2f pos, Texture* texture, std::string type, GUI* parent, std::vector<Object*> *entitesPtr);
	virtual ~Spawner();

	virtual void show();
	virtual void hide();
	virtual void draw(RenderWindow * window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
	void spawn(const Vector2f &pos);
	
};

	

