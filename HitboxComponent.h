#pragma once
#include "utils.hpp"
#include "PreLoad.h"

class HitboxComponent
{
private:
	Sprite *spritePtr;
	int hitboxIndex;
	int animationIndex;
	std::vector<std::pair<std::string, std::vector<int>>> *listPtr;

public:
	bool staticComponent;
	RectangleShape rect;
	Color color;
	void draw(RenderWindow * window) const;
	void update(const float &dt, const float &multiplier);
	void setStaticComponent();
	void staticUpdate(const float &dt, const float &multiplier);

	void setIndex(const int &index);
	HitboxComponent(Sprite &sprite, const int hitboxIndex, Color color);
	~HitboxComponent();
};

