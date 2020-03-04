#pragma once
#include "MovementComponent.h"
#include "HitboxComponent.h"
#include "ColisionComponent.h"
#include "AnimationComponent.h"

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
	int colisionIndex;
	MovementComponent* movementComponent;
	HitboxComponent *hitboxComponent;
	ColisionComponent *colisionComponent;
	
	struct EditorData{
		bool defined = false;
		Vector2f distance;
	};
	EditorData editorData;

public:
	bool fixedZIndex;
	bool chosen;
	bool shouldColide;
	float currentDistance;
	struct GridPos
	{
		Vector2i topLeft;
		Vector2i bottomRight;
	};
	GridPos gridPos;
	std::vector<Object*> colisionVec;
	Object(Vector2f pos, Texture *spriteSheet, Vector2i sheetSize, Vector2f scale);
	virtual ~Object();
	//Components
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deAcceleration);
	void createHitboxComponent(Color color);
	void createColisionComponent(bool outwards, bool left, bool right, bool top, bool bottom);

	//Accessors
	inline const GridPos &getWorldGridPos() const { return this->gridPos; }
	inline const int &getZIndex() const { return this->zIndex; }
	inline const int &getColisionIndex() const { return this->colisionIndex; }
	RectangleShape &getHitbox() const;
	const HitboxComponent *getHitboxComponent() const;
	const Vector2f getCenterHitbox() const;
	const Vector2f &getPos() const;
	const FloatRect &getSpriteSize() const;
	const Vector2f getCenter() const;
	
	//Modifiers
	inline void setZIndex(const int &zIndex) { this->zIndex = zIndex; }
	inline void setColisionIndex(const int &cIndex) { this->colisionIndex = cIndex; }
	void setPosition(const Vector2f &pos);
	void setPositionCenter(const Vector2f &pos);
	void setWorldGridPos();
	void addColisionVec(std::vector<Object*> *gridColisionVec);
	void addColisionObj(Object* obj);
	void moveWithMouse(const Vector2f &mousePos, const bool &followMouse, const Vector2f &mousePoint);

	//Functions
	virtual void draw(RenderWindow * window) const = 0;
	virtual void update(const float &dt,const float &multiplier) = 0;
	void drawSpriteRect(RenderWindow *window);
	void updateColisions();
	void updateColisionComponent(Sprite *characterSprite, const RectangleShape &characterHitbox, const Vector2f& prevPos, const float &dt, const float &multiplier);
	bool mouseColision(RenderWindow *window);
	bool colision(Object* object);
	void flipTexture();
	void createSpriteHitboxComponent(Color color);
	static std::vector<std::vector<IntRect>> getTextureRects(Texture *spriteSheet, const Vector2i &nrOfImgs);
};



