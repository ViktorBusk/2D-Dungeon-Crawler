#include "Item.h"


Item::Item(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale, int weight, bool idle) :
	Object(pos, spriteSheet, sheetSize, scale)
{
	this->weight = weight;
	this->idle = idle;
	this->radius = 10;

	//Idle animation
	this->createMovementComponent(100.f, 4.f, 1.f);
	this->angle = rand() % 360 + 1;
	this->angle *= PI / 180;
	this->factor = 10;
	this->first = true;
}


Item::~Item()
{
}

void Item::draw(RenderWindow * window) const
{
	this->Object::draw(window);
}

void Item::update(const float & dt, const float & multiplier)
{
	if (this->idle)
	{
		this->angle += dt*this->factor;
		if (cos(angle) < 0) this->movementComponent->move(0.f, 1.f, dt, multiplier);
		else this->movementComponent->move(0.f, -1.f, dt, multiplier);
	}
	if(!this->first) this->Object::update(dt, multiplier);
	this->first = false;
}

void Item::setIdle()
{
	this->idle = true;
}

void Item::followObject()
{
	this->idle = false;
	this->first = true;
}

void Item::flyToObject(Object * object, const float & dt)
{
	float objAngle = atan2(object->getCenterHitbox().y - this->getCenterHitbox().y, object->getCenterHitbox().x - this->getCenterHitbox().x);
	this->sprite.move(this->suckSpeed*cos(objAngle)*dt, this->suckSpeed*sin(objAngle)*dt);

}
