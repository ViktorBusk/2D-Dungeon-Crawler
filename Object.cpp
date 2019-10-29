#include "Object.h"

Object::Object(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale)
{
	this->sprite.setPosition(pos);
	this->spriteSheet = spriteSheet;
	this->textureRects = this->getTextureRects(spriteSheet, Vector2i(sheetSize.x, sheetSize.y));
	this->sprite.setTexture(*spriteSheet);
	this->sprite.setScale(scale);
	this->initVariables();
}

Object::~Object()
{
	delete this->movementComponent;
	delete this->hitboxComponent;
	delete this->colisionComponent;
}

void Object::initVariables()
{
	this->movementComponent = NULL;
	this->hitboxComponent = NULL;
	this->colisionVec = NULL;
	this->colisionComponent = NULL;
	this->zIndex = 0;
	this->fixedZIndex = false;
}

void Object::createMovementComponent(const float maxVelocity , const float acceleration, const float deAcceleration)
{
	if (this->movementComponent != NULL) delete this->movementComponent;
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deAcceleration);
}

void Object::createHitboxComponent(const int hitboxIndex, Color color)
{
	if (this->hitboxComponent != NULL) delete this->hitboxComponent;
	this->hitboxComponent = new HitboxComponent(this->sprite, hitboxIndex, color);
}

void Object::createColisionComponent(float dir_x, float dir_y)
{
	if (this->colisionComponent != NULL) delete this->colisionComponent;
	this->colisionComponent = new ColisionComponent(this->sprite, dir_x, dir_x);
}

void Object::updateColisionComponent(Sprite *characterSprite, const RectangleShape &characterHitbox, const float &dt, const float &multiplier)
{
	if (this->colisionComponent != NULL)
	{
		this->colisionComponent->update(characterSprite, characterHitbox, dt, multiplier);
	}
}

void Object::draw(RenderWindow * window) const
{
	if (this->hitboxComponent != NULL)
	{
		this->hitboxComponent->draw(window);
	}
}

void Object::update(const float& dt, const float& multiplier)
{
	if (this->movementComponent) this->movementComponent->update(dt, multiplier);
	if (this->hitboxComponent) {
		if(!this->fixedZIndex) this->zIndex = this->hitboxComponent->rect.getPosition().y + this->hitboxComponent->rect.getGlobalBounds().height;
		this->hitboxComponent->update(dt, multiplier);
		this->setWorldGridPos();
	}
}

void Object::updateColisions()
{
	if (this->hitboxComponent) {
		bool isColiding = false;
		if (colisionVec != NULL) {
			for (Object* object : *colisionVec)
			{
				if (object->hitboxComponent == NULL) continue;
				if (this->colision(object))
				{
					isColiding = true;
					object->addColisionObj(this);
					this->hitboxComponent->rect.setFillColor(Color::Magenta);
					object->getHitbox().setFillColor(Color::Magenta);
				}
			}
		}
		if(!isColiding) this->hitboxComponent->rect.setFillColor(this->hitboxComponent->color);
	}
}

void Object::setWorldGridPos()
{
	Vector2i tileSize(SCALE.x*TILESIZE, SCALE.y*TILESIZE);
	this->gridPos.topLeft.x = floor(this->hitboxComponent->rect.getPosition().x / tileSize.x);
	this->gridPos.topLeft.y = floor(this->hitboxComponent->rect.getPosition().y / tileSize.y);
	this->gridPos.bottomRight.x = floor((this->hitboxComponent->rect.getPosition().x + this->hitboxComponent->rect.getSize().x) / tileSize.x);
	this->gridPos.bottomRight.y = floor((this->hitboxComponent->rect.getPosition().y + this->hitboxComponent->rect.getSize().y) / tileSize.y);
}

void Object::addColisionVec(std::vector<Object*>* gridColisionVec)
{
	if(this->colisionVec == NULL) this->colisionVec = gridColisionVec;
	else this->colisionVec->insert(this->colisionVec->end(), gridColisionVec->begin(), gridColisionVec->end());
}

void Object::addColisionObj(Object * obj)
{
	if (this->colisionVec != NULL) this->colisionVec->push_back(obj);
}

const Vector2f & Object::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect & Object::getSpriteSize() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f Object::getCenter() const
{
	Vector2f center(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
	return center;
}

void Object::setPosition(const Vector2f &pos)
{
	this->sprite.setPosition(pos);
}

RectangleShape & Object::getHitbox() const
{
	return this->hitboxComponent->rect;
}

const Vector2f Object::getCenterHitbox() const
{
	float x = this->hitboxComponent->rect.getPosition().x + this->hitboxComponent->rect.getGlobalBounds().width / 2;
	float y = this->hitboxComponent->rect.getPosition().y + this->hitboxComponent->rect.getGlobalBounds().height / 2;
	return Vector2f(x, y);
}

//AABB
bool Object::colision(Object * object)
{
	float sX1 = this->hitboxComponent->rect.getPosition().x;
	float sX2 = sX1 + this->hitboxComponent->rect.getSize().x;
	float sY1 = this->hitboxComponent->rect.getPosition().y;
	float sY2 = sY1 + this->hitboxComponent->rect.getSize().y;

	float oX1 = object->getHitbox().getPosition().x;
	float oX2 = oX1 + object->getHitbox().getSize().x;
	float oY1 = object->getHitbox().getPosition().y;
	float oY2 = oY1 + object->getHitbox().getSize().y;

	return (sX1 <= oX2 && sX2 >= oX1 &&
		sY1 <= oY2 && sY2 >= oY1);
}

bool Object::colision(Object * obj1, Object * obj2)
{
	float sX1 = obj1->getHitbox().getPosition().x;
	float sX2 = sX1 + obj1->getHitbox().getSize().x;
	float sY1 = obj1->getHitbox().getPosition().y;
	float sY2 = sY1 + obj1->getHitbox().getSize().y;

	float oX1 = obj2->getHitbox().getPosition().x;
	float oX2 = oX1 + obj2->getHitbox().getSize().x;
	float oY1 = obj2->getHitbox().getPosition().y;
	float oY2 = oY1 + obj2->getHitbox().getSize().y;

	return (sX1 <= oX2 && sX2 >= oX1 &&
		sY1 <= oY2 && sY2 >= oY1);
}

void Object::flipTexture()
{
	for (size_t x = 0; x < textureRects.size(); x++)
	{
		for (size_t y = 0; y < textureRects[x].size(); y++)
		{
			this->textureRects[x][y].left += this->textureRects[x][y].width;
			this->textureRects[x][y].width = -this->textureRects[x][y].width;
		}
	}

}

std::vector<std::vector<IntRect>> Object::getTextureRects(Texture * spriteSheet, const Vector2i &nrOfImgs)
{
	std::vector<std::vector<IntRect>> textureRects;
	Vector2f inc(spriteSheet->getSize().x / nrOfImgs.x, spriteSheet->getSize().y / nrOfImgs.y);

	for (int x = 0; x < spriteSheet->getSize().x; x+=inc.x)
	{
		std::vector<IntRect> temp;
		for (int y = 0; y < spriteSheet->getSize().y; y+=inc.y)
		{
			temp.push_back(IntRect(Vector2i(x, y), Vector2i(inc.x-1, inc.y-1)));
		}
		textureRects.push_back(temp);
	}
	return textureRects;
}



