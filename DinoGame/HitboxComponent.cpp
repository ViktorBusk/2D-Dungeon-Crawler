#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite &sprite, Color color)
{
	this->spritePtr = &sprite;
	this->color = color;
	this->dynamicRect.setFillColor(color);
	this->staticRect.setFillColor(color);
	this->dynamicComponent = false;
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
	window->draw(*this->rect);
}

void HitboxComponent::update(const float & dt, const float & multiplier)
{
	this->staticUpdate(dt, multiplier);

	//Dynamic rect
	if (this->dynamicComponent)
	{
		std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[this->hitboxIndex][this->animationIndex].second;
		this->dynamicRect.setPosition(this->spritePtr->getPosition().x + hitboxData[2] * SCALE.x, this->spritePtr->getPosition().y + hitboxData[3] * SCALE.y);
		this->dynamicRect.setSize(Vector2f(hitboxData[4] * SCALE.x, hitboxData[5] * SCALE.y));
	}
}

void HitboxComponent::setDynamicComponent(int hitboxIndex)
{
	this->hitboxIndex = hitboxIndex;
	this->dynamicComponent = true;
	this->rect = &this->dynamicRect;
}

void HitboxComponent::setStaticComponent(const Vector2f &start, const Vector2f &size)
{
	this->staticHitboxData.push_back(start.x);
	this->staticHitboxData.push_back(start.y);
	this->staticHitboxData.push_back(size.x);
	this->staticHitboxData.push_back(size.y);

	this->staticRect.setPosition(Vector2f(this->spritePtr->getPosition().x + staticHitboxData[0]*SCALE.x, this->spritePtr->getPosition().y + staticHitboxData[1] * SCALE.y));
	this->staticRect.setSize(Vector2f(staticHitboxData[2] * SCALE.x, staticHitboxData[3] * SCALE.y));
	this->rect = &this->staticRect;
}

void HitboxComponent::staticUpdate(const float & dt, const float & multiplier)
{
	this->staticRect.setPosition(Vector2f(this->spritePtr->getPosition().x + staticHitboxData[0] * SCALE.x, this->spritePtr->getPosition().y + staticHitboxData[1] * SCALE.y));
}
