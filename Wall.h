#pragma once
#include "Tile.h"
#include "Character.h"

class Wall : public Tile
{
private:
	Vector2i type;

protected:

public:
	Wall(Vector2f pos, Vector2i type, const float dir_x, const float dir_y);
	virtual virtual ~Wall();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};


