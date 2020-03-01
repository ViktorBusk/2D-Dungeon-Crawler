#include "Hero.h"

Hero::Hero(Vector2f pos) :
	Character(pos, PreLoad::Textures::knight, Vector2i(9, 1), SCALE)
{
	//Animations
	this->index = 0;
	this->setAnimations();
	this->currentAnim = this->idle;
	this->previousAnim = &this->currentAnim;
	this->sprite.setTextureRect(*this->currentAnim.rectArray[this->index]);

	//Movement
	this->createMovementComponent(200.f, 5.f, FRICTION);

	//Hitbox
	this->createHitboxComponent(Color(0, 255, 0, 125));
	std::vector<int> hitboxData = PreLoad::Hitboxes::hitboxlist->hitboxData[3][1].second;
	this->hitboxComponent->setStaticComponent(Vector2f(hitboxData[2], hitboxData[3]), Vector2f(hitboxData[4], hitboxData[5]));
	this->hitboxComponent->setDynamicComponent(3);
}

void Hero::draw(RenderWindow * window) const
{
	this->Character::draw(window);
}

void Hero::setAnimations()
{

	//Idle
	this->idle.rectArray.push_back(&this->textureRects[1][0]);
	this->idle.rectArray.push_back(&this->textureRects[2][0]);
	this->idle.rectArray.push_back(&this->textureRects[3][0]);
	this->idle.rectArray.push_back(&this->textureRects[4][0]);

	//walking
	this->walking.rectArray.push_back(&this->textureRects[5][0]);
	this->walking.rectArray.push_back(&this->textureRects[6][0]);
	this->walking.rectArray.push_back(&this->textureRects[7][0]);
	this->walking.rectArray.push_back(&this->textureRects[8][0]);
}

void Hero::update(const float & dt, const float &multiplier)
{
	//Input
	//Movement
	if (Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) this->up(dt, multiplier);
	if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)) this->left(dt, multiplier);
	if (Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W)) this->down(dt, multiplier);
	if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A)) this->right(dt, multiplier);
	//Items
	if (Keyboard::isKeyPressed(Keyboard::F) && this->holding == NULL)
	{
		bool pickedUp = false;
		for (Object* object : this->colisionVec)
		{
			if (pickedUp) break;
			if (this == object) continue;
			Item* item = dynamic_cast<Item*>(object);
			if (item != NULL && item->idle == true) {
				this->pickUpItem(item);
				pickedUp = true;
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::R) && this->holding != NULL)
	{
		this->dropItem();
	}

	this->Character::update(dt, multiplier);

	//Hitbox
	this->hitboxComponent->setIndex(this->animIndex);
}


Hero::~Hero()
{
}
