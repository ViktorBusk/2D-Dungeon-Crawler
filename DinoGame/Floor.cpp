#include "Floor.h"


Floor::Floor(Vector2f pos, Vector2i type) :
	Tile(pos, PreLoad::Textures::floors, Vector2i(4, 4), SCALE)
{
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type.x][this->type.y]);
	this->createSpriteHitboxComponent(Color(0, 255, 255, 125));
	this->shouldColide = false;
	this->zIndex = 0;
	this->fixedZIndex = true;
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

