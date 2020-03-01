#include "ColisionComponent.h"


ColisionComponent::ColisionComponent(Sprite& sprite, bool outwards, bool left, bool right, bool top, bool bottom)
{
	this->outwards = outwards;
	this->spritePtr = &sprite;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

ColisionComponent::~ColisionComponent()
{
}

void ColisionComponent::draw(RenderWindow * window) const
{

}

void ColisionComponent::update(Sprite *characterSprite, const RectangleShape &characterHitbox, const Vector2f& prevPos, const float &dt, const float &multiplier)
{
	//TODO: change if conditions cause they only work if they sprite has the same size as the wall 
	//Character
	Vector2f cS1Pos = characterSprite->getPosition();
	Vector2f cS2Pos = characterSprite->getPosition() + Vector2f(characterSprite->getGlobalBounds().width, characterSprite->getGlobalBounds().height);
	
	Vector2f cH1Pos = characterHitbox.getPosition();
	Vector2f cH2Pos = characterHitbox.getPosition() + Vector2f(characterHitbox.getGlobalBounds().width, characterHitbox.getGlobalBounds().height);

	//Tile
	Vector2f t1Pos = this->spritePtr->getPosition();
	Vector2f t2Pos = this->spritePtr->getPosition() + Vector2f(this->spritePtr->getGlobalBounds().width, this->spritePtr->getGlobalBounds().height);

	if (this->outwards)
	{
		if (this->top)
		{
			if (characterHitbox.getGlobalBounds().top < spritePtr->getGlobalBounds().top
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left
				)
			{
				float s1 = characterHitbox.getPosition().y - characterSprite->getPosition().y;
				characterSprite->setPosition(Vector2f(characterSprite->getPosition().x, t1Pos.y - characterHitbox.getGlobalBounds().height - s1));
			}
		}
		if (this->bottom)
		{
			if (characterHitbox.getGlobalBounds().top > spritePtr->getGlobalBounds().top
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left
				)
			{
				float s1 = characterHitbox.getPosition().y - characterSprite->getPosition().y;
				characterSprite->setPosition(Vector2f(characterSprite->getPosition().x, t2Pos.y - s1));
			}
		}
		if (this->left)
		{
			if (characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().top < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top
				)
			{
				characterSprite->setPosition(Vector2f(t1Pos.x - characterHitbox.getGlobalBounds().width - (cS2Pos.x - cH2Pos.x), characterSprite->getPosition().y));
			}
		}

		if (this->right)
		{
			if (characterHitbox.getGlobalBounds().left > spritePtr->getGlobalBounds().left
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().top < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top
				)
			{
				characterSprite->setPosition(Vector2f(t1Pos.x + characterHitbox.getGlobalBounds().width - (cS2Pos.x - cH2Pos.x), characterSprite->getPosition().y));
			}
		}
	}
	else 
	{
		if (this->top)
		{
			if (characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left
				)
			{
				float s2 = characterHitbox.getGlobalBounds().height - spritePtr->getGlobalBounds().height;
				float s1 = characterHitbox.getPosition().y - characterSprite->getPosition().y;
				characterSprite->setPosition(Vector2f(characterSprite->getPosition().x, t1Pos.y - (s1 + s2)));
			}
		}

		if (this->bottom)
		{
			if (characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left
				)
			{
				float s2 = characterHitbox.getGlobalBounds().height - spritePtr->getGlobalBounds().height;
				float s1 = characterHitbox.getPosition().y - characterSprite->getPosition().y;
				characterSprite->setPosition(Vector2f(characterSprite->getPosition().x, t1Pos.y - (s1 + s2)));
			}
		}

		if (this->left)
		{
			if (characterHitbox.getGlobalBounds().left < spritePtr->getGlobalBounds().left
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width < spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().top < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top
				)
			{
				characterSprite->setPosition(Vector2f(t1Pos.x - (cS2Pos.x - cH2Pos.x), characterSprite->getPosition().y));
			}
		}

		if (this->right)
		{
			if (characterHitbox.getGlobalBounds().left > spritePtr->getGlobalBounds().left
				&& characterHitbox.getGlobalBounds().left + characterHitbox.getGlobalBounds().width > spritePtr->getGlobalBounds().left + spritePtr->getGlobalBounds().width
				&& characterHitbox.getGlobalBounds().top < spritePtr->getGlobalBounds().top + spritePtr->getGlobalBounds().height
				&& characterHitbox.getGlobalBounds().top + characterHitbox.getGlobalBounds().height > spritePtr->getGlobalBounds().top
				)
			{
				characterSprite->setPosition(Vector2f(t2Pos.x - characterHitbox.getGlobalBounds().width - (cS2Pos.x - cH2Pos.x), characterSprite->getPosition().y));
			}
		}
	}
}
