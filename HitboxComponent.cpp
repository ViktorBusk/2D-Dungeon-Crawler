#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite &sprite, const int hitboxIndex, Color color)
{
	this->spritePtr = &sprite;
	this->hitboxIndex = hitboxIndex + 1;
	this->color = color;
	this->rect.setFillColor(color);
	this->staticComponent = false;
}


HitboxComponent::~HitboxComponent()
{
}


void HitboxComponent::setIndex(const int &index)
{
	this->animationIndex = index;
}

void HitboxComponent::draw(RenderWindow * window) const
{
	window->draw(this->rect);
}

void HitboxComponent::update(const float & dt, const float & multiplier)
{
	if (this->staticComponent) this->staticUpdate(dt, multiplier);
	else
	{
		std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[this->hitboxIndex][this->animationIndex].second;
		this->rect.setPosition(this->spritePtr->getPosition().x + hitboxData[2] * SCALE.x, this->spritePtr->getPosition().y + hitboxData[3] * SCALE.y);
		this->rect.setSize(Vector2f(hitboxData[4] * SCALE.x, hitboxData[5] * SCALE.y));
	}
}

void HitboxComponent::setStaticComponent()
{
	this->staticComponent = true;
}

void HitboxComponent::staticUpdate(const float & dt, const float & multiplier)
{
	this->rect.setPosition(this->spritePtr->getPosition());
	this->rect.setSize(Vector2f(this->spritePtr->getGlobalBounds().width, this->spritePtr->getGlobalBounds().height));
}
