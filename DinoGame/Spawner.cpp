#include "Spawner.h"


Spawner::Spawner(Vector2f pos, Texture* texture, std::string type, Folder* parent, std::vector<Object*> *entitesPtr) :
	GUI()
{
	this->parent = parent;
	if (this->parent != NULL)
		this->sprite.setPosition(Vector2f(this->parent->getPosition().x + this->parent->sprite.getGlobalBounds().width / 2, pos.y));
	else
		this->sprite.setPosition(pos);
	this->text.setString(type);
	this->texture = texture;
	this->type = type;
	this->entitesPtr = entitesPtr;
	this->initType();
	this->init();
}

Spawner::~Spawner()
{
}


void Spawner::init()
{
	this->sprite.setScale(1.f, 1.f);
	this->constTextScale = Vector2f(0.5, 0.5);
	this->text.setScale(this->constTextScale);
	this->text.setFont(*PreLoad::Fonts::font1);
	this->constPos = this->sprite.getPosition();
	this->constSize = this->sprite.getScale();
	this->sprite.setTexture(*this->texture);
	
	this->currentTextPos = Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/this->constTextFactor.x, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height/this->constTextFactor.y);
	this->text.setPosition(this->currentTextPos);
	this->shouldSpawn = true;
	this->visableState = false;
}

void Spawner::initType()
{
	if (this->type == "Hero")
	{
		this->textureRects = Object::getTextureRects(PreLoad::Textures::knight, Vector2i(9, 1));
		this->sprite.setTextureRect(this->textureRects[1][0]);
		this->constTextFactor = Vector2f(0.9f, 3.f);
	}
	else if (this->type == "BigZombie")
	{
		this->textureRects = Object::getTextureRects(PreLoad::Textures::bigZombie, Vector2i(8, 1));
		this->sprite.setTextureRect(this->textureRects[0][0]);
		this->constTextFactor = Vector2f(1.f, 3.f);
	}
}


void Spawner::show()
{
	this->visableState = true;
}

void Spawner::hide()
{
	this->visableState = false;
}


void Spawner::draw(RenderWindow * window)
{
	if (this->visableState)
	{
		this->mapToWindowCoords(window);
		window->draw(this->sprite);
		this->drawText(window);
	}
	this->GUI::draw(window);
}

void Spawner::update(const float & dt, const float & multiplier, const Vector2f & mousePos)
{
	if (this->visableState)
	{
		if (this->mouseHover(mousePos) && Mouse::isButtonPressed(Mouse::Left) && this->shouldSpawn)
		{
			for (size_t i = 0; i < this->spawnAmount; i++)
			{
				this->spawn(mousePos);
			}
			this->shouldSpawn = false;
		}

		else if (!Mouse::isButtonPressed(Mouse::Left))
		{
			this->shouldSpawn = true;
		}
	}
	this->GUI::update(dt, multiplier, mousePos);
}
void Spawner::spawn(const Vector2f &pos)
{
	if (this->type == "Hero") this->entitesPtr->push_back(new Hero(pos));
	else if (this->type == "BigZombie") this->entitesPtr->push_back(new BigZombie(pos));
	//else if Etc
}

//Static variable definitions
unsigned int Spawner::spawnAmount = 1;