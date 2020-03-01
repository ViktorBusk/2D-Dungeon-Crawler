#include "GUI.h"

GUI::GUI(Vector2f pos, GUI* parent)
{
	this->parent = parent;
	if (this->parent != NULL)
	{
		this->sprite.setPosition(Vector2f(this->parent->getPosition().x + this->parent->sprite.getGlobalBounds().width / 2, pos.y));
		this->myIndex = this->parent->myIndex;
	}
	else
	{
		this->sprite.setPosition(pos);
		this->myIndex = GUI::index;
		GUI::index++;
	}
}

GUI::~GUI()
{
}

bool GUI::mouseHover(const Vector2f & mousePos)
{
	return (mousePos.x >= this->sprite.getPosition().x &&
		mousePos.x <= this->sprite.getPosition().x + this->sprite.getGlobalBounds().width &&
		mousePos.y >= this->sprite.getPosition().y &&
		mousePos.y <= this->sprite.getPosition().y + this->sprite.getGlobalBounds().height);
}

void GUI::updateTextPos()
{
	this->currentTextPos = Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/this->constTextFactor.x, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / this->constTextFactor.y);
}


void GUI::mapToWindowCoords(RenderWindow * window)
{
	//Sprite
	this->sprite.setPosition(Vector2f(window->mapPixelToCoords(Vector2i(this->constPos))));
	this->sprite.setScale(this->constSize.x / window->getDefaultView().getSize().x * window->getView().getSize().x,
		this->constSize.y / window->getDefaultView().getSize().y * window->getView().getSize().y);
	
	//Text
	this->updateTextPos();
	this->text.setPosition(this->currentTextPos);
	this->text.setScale(this->constTextScale.x*window->getView().getSize().x / window->getDefaultView().getSize().x, this->constTextScale.y*window->getView().getSize().y / window->getDefaultView().getSize().y);
}

void GUI::drawText(RenderWindow * window)
{
	window->draw(this->text);
}

void GUI::moveY(const float &yDist)
{
	this->constPos = Vector2f(this->constPos.x, this->constPos.y + yDist);
}


void GUI::draw(RenderWindow * window)
{
	Vector2f mousePos = window->mapPixelToCoords(Mouse::getPosition(*window), window->getView());
	if (this->mouseHover(mousePos)) this->text.setFillColor(Color(0, 255, 0));
	else
	{
		this->text.setFillColor(Color(180, 168, 255));
		this->text.setOutlineColor(Color::Black);
		this->text.setOutlineThickness(3.f);
		this->text.setLetterSpacing(1.4f);
	}		
}

void GUI::update(const float & dt, const float & multiplier, const Vector2f &mousePos)
{
	
}

std::vector<GUI*> *GUI::GUI_elements = NULL;