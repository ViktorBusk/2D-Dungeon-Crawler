#include "Editor.h"


Editor::Editor(Grid *worldGridPtr, std::vector<Object*> *entitesPtr, RenderWindow* window, Object** cameraFollow)
{
	this->worldGridPtr = worldGridPtr;
	this->entitesPtr = entitesPtr;
	this->window = window;
	this->cameraFollow = cameraFollow;
	*this->cameraFollow = NULL;
	this->init();
}

Editor::~Editor()
{
	this->delete_GUI_elements();
}

void Editor::delete_GUI_elements()
{
	for (GUI* element: this->GUI_elements)
	{
		delete element;
	}
}

void Editor::init()
{
	this->mouseRect.setFillColor(Color(100, 255, 100, 50));
	this->setStartPoint = true;
	this->followMouse = false;
	this->chosenAmt = 0;
	this->initGrid();
	this->initGUI();
}

void Editor::initGrid()
{
	this->gridSprite.setTexture(*PreLoad::Textures::grid);
	this->gridSprite.setScale(1.40625, 1.40625);
	this->resizeGridImage(this->worldGridPtr->getSize());
	this->showGrid = true;
}

void Editor::initGUI()
{
	GUI::GUI_elements = &this->GUI_elements;

	//Order of the partentfolders are important!!!
	//////////////////////////////PARENTFOLDERS//////////////////////////////
	Folder* floorFolder = new Folder("Floor", NULL, Vector2f(10.f, 10.f));
	this->GUI_elements.push_back(floorFolder);
	
	Folder* characterFolder = new Folder("Characters", NULL, Vector2f(10.f, 35.f));
	this->GUI_elements.push_back(characterFolder);

	Folder* doorFolder = new Folder("Doors", NULL, Vector2f(10.f, 60.f));
	this->GUI_elements.push_back(doorFolder);

	Folder* weaponFolder = new Folder("Weapons", NULL, Vector2f(10.f, 85.f));
	this->GUI_elements.push_back(weaponFolder);

	Folder* wallFolder = new Folder("Walls", NULL, Vector2f(10.f, 110.f));
	this->GUI_elements.push_back(wallFolder);
	//////////////////////////////////////////////////////////////////////////

	Folder* testFolder0 = new Folder("Test Folder", floorFolder, Vector2f(10.f, 35.f));
	this->GUI_elements.push_back(testFolder0);
	floorFolder->addContent(testFolder0);

	Folder* testFolder1 = new Folder("Test Folder", characterFolder, Vector2f(10.f, 60.f));
	this->GUI_elements.push_back(testFolder1);
	characterFolder->addContent(testFolder1);

	Folder* testFolder2 = new Folder("Test Folder", testFolder1, Vector2f(10.f, 85.f));
	this->GUI_elements.push_back(testFolder2);
	testFolder1->addContent(testFolder2);
	
	
	Spawner* bigZombieSpawner = new Spawner(Vector2f(0.f, 100.f), PreLoad::Textures::bigZombie, "BigZombie", testFolder2, this->entitesPtr);
	this->GUI_elements.push_back(bigZombieSpawner);
	testFolder2->addContent(bigZombieSpawner);

	Spawner* demonSpawner = new Spawner(Vector2f(0.f, 130.f), PreLoad::Textures::demon, "Demon", testFolder2, this->entitesPtr);
	this->GUI_elements.push_back(demonSpawner);
	testFolder2->addContent(demonSpawner);

	Spawner* heroSpawner = new Spawner(Vector2f(0.f, 160.f), PreLoad::Textures::knight, "Hero", testFolder2, this->entitesPtr);
	this->GUI_elements.push_back(heroSpawner);
	testFolder2->addContent(heroSpawner);

	Spawner* skeletSpawner= new Spawner(Vector2f(0.f, 190.f), PreLoad::Textures::skelet, "Skelet", testFolder2, this->entitesPtr);
	this->GUI_elements.push_back(skeletSpawner);
	testFolder2->addContent(skeletSpawner);
}

void Editor::initSpawners()
{
	
}

void Editor::resizeGridImage(const Vector2i & size)
{
	Vector2f rectSize(this->gridSprite.getTexture()->getSize().x / 100, this->gridSprite.getTexture()->getSize().y / 100);
	this->gridSprite.setTextureRect(IntRect(0, 0, rectSize.x*size.x, rectSize.y*size.x));

}

void Editor::resizeGrid(const Vector2i & size)
{
	this->resizeGridImage(size);
	this->worldGridPtr->resize(size);
}

