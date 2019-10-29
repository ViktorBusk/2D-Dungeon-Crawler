#pragma once
#include "Character.h"
class Hero : public Character
{
private:
	void setAnimations();

protected:
	

public:
	Hero(Vector2f pos, Texture *spriteSheet);
	virtual ~Hero();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float &multiplier);
};

