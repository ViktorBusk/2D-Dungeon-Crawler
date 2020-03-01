#include "BigZombie.h"

BigZombie::BigZombie(Vector2f pos) :
	Enemy(pos, PreLoad::Textures::bigZombie, Vector2i(8, 1), SCALE)
{
	//Hitbox
	this->createHitboxComponent(Color(255, 0, 0, 125));
	std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[1][0].second;
	this->hitboxComponent->setStaticComponent(Vector2f(hitboxData[2], hitboxData[3]), Vector2f(hitboxData[4], hitboxData[5]));
	this->hitboxComponent->setDynamicComponent(1);

	this->createMovementComponent(100.f, 4.f, FRICTION);
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

