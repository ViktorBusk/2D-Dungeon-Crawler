#pragma once
#include "utils.hpp"

using namespace sf;

class Slider
{
private:
	Vector2f smallRectPos;
	Vector2f bigRectPos;
	Vector2f rect;
	RectangleShape bigRect;
	RectangleShape smallRect;
	bool adjusting = false;
	float *value;
	float copyValue;
	Vector2f interval;

	Text text;

public:
	Slider(Vector2f pos, float *value, Vector2f interval, Font *font);
	~Slider();

	void draw(RenderWindow *window);
	void update();
};