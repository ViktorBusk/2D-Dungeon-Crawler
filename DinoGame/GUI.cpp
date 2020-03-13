#include "GUI.h"

GUI::GUI(Vector2f pos, GUI* parent)
{
	this->contentIndex = 0;
	this->parent = parent;
	if (this->parent != NULL)
	{
		this->sprite.setPosition(Vector2f(pos.x + this->parent->sprite.getGlobalBounds().width / 2, pos.y));
		this->indexVec.insert(this->indexVec.end(), this->parent->indexVec.begin(), this->parent->indexVec.end());
		this->indexVec.push_back(this->parent->contentIndex);
		this->parent->contentIndex++;
	}
	else
	{
		this->sprite.setPosition(pos);
		this->indexVec.push_back(GUI::rootIndex);
		GUI::rootIndex++;
	}
}

GUI::~GUI()
{
}

bool GUI::hasHaparent(GUI * element)
{
	GUI *rootParent = element;
	while (rootParent->parent != NULL)
	{
		if (rootParent == element)
			return true;
		rootParent = rootParent->parent;
	}
	return false;
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
	GUI::mapSpriteToWindowCoords(window, &this->sprite, this->constPos, this->constSize);
	
	//Text
	this->updateTextPos();
	this->text.setPosition(this->currentTextPos);
	this->text.setScale(this->constTextScale.x*window->getView().getSize().x / window->getDefaultView().getSize().x, this->constTextScale.y*window->getView().getSize().y / window->getDefaultView().getSize().y);
}

void GUI::mapSpriteToWindowCoords(RenderWindow * window, Sprite * sprite, const Vector2f &constPos, const Vector2f &constSize)
{
	//Sprite
	sprite->setPosition(Vector2f(window->mapPixelToCoords(Vector2i(constPos))));
	sprite->setScale(constSize.x / window->getDefaultView().getSize().x * window->getView().getSize().x,
		constSize.y / window->getDefaultView().getSize().y * window->getView().getSize().y);
}

void GUI::mapTextToWindowCoords(RenderWindow * window, Text * text, const Vector2f & constPos, const Vector2f & constSize)
{
	text->setPosition(Vector2f(window->mapPixelToCoords(Vector2i(constPos))));
	text->setScale(constSize.x*window->getView().getSize().x / window->getDefaultView().getSize().x, constSize.y*window->getView().getSize().y / window->getDefaultView().getSize().y);
}

void GUI::drawText(RenderWindow * window)
{
	window->draw(this->text);
}

void GUI::moveY(const float &yDist)
{
	this->constPos = Vector2f(this->constPos.x, this->constPos.y + yDist);
}

bool GUI::hasChild(GUI * element)
{
	GUI* elementPtr = element;
	while (elementPtr->parent != NULL)
	{
		if(this == elementPtr->parent) return true;
		else elementPtr = elementPtr->parent;
	}
	return false;
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
std::vector<GUI*> *GUI::GUI_TreeView_elements = NULL;
std::vector<Object*> *GUI::entitiesPtr = NULL;