#pragma once
#include "Object.h"
#include "Item.h"
#include "Wall.h"

class Character : public Object
{
private:
	int baseHP;
	int HP;

protected:
	struct Movement {
		float maxVel = 200.f;

		bool NOW = false;
		bool UP = false;
		bool LEFT = false;
		bool DOWN = false;
		bool RIGHT = false;

		void reset();
	};
	struct Animation
	{
		std::vector<IntRect*> rectArray;
	};

	float incer;
	float cap;
	unsigned int index;
	int animIndex;
	Texture *spriteSheet;
	Movement move;
	bool direction; //false = left, true = right
	float angle;
	bool prevDirection;
	
	Animation idle;
	Animation walking;
	Animation currentAnim;
	Animation *previousAnim;

	std::vector<Item*> inventory;
	Item* holding;
	
	void updateFrames(const float & dt, const float & multiplier);
	int findIndex(const IntRect *currentFrame);
	void updateAngle();

	void nothing();
	void up(const float &dt, const float &multiplier);
	void left(const float &dt, const float &multiplier);
	void down(const float &dt, const float &multiplier);
	void right(const float &dt, const float &multiplier);
	void useItem(const float &dt, const float &multiplier);
	void pickUpItem(Item *item);
	void dropItem();

public:
	Character(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale);
	virtual ~Character();

	//Accessors
	
	//Modifiers

	//Functions
	virtual void draw(RenderWindow *window) const;
	virtual void update(const float & dt, const float & multiplier);
	void takeDamage(int amount);
};

