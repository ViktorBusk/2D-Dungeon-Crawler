#pragma once
#include "Tile.h"
class Floor : public Tile
{
private:
	Vector2i type;

protected:

public:
	Floor(Vector2f pos, Vector2i type);
	virtual ~Floor();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};
