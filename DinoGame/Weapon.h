#pragma once
#include "Item.h"

class Weapon :
	public Item
{
private:
	int type;
	int damage;

protected:
	Texture *spriteSheet;
	RectangleShape attackHitbox;

public:
	Weapon(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale, int type, int damage, int weight, bool idle);
	virtual ~Weapon();

	//Functions
	virtual void use(const float & dt, const float & multiplier);
	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
};

