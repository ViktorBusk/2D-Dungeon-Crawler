#pragma once
#include "utils.hpp"

using namespace sf;

class ColisionComponent
{
private:
	Sprite* spritePtr;
	float dir_x;
	float dir_y;

public:
	ColisionComponent(Sprite& sprite, float dir_x, float dir_y);
	~ColisionComponent();

	void draw(RenderWindow * window) const;
	void update(Sprite *characterSprite, const RectangleShape &characterHitbox, const float &dt, const float &multiplier);
};


