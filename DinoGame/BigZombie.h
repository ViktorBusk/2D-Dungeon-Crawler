#pragma once
#include "Enemy.h"
class BigZombie : public Enemy
{
private:

protected:

public:
	BigZombie(Vector2f pos);
	virtual ~BigZombie();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

