#pragma once
#include "utils.hpp"

using namespace sf;

class MovementComponent
{
private:
	Sprite* spritePtr;
	float maxVel;
	Vector2f vel;
	float acc;
	float deAcc;

public:
	MovementComponent(Sprite &sprite, float maxVelocity, float acc, float deAcc);
	virtual ~MovementComponent();

	//Accessors
	const Vector2f& getVel() const;

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt, const float &multiplier);
	void update(const float& dt, const float &multiplier);
	const Vector2f getClampedMagVel();
};

