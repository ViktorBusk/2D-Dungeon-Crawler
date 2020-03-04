#pragma once
#include "utils.hpp"
#include "Object.h"

using namespace sf;

class GUI
{
private:
	void updateTextPos();

protected:
	Vector2f constSize;
	Vector2f currentTextPos;
	Vector2f constTextFactor;
	Vector2f constTextScale;
	Texture* texture;
	Text text;

public:
	GUI* parent;
	Vector2f constPos;
	FloatRect constDimensions;
	static std::vector<GUI*> *GUI_elements;
	static std::vector<Object*> *entitiesPtr;
	static unsigned int index;
	unsigned int myIndex;
	Sprite sprite;
	GUI(Vector2f pos, GUI* parent);
	virtual ~GUI();
	bool visableState;
	virtual void show() = 0;
	virtual void hide() = 0;
	bool mouseHover(const Vector2f &mousePos);

	inline const Vector2f& getPosition() { return this->sprite.getPosition(); }
	void mapToWindowCoords(RenderWindow *window);
	void drawText(RenderWindow* window);
	void moveY(const float &yDist);

	virtual void draw(RenderWindow * window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
};

