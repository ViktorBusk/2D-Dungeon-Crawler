#include "MovementComponent.h"



MovementComponent::MovementComponent(Sprite &sprite, float maxVelocity, float acc, float deAcc)
{
	this->spritePtr = &sprite;
	this->acc = acc;
	this->deAcc = deAcc;
	this->maxVel = maxVelocity;
}


MovementComponent::~MovementComponent()
{

}

const Vector2f & MovementComponent::getVel() const
{
	return this->vel;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt, const float &multiplier)
{
	this->vel.x += this->acc * dir_x * dt * multiplier;
	this->vel.y += this->acc * dir_y * dt * multiplier;
}

void MovementComponent::update(const float & dt, const float & multiplier)
{
	//Horizontal x-movement
	if (this->vel.x > 0.f)
	{
		this->vel.x -= this->deAcc*dt*multiplier;
		if (this->vel.x < 0.f)
			this->vel.x = 0.f;

		if (this->vel.x > this->maxVel)
			this->vel.x = this->maxVel;
	}
	else if (this->vel.x < 0.f)
	{
		this->vel.x += this->deAcc*dt*multiplier;
		if (this->vel.x > 0.f)
			this->vel.x = 0.f;

		if (this->vel.x < -this->maxVel)
			this->vel.x = -this->maxVel;
	}

	//Vertical y-movement
	if (this->vel.y > 0.f)
	{
		this->vel.y -= this->deAcc*dt*multiplier;
		if (this->vel.y < 0.f)
			this->vel.y = 0.f;

		if (this->vel.y > this->maxVel)
			this->vel.y = this->maxVel;
	}
	else if (this->vel.y < 0.f)
	{
		this->vel.y += this->deAcc*dt*multiplier;
		if (this->vel.y > 0.f)
			this->vel.y = 0.f;

		if (this->vel.y < -this->maxVel)
			this->vel.y = -this->maxVel;
	}

	this->spritePtr->move(this->getClampedMagVel()*dt);
}

const Vector2f MovementComponent::getClampedMagVel()
{
	float rotation = atan2(this->vel.y, this->vel.x);
	Vector2f clampMagnitudeVel(abs(this->vel.x)*cos(rotation), abs(this->vel.y)*sin(rotation));
	return clampMagnitudeVel;
}
