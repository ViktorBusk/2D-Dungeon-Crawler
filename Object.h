#pragma once
#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "ColisionComponent.h"

using namespace sf;

class Object
{
private:
	void initVariables();

protected:
	Sprite sprite;
	Texture* spriteSheet;
	std::vector<std::vector<IntRect>> textureRects;
	int zIndex;
	MovementComponent* movementComponent;
	HitboxComponent *hitboxComponent;
	ColisionComponent *colisionComponent;

public:
	bool fixedZIndex;
	struct GridPos
	{
		Vector2i topLeft;
		Vector2i bottomRight;
	};
	GridPos gridPos;
	std::vector<Object*> *colisionVec;
	Object(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale);
	virtual ~Object();
	//Components
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deAcceleration);
	void createHitboxComponent(const int hitboxIndex, Color color);
	void createColisionComponent(float dir_x, float dir_y);
	void updateColisionComponent(Sprite *characterSprite, const RectangleShape &characterHitbox, const float &dt, const float &multiplier);

	//Accessors
	inline const GridPos &getWorldGridPos() const { return this->gridPos; }
	inline const int &getZIndex() const { return this->zIndex; }
	RectangleShape &getHitbox() const;
	const Vector2f getCenterHitbox() const;
	const Vector2f &getPos() const;
	const FloatRect &getSpriteSize() const;
	const Vector2f getCenter() const;
	
	//Modifiers
	inline void setZIndex(const int &zIndex) { this->zIndex = zIndex; }
	void setPosition(const Vector2f &pos);
	void setWorldGridPos();
	void addColisionVec(std::vector<Object*> *gridColisionVec);
	void addColisionObj(Object* obj);

	//Functions
	virtual void draw(RenderWindow * window) const = 0;
	virtual void update(const float &dt,const float &multiplier) = 0;
	void updateColisions();
	bool colision(Object* object);
	static bool colision(Object* obj1, Object* obj2);
	void flipTexture();
	static std::vector<std::vector<IntRect>> getTextureRects(Texture *spriteSheet, const Vector2i &nrOfImgs);
};



