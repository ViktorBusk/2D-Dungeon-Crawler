#pragma once
#include "Enemy.h"
class Demon : public Enemy
{
private:

protected:

public:
	Demon(Vector2f pos);
	virtual ~Demon();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

