#pragma once
#include "Object.h"
class Tile : public Object
{
private:

protected:

public:
	bool solid;
	Tile(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale);
	virtual ~Tile();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

