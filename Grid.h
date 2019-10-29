#pragma once
#include "Cell.h"

using namespace sf;

class Grid
{
private:
	Vector2i size;
	Vector2f worldSize;
	RenderTexture texture;
	Sprite sprite;
	float scale;
	bool worldGrid;

	void init();
	

public:
	Grid(Vector2i size, float scale, bool worldGrid);
	~Grid();

	std::vector<std::vector<Cell>> cells;

	//Accessors
	inline const Vector2i& getSize() const { return this->size; }

	//Modifiers

	//Functions
	void draw(RenderWindow *window);
	void update(const float &dt, const float &multiplier);
	void updateTexture();
};