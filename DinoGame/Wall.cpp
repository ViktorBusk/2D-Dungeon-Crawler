#include "Wall.h"

Wall::Wall(Vector2f pos, Vector2i type) :
	Tile(pos, PreLoad::Textures::walls, Vector2i(8, 7), SCALE)
{
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type.x][this->type.y]);
	
	//Hitbox
	this->createSpriteHitboxComponent(Color(0, 255, 255, 125));

	//Colision
	//this->createColisionComponent(false, false, true, true, false);
	this->colisionIndex = 1000000000;
	this->zIndex = this->colisionIndex;
	this->fixedZIndex = true;
}

Wall::~Wall()
{
}

void Wall::draw(RenderWindow * window) const
{
	this->Tile::draw(window);
	window->draw(this->sprite);
}

void Wall::update(const float & dt, const float & multiplier)
{
	this->Tile::update(dt, multiplier);
}

