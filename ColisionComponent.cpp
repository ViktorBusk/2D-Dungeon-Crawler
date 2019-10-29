#include "ColisionComponent.h"


ColisionComponent::ColisionComponent(Sprite& sprite, float dir_x, float dir_y)
{
	this->spritePtr = &sprite;
	this->dir_x = dir_x;
	this->dir_y = dir_y;
}

ColisionComponent::~ColisionComponent()
{
}

void ColisionComponent::draw(RenderWindow * window) const
{

}

void ColisionComponent::update(Sprite *characterSprite, const RectangleShape &characterHitbox, const float &dt, const float &multiplier)
{
	//X-component
	//Character
	Vector2f cS1Pos = characterSprite->getPosition();
	Vector2f cS2Pos = characterSprite->getPosition() + Vector2f(characterSprite->getGlobalBounds().width, characterSprite->getGlobalBounds().height);
	
	Vector2f cH1Pos = characterHitbox.getPosition();
	Vector2f cH2Pos = characterHitbox.getPosition() + Vector2f(characterHitbox.getGlobalBounds().width, characterHitbox.getGlobalBounds().height);

	//Tile
	Vector2f t1Pos = this->spritePtr->getPosition();
	Vector2f t2Pos = this->spritePtr->getPosition() + Vector2f(this->spritePtr->getGlobalBounds().width, this->spritePtr->getGlobalBounds().height);


	if (this->dir_x == -1)
	{
		if (cH2Pos.x >= t1Pos.x && cH1Pos.x < t2Pos.x)
		{
			characterSprite->setPosition(Vector2f(t1Pos.x - characterHitbox.getGlobalBounds().width - (cS2Pos.x - cH2Pos.x), characterSprite->getPosition().y));
		}
	}

	if (this->dir_x == 1)
	{
	
	}

	//Y-component
	if (this->dir_y == -1)
	{

	}

	if (this->dir_y == 1)
	{

	}
}
