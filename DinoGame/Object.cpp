#include "Object.h"

Object::Object(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale)
{
	this->sprite.setPosition(pos);
	this->spriteSheet = spriteSheet;
	this->textureRects = this->getTextureRects(spriteSheet, sheetSize);
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
	this->colisionComponent = NULL;
	this->zIndex = 0;
	this->currentDistance = INT_MAX;
	this->fixedZIndex = false;
	this->colisionIndex = this->zIndex;
	this->shouldColide = false;
}

void Object::createMovementComponent(const float maxVelocity , const float acceleration, const float deAcceleration)
{
	if (this->movementComponent != NULL) delete this->movementComponent;
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deAcceleration);
}

void Object::createHitboxComponent(Color color)
{
	this->shouldColide = true;
	if (this->hitboxComponent != NULL) delete this->hitboxComponent;
	this->hitboxComponent = new HitboxComponent(this->sprite, color);
}

void Object::createColisionComponent(bool outwards, bool left, bool right, bool top, bool bottom)
{
	if (this->colisionComponent != NULL) delete this->colisionComponent;
	this->colisionComponent = new ColisionComponent(this->sprite, outwards, left, right, top, bottom);
	this->colisionIndex = 1;
}

void Object::updateColisionComponent(Sprite *characterSprite, const RectangleShape &characterHitbox, const Vector2f& prevPos, const float &dt, const float &multiplier)
{
	if (this->colisionComponent != NULL)
	{
		this->colisionComponent->update(characterSprite, characterHitbox, prevPos, dt, multiplier);
	}
}

bool Object::mouseColision(RenderWindow *window)
{
	Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window), window->getView());
	return (mousePos.x >= this->hitboxComponent->rect->getPosition().x &&
		mousePos.x <= this->hitboxComponent->rect->getPosition().x + this->hitboxComponent->rect->getGlobalBounds().width &&
		mousePos.y >= this->hitboxComponent->rect->getPosition().y &&
		mousePos.y <= this->hitboxComponent->rect->getPosition().y + this->hitboxComponent->rect->getGlobalBounds().height);
}

void Object::draw(RenderWindow * window) const
{
	if (this->hitboxComponent != NULL)
	{
		if (this->chosen) this->hitboxComponent->draw(window);
	}
}

void Object::update(const float& dt, const float& multiplier)
{
	if (this->movementComponent) this->movementComponent->update(dt, multiplier);
	if (this->hitboxComponent) {
		if(!this->fixedZIndex) this->zIndex = this->hitboxComponent->staticRect.getPosition().y + this->hitboxComponent->rect->getGlobalBounds().height;
		this->hitboxComponent->update(dt, multiplier);
	}
	this->colisionVec.clear();
}

void Object::drawSpriteRect(RenderWindow *window)
{
	RectangleShape rect(Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height));
	rect.setPosition(this->sprite.getPosition());
	rect.setFillColor(this->hitboxComponent->color);
	window->draw(rect);
}

void Object::updateColisions()
{
	if (this->hitboxComponent) {
		bool isColiding = false;
		for (Object* object : this->colisionVec)
		{	
			if (object == NULL || this == object) continue;
			else if(object->hitboxComponent == NULL) continue;
			if (this->colision(object))
			{
				isColiding = true;
				object->addColisionObj(this);
				this->hitboxComponent->rect->setFillColor(Color::Magenta);
				object->getHitbox().setFillColor(Color::Magenta);
				object->currentDistance = Utils::distance2f(this->getCenterHitbox(), object->getCenterHitbox());
			}
		}
		if(!isColiding) this->hitboxComponent->rect->setFillColor(this->hitboxComponent->color);
		
		//Sort based on distance to itself
		std::sort(this->colisionVec.begin(), this->colisionVec.end(), [](const Object* obj1, const Object* obj2) {
			return obj1->currentDistance < obj2->currentDistance;
		});
	}
}

void Object::setWorldGridPos()
{
	Vector2i tileSize(SCALE.x*TILESIZE, SCALE.y*TILESIZE);
	this->gridPos.topLeft.x = floor(this->hitboxComponent->staticRect.getPosition().x / tileSize.x);
	this->gridPos.topLeft.y = floor(this->hitboxComponent->staticRect.getPosition().y / tileSize.y);
	this->gridPos.bottomRight.x = floor((this->hitboxComponent->staticRect.getPosition().x + this->hitboxComponent->staticRect.getSize().x) / tileSize.x);
	this->gridPos.bottomRight.y = floor((this->hitboxComponent->staticRect.getPosition().y + this->hitboxComponent->staticRect.getSize().y) / tileSize.y);
}

void Object::addColisionVec(std::vector<Object*>* gridColisionVec)
{
	this->colisionVec.insert(this->colisionVec.end(), gridColisionVec->begin(), gridColisionVec->end());
}

void Object::addColisionObj(Object * obj)
{
	this->colisionVec.push_back(obj);
}

void Object::moveWithMouse(const Vector2f &mousePos, const bool &followMouse, const Vector2f &mousePoint)
{
	if (this->chosen)
	{
		if (followMouse)
		{
			if (!this->editorData.defined)
			{
				this->editorData.distance.x = this->sprite.getPosition().x - mousePoint.x;
				this->editorData.distance.y = this->sprite.getPosition().y - mousePoint.y;
				this->editorData.defined = true;
			}
			this->sprite.setPosition(mousePos + this->editorData.distance);
		}
	}
	if (!followMouse)
	{
		this->editorData.defined = false;
	}
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

void Object::setPositionCenter(const Vector2f & pos)
{
	this->sprite.setPosition(Vector2f(pos.x - this->sprite.getGlobalBounds().width/2, pos.y - this->sprite.getGlobalBounds().height / 2));
}

RectangleShape &Object::getHitbox() const
{
	return *this->hitboxComponent->rect;
}

const HitboxComponent * Object::getHitboxComponent() const
{
	return this->hitboxComponent;
}

const Vector2f Object::getCenterHitbox() const
{
	float x = this->hitboxComponent->rect->getPosition().x + this->hitboxComponent->rect->getGlobalBounds().width / 2;
	float y = this->hitboxComponent->rect->getPosition().y + this->hitboxComponent->rect->getGlobalBounds().height / 2;
	return Vector2f(x, y);
}

//AABB static rect
bool Object::colision(Object * object)
{
	float sX1 = this->hitboxComponent->staticRect.getPosition().x;
	float sX2 = sX1 + this->hitboxComponent->staticRect.getSize().x;
	float sY1 = this->hitboxComponent->staticRect.getPosition().y;
	float sY2 = sY1 + this->hitboxComponent->staticRect.getSize().y;

	float oX1 = object->getHitboxComponent()->staticRect.getPosition().x;
	float oX2 = oX1 + object->getHitboxComponent()->staticRect.getSize().x;
	float oY1 = object->getHitboxComponent()->staticRect.getPosition().y;
	float oY2 = oY1 + object->getHitboxComponent()->staticRect.getSize().y;

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

void Object::createSpriteHitboxComponent(Color color)
{
	this->createHitboxComponent(color);
	this->hitboxComponent->setStaticComponent(Vector2f(0.f, 0.f), Vector2f(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height));
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
			temp.push_back(IntRect(Vector2i(x, y), Vector2i(inc.x, inc.y)));
		}
		textureRects.push_back(temp);
	}
	return textureRects;
}



