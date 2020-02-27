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
	RectangleShape dynamicRect;
	RectangleShape staticRect;
	RectangleShape* rect;
	bool dynamicComponent;
	std::vector<int> staticHitboxData;
	Color color;
	void draw(RenderWindow * window) const;
	void update(const float &dt, const float &multiplier);
	void setDynamicComponent(int hitboxIndex);
	void setStaticComponent(const Vector2f &start, const Vector2f &size);
	void staticUpdate(const float &dt, const float &multiplier);

	void setIndex(const int &index);
	HitboxComponent(Sprite &sprite, Color color);
	~HitboxComponent();
};

