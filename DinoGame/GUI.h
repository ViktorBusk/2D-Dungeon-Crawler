#pragma once
#include "utils.hpp"

using namespace sf;

class GUI
{
private:
	void updateTextPos();

protected:
	Vector2f constPos;
	Vector2f constSize;
	Vector2f currentTextPos;
	Vector2f constTextFactor;
	Vector2f constTextScale;
	Texture* texture;
	Text text;

public:
	static std::vector<GUI*> *GUI_elements;
	Sprite sprite;
	GUI();
	virtual ~GUI();
	virtual void show() = 0;
	virtual void hide() = 0;
	bool mouseHover(const Vector2f &mousePos);

	inline const Vector2f& getPosition() { return this->sprite.getPosition(); }
	void mapToWindowCoords(RenderWindow *window);
	void drawText(RenderWindow* window);

	virtual void draw(RenderWindow * window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
};

