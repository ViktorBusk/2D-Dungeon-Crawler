#include "Weapon.h"

Weapon::Weapon(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale, int type, int damage, int weight, bool idle) :
	Item(pos, spriteSheet, sheetSize, scale, weight, idle)
{
	//Sprite
	this->type = type;
	this->sprite.setTextureRect(this->textureRects[this->type][0]);

	//Stats
	this->damage = damage;

	//Hitbox
	this->createHitboxComponent(Color(0, 0, 255, 125));
	std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[3][this->type].second;
	this->hitboxComponent->setStaticComponent(Vector2f(hitboxData[2], hitboxData[3]), Vector2f(hitboxData[4], hitboxData[5]));
}

Weapon::~Weapon()
{

}

void Weapon::use(const float & dt, const float & multiplier)
{

}

void Weapon::draw(RenderWindow * window) const
{
	this->Item::draw(window);
	window->draw(this->sprite);
}

void Weapon::update(const float & dt, const float & multiplier)
{
	this->sprite.setTextureRect(this->textureRects[this->type][0]);
	this->Item::update(dt, multiplier);
}