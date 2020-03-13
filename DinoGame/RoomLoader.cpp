#include "RoomLoader.h"

RoomLoader::RoomLoader(Vector2f pos, std::string fileName, GUI* parent) :
	GUI(pos, parent)
{
	this->text.setString(fileName);
	this->fm.openFile(fileName);
	this->init();
}


RoomLoader::~RoomLoader()
{

}


void RoomLoader::init()
{

	this->sprite.setScale(1.f, 1.f);
	this->constTextScale = Vector2f(0.5, 0.5);
	this->text.setScale(this->constTextScale);
	this->text.setFont(*PreLoad::Fonts::font1);
	this->constPos = this->sprite.getPosition();
	this->constSize = this->sprite.getScale();
	this->texture = PreLoad::Textures::floors;
	this->sprite.setTexture(*this->texture);
	this->currentTextPos = Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / this->constTextFactor.x, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / this->constTextFactor.y);
	this->text.setPosition(this->currentTextPos);

	std::vector<std::vector<IntRect>> textureRects;
	textureRects = Object::getTextureRects(PreLoad::Textures::floors, Vector2i(4, 4));
	this->sprite.setTextureRect(textureRects[0][0]);
	this->constTextFactor = Vector2f(0.5f, 7.f);
	this->constDimensions = this->sprite.getGlobalBounds();
	this->shouldPickUp = true;
	this->visableState = false;
}

/*static*/ void RoomLoader::initStatic()
{
	if (!RoomLoader::initedStatic)
	{
		RoomLoader::text.setPosition(RoomLoader::constTextPos);
		RoomLoader::text.setString("Saved room: " + RoomLoader::roomName);
		RoomLoader::text.setFont(*PreLoad::Fonts::font1);
		RoomLoader::text.setFillColor(Color(180, 168, 255));
		RoomLoader::text.setOutlineColor(Color::Black);
		RoomLoader::text.setOutlineThickness(3.f);
		RoomLoader::text.setLetterSpacing(1.4f);
	}
	RoomLoader::initedStatic = true;
}

void RoomLoader::renderText(RenderWindow * window)
{
	GUI::mapTextToWindowCoords(window, &RoomLoader::text, RoomLoader::constTextPos, RoomLoader::constTextSize);
	window->draw(RoomLoader::text);
}


void RoomLoader::loadRoom()
{
	this->fm.read();

	std::string s = "10";

	int i;
	std::istringstream(s) >> i;
	std::cout << i << '\n';
}

void RoomLoader::show()
{
	this->visableState = true;
}

void RoomLoader::hide()
{
	this->visableState = false;
}

/*static*/ void RoomLoader::updateRoomSave(RenderWindow * window, const float & dt, const float & multiplier, const Vector2f & mousePos)
{
	if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S) && RoomLoader::shouldSave)
	{
		RoomLoader::fm.openFile(RoomLoader::roomName);
		for (Object* entity: *GUI::entitiesPtr)
		{
			std::string name = typeid(*entity).name();
			RoomLoader::fm.writeLine(name + " x: " + std::to_string(entity->getPos().x) + 
											" y: " + std::to_string(entity->getPos().y));
		}
		RoomLoader::shouldDisplaytext = true;
		RoomLoader::shouldSave = false;
		
	}
	if (!Keyboard::isKeyPressed(Keyboard::LControl) && !Keyboard::isKeyPressed(Keyboard::S) && !RoomLoader::shouldSave)
	{
		RoomLoader::shouldSave = true;
	}
	if (RoomLoader::shouldDisplaytext)
	{
		RoomLoader::incer += dt * multiplier;
		RoomLoader::renderText(window);
		if(RoomLoader::incer >= RoomLoader::cap){
			RoomLoader::incer = 0;
			RoomLoader::shouldDisplaytext = false;
		}
	}
}

void RoomLoader::draw(RenderWindow * window)
{
	if (this->visableState)
	{
		this->mapToWindowCoords(window);
		window->draw(this->sprite);
		this->drawText(window);
	}
	this->GUI::draw(window);
}

void RoomLoader::update(const float & dt, const float & multiplier, const Vector2f & mousePos)
{
	if (this->visableState)
	{
		if (this->mouseHover(mousePos) && Mouse::isButtonPressed(Mouse::Left) && this->shouldPickUp)
		{

			this->shouldPickUp = false;
		}
		else if (!Mouse::isButtonPressed(Mouse::Left))
		{
			this->shouldPickUp = true;
		}
	}
	this->GUI::update(dt, multiplier, mousePos);
}

bool RoomLoader::initedStatic = false;
bool RoomLoader::shouldSave = true;
float RoomLoader::incer = 0.f;
float RoomLoader::cap = 200.f;
bool RoomLoader::shouldDisplaytext = false;
FileManager RoomLoader::fm;
std::string RoomLoader::roomName = "test.txt";
Text RoomLoader::text;
Vector2f RoomLoader::constTextPos = Vector2f(WINDOWSIZE.x*0.4f, WINDOWSIZE.y*0.95f);
Vector2f RoomLoader::constTextSize = Vector2f(1.f, 1.f);
