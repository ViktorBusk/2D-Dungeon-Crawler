#include "Skelet.h"

Skelet::Skelet(Vector2f pos) :
	Enemy(pos, PreLoad::Textures::skelet, Vector2i(8, 1), SCALE)
{
	//Hitbox
	this->createHitboxComponent(Color(255, 0, 0, 125));
	std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[5][0].second;
	this->hitboxComponent->setStaticComponent(Vector2f(hitboxData[2], hitboxData[3]), Vector2f(hitboxData[4], hitboxData[5]));
	this->hitboxComponent->setDynamicComponent(5);

	this->createMovementComponent(200.f, 5.f, FRICTION);
}


Skelet::~Skelet()
{

}


void Skelet::draw(RenderWindow * window) const
{
	this->Enemy::draw(window);
}

void Skelet::update(const float & dt, const float & multiplier)
{
	this->Enemy::update(dt, multiplier);
}

