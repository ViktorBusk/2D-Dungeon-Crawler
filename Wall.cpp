#include "Wall.h"

Wall::Wall(Vector2f pos, Vector2i type, const float dir_x, const float dir_y) :
	Tile(pos, PreLoad::Textures::walls, Vector2i(8, 7), SCALE)
{
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type.x][this->type.y]);
	
	//Hitbox
	this->createHitboxComponent(0, Color(0, 255, 255, 125));
	this->hitboxComponent->setStaticComponent();

	//Colision
	this->createColisionComponent(dir_x, dir_y);
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

