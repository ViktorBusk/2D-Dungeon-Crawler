#include "Wall.h"

Wall::Wall(Vector2f pos, Vector2i type) :
	Tile(pos, PreLoad::Textures::walls, Vector2i(8, 7), SCALE)
{
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type.x][this->type.y]);
	
	//Hitbox
	this->createHitboxComponent(Color(0, 255, 255, 125));
	this->hitboxComponent->setStaticComponent(Vector2f(0.f, 0.f), Vector2f(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height));

	//Colision
	this->createColisionComponent(false, false, true, false, true);
	this->fixedZIndex = true;
	this->zIndex = 1000;
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

