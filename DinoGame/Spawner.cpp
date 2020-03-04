#include "Spawner.h"

Spawner::Spawner(Vector2f pos, Texture* texture, std::string type, GUI* parent, Vector2i types) :
	GUI(pos, parent)
{
	this->text.setString(type);
	this->texture = texture;
	this->type = type;
	this->types = types;
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
	this->constDimensions = this->sprite.getGlobalBounds();
	this->shouldPickUp = true;
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
	else if (this->type == "Demon")
	{
		this->textureRects = Object::getTextureRects(PreLoad::Textures::demon, Vector2i(8, 1));
		this->sprite.setTextureRect(this->textureRects[0][0]);
		this->constTextFactor = Vector2f(1.f, 3.f);
	}
	else if (this->type == "Skelet")
	{
		this->textureRects = Object::getTextureRects(PreLoad::Textures::skelet, Vector2i(8, 1));
		this->sprite.setTextureRect(this->textureRects[0][0]);
		this->constTextFactor = Vector2f(1.f, 3.f);
	}
	else if (this->type == "Floor")
	{
		this->text.setString("F (" + std::to_string(this->types.x) + ", "+ std::to_string(this->types.y) + ")");
		this->textureRects = Object::getTextureRects(PreLoad::Textures::floors, Vector2i(4, 4));
		this->sprite.setTextureRect(this->textureRects[this->types.x][this->types.y]);
		this->constTextFactor = Vector2f(0.5f, 7.f);
	}
	else if (this->type == "Wall")
	{
		this->text.setString("W (" + std::to_string(this->types.x) + ", " + std::to_string(this->types.y) + ")");
		this->textureRects = Object::getTextureRects(PreLoad::Textures::walls, Vector2i(8, 7));
		this->sprite.setTextureRect(this->textureRects[this->types.x][this->types.y]);
		this->constTextFactor = Vector2f(0.5f, 7.f);
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


/*static*/ void Spawner::drawCurrentType(RenderWindow *window)
{
	if (!Spawner::inited) return;
	//Sprite
		//Scale
	Spawner::spritePtr->setScale(Spawner::constSizePtr->x * 4/ window->getDefaultView().getSize().x * window->getView().getSize().x,
		Spawner::constSizePtr->y * 4/ window->getDefaultView().getSize().y * window->getView().getSize().y);
		//Pos
	Spawner::spritePtr->setPosition(Vector2f(window->mapPixelToCoords(Vector2i(Spawner::constSpawnerPos))));
	//Text
	Vector2f windowFactor(WINDOWSIZE.x / WINDOWSIZE.y, WINDOWSIZE.y/ WINDOWSIZE.x);
	
	std::string prevString = Spawner::chosenText->getString();
	Spawner::chosenText->setString(std::to_string(GUI::entitiesPtr->size()));
	Spawner::chosenText->setFillColor(Color(180, 168, 255));
	Spawner::chosenText->setPosition(Vector2f(window->mapPixelToCoords(Vector2i(constSpawnerTextPos))));
	Spawner::chosenText->setScale(window->getView().getSize().x / window->getDefaultView().getSize().x, window->getView().getSize().y / window->getDefaultView().getSize().y);
	window->draw(*Spawner::spritePtr);
	window->draw(*Spawner::chosenText);
	
	//Revert temp changes
	Spawner::chosenText->setString(prevString);
}

void Spawner::changeCurrentType(Spawner* spawner)
{
	Spawner::inited = true;
	Spawner::chosenType = spawner->type;
	Spawner::chosenTypes = spawner->types;
	spawner->sprite.setScale(SCALE);
	Spawner::spriteRect = Vector2f(spawner->sprite.getGlobalBounds().width, spawner->sprite.getGlobalBounds().height);
	spawner->sprite.setScale(1.f, 1.f);

	Spawner::spritePtr = &spawner->sprite;
	Spawner::constSizePtr = &spawner->constSize;
	Spawner::chosenText = &spawner->text;
	Spawner::constSpawnerPos = Vector2f(WINDOWSIZE.x - 1.5*SCALE.x*Spawner::spritePtr->getGlobalBounds().width, WINDOWSIZE.y - 1.5*SCALE.y*Spawner::spritePtr->getGlobalBounds().height);
	Spawner::constSpawnerTextPos = Vector2f(Spawner::constSpawnerPos.x - Spawner::spritePtr->getGlobalBounds().width / 2 * SCALE.x, Spawner::constSpawnerPos.y - Spawner::spritePtr->getGlobalBounds().height / 2 * SCALE.y);
}

/*static*/ void Spawner::updateSpawn(const float & dt, const float & multiplier, const Vector2f & mousePos)
{
	Vector2f spawnPos;
	if (Spawner::chosenTypes == Vector2i(0, 0))
	{
		spawnPos = Vector2f(mousePos.x - Spawner::spriteRect.x / 2, mousePos.y - Spawner::spriteRect.y / 2);
	}
	else spawnPos = mousePos;
	
	if (Mouse::isButtonPressed(Mouse::Right) && Spawner::shouldSpawn)
	{
		Spawner::spawn(spawnPos);
		Spawner::shouldSpawn = false;
	}

	else if (!Mouse::isButtonPressed(Mouse::Right))
	{
		Spawner::shouldSpawn = true;
	}
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
		if (this->mouseHover(mousePos) && Mouse::isButtonPressed(Mouse::Left) && this->shouldPickUp)
		{
			Spawner::changeCurrentType(this);
			this->shouldPickUp = false;
		}
		else if (!Mouse::isButtonPressed(Mouse::Left))
		{
			this->shouldPickUp = true;
		}
	}
	this->GUI::update(dt, multiplier, mousePos);
}
void Spawner::spawn(const Vector2f &pos)
{
	if (Spawner::chosenType == "Hero") GUI::entitiesPtr->push_back(new Hero(pos));
	else if (Spawner::chosenType == "BigZombie") GUI::entitiesPtr->push_back(new BigZombie(pos));
	else if (Spawner::chosenType == "Demon") GUI::entitiesPtr->push_back(new Demon(pos));
	else if (Spawner::chosenType == "Skelet") GUI::entitiesPtr->push_back(new Skelet(pos));
	else if (Spawner::chosenType == "Floor") GUI::entitiesPtr->push_back(new Floor(pos, Spawner::chosenTypes));
	else if (Spawner::chosenType == "Wall") GUI::entitiesPtr->push_back(new Wall(pos, Spawner::chosenTypes));
	//else if Etc
}

//Static variable definitions
unsigned int Spawner::spawnAmount = 1;
std::string Spawner::chosenType = "";
Vector2i Spawner::chosenTypes = Vector2i(0, 0);
Vector2f Spawner::constSpawnerPos;
Vector2f Spawner::constSpawnerTextPos;
bool Spawner::shouldSpawn = true;
bool Spawner::inited = false;
Text *Spawner::chosenText;
Vector2f Spawner::spriteRect;
Sprite *Spawner::spritePtr;
Vector2f* Spawner::constSizePtr;