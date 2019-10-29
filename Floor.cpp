#include "Floor.h"


Floor::Floor(Vector2f pos, Vector2i type) :
	Tile(pos, PreLoad::Textures::floors, Vector2i(4, 4), SCALE)
{
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type.x][this->type.y]);
}


Floor::~Floor()
{

}

void Floor::draw(RenderWindow * window) const
{
	this->Tile::draw(window);
	window->draw(this->sprite);
}

void Floor::update(const float & dt, const float & multiplier)
{
	this->Tile::update(dt, multiplier);
}

