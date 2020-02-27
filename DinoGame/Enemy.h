#pragma once
#include "Character.h"
class Enemy : public Character
{
private:
	void setAnimations();
	std::string trollingDirs[9];
	std::string dir;
	float trolling;
	const float cap = 100;

protected:

public:
	Enemy(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale);
	virtual ~Enemy();

	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