void Editor::ensureGrid(Object* entity)
{
	Tile* tile = dynamic_cast<Tile*>(entity);
	if (tile != NULL)
	{
		int padding = TILESIZE * SCALE.x;
		entity->setPosition(Vector2f(round(entity->getPos().x), round(entity->getPos().y)));
		int zeroLevelX = entity->getPos().x;
		int zeroLevelY = entity->getPos().y;
		if (zeroLevelX % padding >= (padding/2 - 1) && zeroLevelX % padding < padding) entity->setPosition(Vector2f(entity->getPos().x + 1, entity->getPos().y));
		if (zeroLevelX % padding < (padding / 2 - 1) && zeroLevelX % padding > 0) entity->setPosition(Vector2f(entity->getPos().x - 1, entity->getPos().y));
		if (zeroLevelY % padding >= (padding / 2 - 1) && zeroLevelY % padding < padding) entity->setPosition(Vector2f(entity->getPos().x, entity->getPos().y + 1));
		if (zeroLevelY % padding < (padding / 2 - 1) && zeroLevelY % padding > 0) entity->setPosition(Vector2f(entity->getPos().x, entity->getPos().y - 1));

		if (zeroLevelX % padding <= -(padding / 2 - 1) && zeroLevelX % padding > -padding) entity->setPosition(Vector2f(entity->getPos().x - 1, entity->getPos().y));
		if (zeroLevelX % padding > -(padding / 2 - 1) && zeroLevelX % padding < 0) entity->setPosition(Vector2f(entity->getPos().x + 1, entity->getPos().y));
		if (zeroLevelY % padding <= -(padding / 2 - 1) && zeroLevelY % padding > -padding) entity->setPosition(Vector2f(entity->getPos().x, entity->getPos().y - 1));
		if (zeroLevelY % padding > -(padding / 2 - 1) && zeroLevelY % padding < -0) entity->setPosition(Vector2f(entity->getPos().x, entity->getPos().y + 1));
	}
}

void Editor::draw() const
{
	for (GUI* element: this->GUI_elements)
	{
		element->draw(this->window);
	}
}

void Editor::drawGrid() const
{
	if (this->showGrid)
	{
		this->window->draw(this->gridSprite);
	}
}

void Editor::showMouseInGrid(Vector2f &mousePos, Vector2i &tileSize, Vector2f &prevMousePos)
{
	if (this->prev.x < 0 || this->prev.y < 0 || this->prev.x >= this->worldGridPtr->getSize().x || this->prev.y >= this->worldGridPtr->getSize().y)
	{

	}
	else {
		this->worldGridPtr->cells[this->prev.x][this->prev.y].color = Cell::baseColor;
		this->worldGridPtr->updateCellTexture(Vector2i(this->prev.x, this->prev.y));
	}

	if (this->current.x < 0 || this->current.y < 0 || this->current.x >= this->worldGridPtr->getSize().x || this->current.y >= this->worldGridPtr->getSize().y)
	{

	}
	else {
		this->worldGridPtr->cells[this->current.x][this->current.y].color = Color(0, 255, 255, 150);
		this->worldGridPtr->updateCellTexture(Vector2i(this->current.x, this->current.y));
	}

	prevMousePos = mousePos;
}

void Editor::zoomViewAt(Vector2i pixel, RenderWindow & window, float zoom)
{
	const Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	View view{ window.getView() };
	view.zoom(zoom);
	window.setView(view);
	const Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
	window.setView(view);
}

void Editor::updateZoom(Event &event)
{
	if (event.mouseWheelScroll.delta > 0)
		this->zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *this->window, (1.f / 1.1));
	else if (event.mouseWheelScroll.delta < 0)
		this->zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, *this->window, 1.1);
}

void Editor::update(const float & dt, const float & multiplier)
{
	//Variables
	static Vector2i tileSize(SCALE.x*TILESIZE, SCALE.y*TILESIZE);
	this->mousePos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window), this->window->getView());
	static Vector2f prevMousePos = mousePos;
	
	//Clear Previous
	this->prev.x = (prevMousePos.x / tileSize.x);
	this->prev.y = floor(prevMousePos.y / tileSize.y);
	
	this->current.x = floor(mousePos.x / tileSize.x);
	this->current.y = floor(mousePos.y / tileSize.y);
	
	this->showMouseInGrid(mousePos, tileSize, prevMousePos);

	//Interaction With GUI
	for (GUI* element : this->GUI_elements)
	{
		element->update(dt, multiplier, this->mousePos);
	}

	//Interaction With Entities
	//--Ported from JS-version--------------
	for (Object* entity : *this->entitesPtr)
	{
		if(entity->chosen) chosenAmt++;
		if (entity->chosen && entity->mouseColision(this->window) && this->setStartPoint && Mouse::isButtonPressed(Mouse::Left))
		{
			this->followMouse = true;
			this->mousePoint.set = true;
			if(this->chosenAmt == 2) *this->cameraFollow = entity;
		}
	}

	bool someChosen = false;

	this->chosenAmt = this->entitesPtr->size();
	for (Object* entity : *this->entitesPtr)
	{
		if (!this->followMouse && Mouse::isButtonPressed(Mouse::Left))
		{
			if (!Utils::AABBColision(this->mouseRect, entity->getHitbox())) 
				entity->chosen = false;
			if(Utils::AABBColision(this->mouseRect, entity->getHitbox()))
				entity->chosen = true;
		}
		this->ensureGrid(entity); //Ensures the grid if the entity is a tile
		if (entity->chosen) someChosen = true;
		else this->chosenAmt--;
	}
	if (!someChosen) *this->cameraFollow = NULL;

	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		this->followMouse = false;
		this->setStartPoint = true;
	}
	if (this->followMouse && this->mousePoint.set)
	{
		this->mousePoint.pos = mousePos;
		this->mousePoint.set = false;
	}
	if (Mouse::isButtonPressed(Mouse::Left) && !this->followMouse)
	{
		if (this->setStartPoint)
		{
			this->rectStartPoint = mousePos;
			this->setStartPoint = false;
		}
		this->mouseRect.setPosition(this->rectStartPoint);
		this->mouseRect.setSize(Vector2f(mousePos.x - this->rectStartPoint.x, mousePos.y - this->rectStartPoint.y));
		this->window->draw(this->mouseRect);
	}
	//-------------------------------------
}
