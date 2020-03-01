#pragma once
#include "Enemy.h"
class Skelet : public Enemy
{
private:

protected:

public:
	Skelet(Vector2f pos);
	virtual ~Skelet();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

