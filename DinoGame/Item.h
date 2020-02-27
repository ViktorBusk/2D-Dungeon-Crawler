#pragma once
#include "Object.h"

class Item :
	public Object
{
private:
	int weight;
	float angle;
	float factor;
	float suckSpeed;
	bool first;
	float radius;

public:
	bool idle;
	Item(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale, int weight, bool idle);
	virtual ~Item();

	//Functions
	virtual void draw(RenderWindow * window) const;
	virtual void update(const float &dt, const float &multiplier);
	virtual void use(const float & dt, const float & multiplier) = 0;
	void setIdle();
	void followObject();
	void flyToObject(Object * object, const float & dt);
};

