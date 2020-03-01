#include "Folder.h"


Folder::Folder(std::string text, Folder* parent, Vector2f pos) :
	GUI(pos, parent)
{
	this->sprite.setTexture(*PreLoad::Textures::closedFolder);
	this->sprite.setScale(0.2f, 0.2f);
	this->constTextScale = Vector2f(0.5, 0.5);
	this->text.setScale(this->constTextScale);
	this->text.setString(text);
	this->text.setFont(*PreLoad::Fonts::font1);
	this->constPos = this->sprite.getPosition();
	this->constSize = this->sprite.getScale();
	this->constDimensions = this->sprite.getGlobalBounds();
	this->init();
}

Folder::~Folder()
{

}

void Folder::init()
{
	this->openImg = PreLoad::Textures::openFolder;
	this->closedImg = PreLoad::Textures::closedFolder;

	this->show();
	if (this->parent != NULL) this->hide();
	this->close();
	this->constTextFactor = Vector2f(1.f, 5.f);
	this->currentTextPos = Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/this->constTextFactor.x, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / this->constTextFactor.y);
	this->text.setPosition(this->currentTextPos);
}

void Folder::open()
{
	this->contentState = true;
	this->sprite.setTexture(*this->openImg);
	for (GUI *element : this->content)
	{
		element->show();
	}
	this->moveLower_GUI_elements(true);
}

void Folder::close()
{
	this->contentState = false;
	this->sprite.setTexture(*this->closedImg);
	this->moveLower_GUI_elements(false);
	for (GUI *element : this->content)
	{
		element->hide();
	}
}

void Folder::moveLower_GUI_elements(bool down)
{
	if (GUI::GUI_elements == NULL || this->content.size() == 0) return;
	float lowestPos = -INT_MAX;

	//Find the lowest element in the folder
	for (GUI* element : *GUI::GUI_elements)
	{
		float bottom = element->constPos.y + element->constDimensions.height;
		if (element->myIndex != this->myIndex || !element->visableState) continue;
		if (bottom > lowestPos) lowestPos = bottom;
	}

	float distance = this->content[0]->constPos.y - lowestPos;
	if(down) distance = -distance;

	//Move all the lover elements by that distance
	for (GUI* element : *GUI::GUI_elements)
	{
		if (element->myIndex > this->myIndex) element->moveY(distance);
	}
}

void Folder::addContent(GUI * moreContent)
{
	this->content.push_back(moreContent);
}

void Folder::addContent(std::vector<GUI*> moreContent)
{
	this->content.insert(this->content.end(), moreContent.begin(), moreContent.end());
}

void Folder::show()
{
	this->visableState = true;
	this->hidden = false;
	if (this->contentState)
	{
		for (GUI *element : this->content)
		{
			element->show();
		}
	}
}

void Folder::hide()
{
	this->visableState = false;
	for (GUI *element : this->content)
	{
		element->hide();
	}
}


void Folder::draw(RenderWindow * window)
{
	if (this->visableState)
	{
		this->mapToWindowCoords(window);
		window->draw(this->sprite);
		this->drawText(window);
	}
	this->GUI::draw(window);
}

void Folder::update(const float & dt, const float & multiplier, const Vector2f &mousePos)
{
	if (this->visableState)
	{
		if (this->mouseHover(mousePos) && Mouse::isButtonPressed(Mouse::Left) && !this->contentState && !this->mousePressedState)
		{
			this->open();
			this->mousePressedState = true;
		}
		else if (this->mouseHover(mousePos) && Mouse::isButtonPressed(Mouse::Left) && this->contentState && !this->mousePressedState)
		{
			this->close();
			this->mousePressedState = true;
		}
	}
	else if(!this->hidden && !this->visableState){
		for (GUI *element : this->content)
		{
			element->hide();
		}
		this->hidden = true;
	}
		
	if (!Mouse::isButtonPressed(Mouse::Left)) this->mousePressedState = false;
	this->GUI::update(dt, multiplier, mousePos);
}

unsigned int Folder::index = 0;