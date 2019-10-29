#include "Enemy.h"

Enemy::Enemy(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale) :
	Character(pos, spriteSheet, sheetSize, scale)
{
	//Animations
	this->setAnimations();
	this->currentAnim = this->idle;
	this->previousAnim = &this->currentAnim;
	this->index = rand() % this->idle.rectArray.size();
	this->sprite.setTextureRect(*this->currentAnim.rectArray[this->index]);

	//Movement
	trollingDirs[0] = "RIGHT";
	trollingDirs[1] = "UP";
	trollingDirs[2] = "DOWN";
	trollingDirs[3] = "NONE";
	trollingDirs[4] = "LU";
	trollingDirs[5] = "LD";
	trollingDirs[6] = "RU";
	trollingDirs[7] = "RD";
	this->trolling = 0;
	this->dir = this->trollingDirs[rand() % this->trollingDirs->size()];

	this->createMovementComponent(100.f, 4.f, FRICTION);
}

void Enemy::setAnimations()
{
	//Idle
	this->idle.rectArray.push_back(&this->textureRects[0][0]);
	this->idle.rectArray.push_back(&this->textureRects[1][0]);
	this->idle.rectArray.push_back(&this->textureRects[2][0]);
	this->idle.rectArray.push_back(&this->textureRects[3][0]);

	//walking
	this->walking.rectArray.push_back(&this->textureRects[4][0]);
	this->walking.rectArray.push_back(&this->textureRects[5][0]);
	this->walking.rectArray.push_back(&this->textureRects[6][0]);
	this->walking.rectArray.push_back(&this->textureRects[7][0]);
}

Enemy::~Enemy()
{
}

void Enemy::draw(RenderWindow * window) const
{
	this->Character::draw(window);
}

void Enemy::update(const float & dt, const float & multiplier)
{
	trolling += dt * multiplier;

	if (trolling >= rand()*cap)
	{
		trolling = 0;
		dir = trollingDirs[rand() % trollingDirs->size()];
	}

	if (dir == "NONE") this->nothing();
	else if (dir == "RIGHT") this->right(dt, multiplier);
	else if (dir == "LEFT") this->left(dt, multiplier);
	else if (dir == "UP") this->up(dt, multiplier);
	else if (dir == "DOWN") this->down(dt, multiplier);
	else if (dir == "LU") this->left(dt, multiplier), this->up(dt, multiplier);
	else if (dir == "LD") this->right(dt, multiplier), this->down(dt, multiplier);
	else if (dir == "RU") this->right(dt, multiplier), this->up(dt, multiplier);
	else this->right(dt, multiplier), this->down(dt, multiplier);
	
	if(this->colisionVec != NULL && this->holding == NULL)
	{
		bool pickedUp = false;
		for (Object* object : *this->colisionVec)
		{
			if (pickedUp) break;
			Item* item = dynamic_cast<Item*>(object);
			if (item != NULL && item->idle == true) {
				this->pickUpItem(item);
				pickedUp = true;
			}
		}
	}

	this->Character::update(dt, multiplier);

	//Hitbox
	this->hitboxComponent->setIndex(this->animIndex);
}
