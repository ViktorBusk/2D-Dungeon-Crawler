#include "BigZombie.h"

BigZombie::BigZombie(Vector2f pos, Texture *spriteSheet) :
	Enemy(pos, spriteSheet, Vector2i(8, 1), SCALE)
{
	//Hitbox
	this->createHitboxComponent(0, Color(255, 0, 0, 125));
}


BigZombie::~BigZombie()
{

}


void BigZombie::draw(RenderWindow * window) const
{
	this->Enemy::draw(window);
}

void BigZombie::update(const float & dt, const float & multiplier)
{
	this->Enemy::update(dt, multiplier);
}

