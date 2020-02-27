#include "Character.h"

Character::Character(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale) :
	Object(pos, spriteSheet, sheetSize, scale)
{
	//Animations
	this->cap = 12.f;
	this->incer = rand() % int(this->cap) + 1;
	this->direction = true;
	this->prevDirection = this->direction;

	//Items
	this->holding = NULL;
}

Character::~Character()
{
}

void Character::updateFrames(const float & dt,const float & multiplier)
{
	this->incer+=dt*multiplier;
	if (this->incer >= this->cap)
	{
		this->incer = 0;
		if (this->index >= this->currentAnim.rectArray.size() || this->previousAnim != &currentAnim)
			this->index = 0;
		this->sprite.setTextureRect(*this->currentAnim.rectArray[this->index]);
		this->animIndex = this->findIndex(this->currentAnim.rectArray[this->index]);
		this->index++;
	}
	this->previousAnim = &this->currentAnim;
}

void Character::updateAngle()
{
	float halfQarter = PI / 4;
	//RIGHT AND UP
	if (this->move.RIGHT && this->move.UP) this->angle = halfQarter;
	else if (this->move.RIGHT && this->move.DOWN) this->angle = -halfQarter;
	else if (this->move.UP && !this->move.LEFT) this->angle = 2 * halfQarter;
	else if (this->direction && !this->move.DOWN) this->angle = 0;

	//LEFT AND DOWN
	else if (this->move.LEFT && this->move.UP) this->angle = 3 * halfQarter;
	else if (this->move.LEFT && this->move.DOWN) this->angle = 5 * halfQarter;
	else if (this->move.DOWN) this->angle = 6 * halfQarter;
	else if (!this->direction) this->angle = 4 * halfQarter;
}


void Character::nothing()
{
	this->currentAnim = this->idle;
}

void Character::up(const float &dt, const float &multiplier)
{
	this->move.NOW, this->move.UP = true;
	this->currentAnim = this->walking;
	this->movementComponent->move(0.f, -1.f, dt, multiplier);
}
																					
void Character::left(const float &dt, const float &multiplier)
{
	this->move.NOW, this->move.LEFT = true;
	this->direction = false;
	this->currentAnim = this->walking;
	this->movementComponent->move(-1.f, 0.f, dt, multiplier);
}

void Character::down(const float &dt, const float &multiplier)
{
	this->move.NOW, this->move.DOWN = true;
	this->currentAnim = this->walking;
	this->movementComponent->move(0.f, 1.f, dt, multiplier);
}

void Character::right(const float &dt, const float &multiplier)
{
	this->move.NOW, this->move.RIGHT = true;
	this-> direction = true;
	this->currentAnim = this->walking;
	this->movementComponent->move(1.f, 0.f, dt, multiplier);
}

void Character::useItem(const float &dt, const float &multiplier)
{
	if (this->holding != NULL)
	{

	}

}

void Character::pickUpItem(Item * item)
{
	this->holding = item;
	this->holding->fixedZIndex = true;
	this->holding->followObject();
	this->inventory.push_back(item);
}

void Character::dropItem()
{
	auto it = std::find(this->inventory.begin(), this->inventory.end(), this->holding);
	if (it != this->inventory.end()) {
		this->inventory.erase(it);
	}
	this->holding->fixedZIndex = false;
	this->holding->setIdle();
	this->holding = NULL;
}

void Character::draw(RenderWindow * window) const
{
	this->Object::draw(window);
	window->draw(this->sprite);
}

void Character::update(const float & dt, const float & multiplier)
{
	//Directions
	//if facing to the left and the texture is not flipped
	if (!this->direction && this->prevDirection != this->direction)
	{
		this->flipTexture();
		if (this->holding != NULL)
		{
			this->holding->flipTexture();
		}

	}
	//if facing to the left and the texture is not flipped
	else if (this->prevDirection != this->direction)
	{
		this->flipTexture();
		if (this->holding != NULL) this->holding->flipTexture();
	}
	this->prevDirection = direction;

	this->updateAngle();

	//Animation
	this->updateFrames(dt, multiplier);
	if (!this->move.NOW) this->nothing();
	
	//Movememet
	this->move.reset();

	//Items
	if (this->holding && !direction)
	{
		this->holding->setPosition(Vector2f(this->getCenterHitbox().x - this->holding->getHitbox().getGlobalBounds().width/3, this->getCenterHitbox().y - this->holding->getHitbox().getSize().y/1.1));
		this->holding->setZIndex(this->zIndex - 1);
	}
	if (this->holding && direction)
	{
		this->holding->setPosition(Vector2f(this->getCenterHitbox().x - this->holding->getHitbox().getGlobalBounds().width/1.5, this->getCenterHitbox().y - this->holding->getHitbox().getSize().y/1.1));
		this->holding->setZIndex(this->zIndex + 1);
	}

	//Handle colision
	for (Object* object : this->colisionVec)
	{
		if (this == object) continue;
		Wall* wall = dynamic_cast<Wall*>(object);
		if (wall != NULL) {
			wall->updateColisionComponent(&this->sprite, this->hitboxComponent->staticRect, dt, multiplier);
			break;
		}
	}
	this->Object::update(dt, multiplier);
}

void Character::Movement::reset()
{
	NOW = false;
	UP = false;
	LEFT = false;
	DOWN = false;
	RIGHT = false;
}

int Character::findIndex(const IntRect *currentFrame)
{
	//only works for sheets with one row, not very efficient fix later!!!
	for (size_t x = 0; x < this->textureRects.size(); x++)
	{
		for (size_t y = 0; y < this->textureRects[x].size(); y++)
		{
			if (currentFrame == &this->textureRects[x][y]) return x;
		}
	}
}
