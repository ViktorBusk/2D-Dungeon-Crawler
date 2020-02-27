#include "Slider.h"

Slider::Slider(Vector2f pos, float * value, Vector2f interval, Font * font)
{
	this->smallRectPos = pos;
	this->bigRectPos = pos;
	this->rect = Vector2f(200, 20);
	//Sliders
	this->bigRect.setFillColor(Color(100, 100, 100));
	this->smallRect.setFillColor(Color(200, 200, 200));

	this->interval = interval;
	this->value = value;
	this->copyValue = *value;
	//Text
	this->text.setFont(*font);
	this->text.setString(std::to_string(*this->value));
	this->text.setCharacterSize(17);
}

Slider::~Slider()
{
}

void Slider::draw(RenderWindow * window)
{
	//Slider
	this->bigRect.setPosition(Vector2f(window->mapPixelToCoords(Vector2i(this->bigRectPos))));
	this->smallRect.setPosition(Vector2f(window->mapPixelToCoords(Vector2i(this->smallRectPos))));

	Vector2f scaledRect = Vector2f(this->rect.x / window->getDefaultView().getSize().x * window->getView().getSize().x,
		this->rect.y / window->getDefaultView().getSize().y * window->getView().getSize().y);

	this->bigRect.setSize(scaledRect);
	this->smallRect.setSize(Vector2f(scaledRect.y, scaledRect.y));

	window->draw(this->bigRect);
	window->draw(this->smallRect);

	//Text
	this->text.setPosition(this->bigRect.getPosition());
	this->text.setScale(window->getView().getSize().x / window->getDefaultView().getSize().x, window->getView().getSize().y / window->getDefaultView().getSize().y);
	window->draw(this->text);
}

