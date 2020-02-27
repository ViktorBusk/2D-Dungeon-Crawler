#include "Tile.h"



Tile::Tile(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale) :
	Object(pos, spriteSheet, sheetSize, scale)
{

}


Tile::~Tile()
{
}

void Tile::draw(RenderWindow * window) const
{
	this->Object::draw(window);
}

void Tile::update(const float & dt, const float & multiplier)
{
	this->Object::update(dt, multiplier);
}
