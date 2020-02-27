#pragma once
#include "utils.hpp"

using namespace sf;

class ColisionComponent
{
private:
	Sprite* spritePtr;
	bool outwards;
	bool left;
	bool right;
	bool top;
	bool bottom;
	

public:
	ColisionComponent(Sprite& sprite, bool outwards, bool left, bool right, bool top, bool bottom);
	~ColisionComponent();

	void draw(RenderWindow * window) const;
	void update(Sprite *characterSprite, const RectangleShape &characterHitbox, const float &dt, const float &multiplier);
};


