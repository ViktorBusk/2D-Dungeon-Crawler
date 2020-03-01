#include "Demon.h"

Demon::Demon(Vector2f pos) :
	Enemy(pos, PreLoad::Textures::demon, Vector2i(8, 1), SCALE)
{
	//Hitbox
	this->createHitboxComponent(Color(255, 0, 0, 125));
	std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[2][0].second;
	this->hitboxComponent->setStaticComponent(Vector2f(hitboxData[2], hitboxData[3]), Vector2f(hitboxData[4], hitboxData[5]));
	this->hitboxComponent->setDynamicComponent(2);

	this->createMovementComponent(100.f, 4.f, FRICTION);
}


Demon::~Demon()
{

}


void Demon::draw(RenderWindow * window) const
{
	this->Enemy::draw(window);
}

void Demon::update(const float & dt, const float & multiplier)
{
	this->Enemy::update(dt, multiplier);
}

