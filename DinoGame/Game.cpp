#include "Game.h"

Game::Game()
{
	this->init();
}

Game::~Game()
{
	delete this->map;
	delete this->window;
	delete this->worldGrid;
	delete this->editor;
	this->clearEntityVec();
}

void Game::init()
{
	//Init Random
	srand(time(NULL));

	//Init Window
	const Vector2i windowSize(800, 800);
	VideoMode normalMode = VideoMode(windowSize.x, windowSize.y);
	VideoMode desktopMode = VideoMode().getDesktopMode();

	this->window = new RenderWindow(desktopMode, "Dungeon Game", Style::None);
	//window->setVerticalSyncEnabled(true);

	//Init Clock
	this->framerateLimit = 100000.f;
	window->setFramerateLimit(framerateLimit);
	this->multiplier = 144.f;

	///////////////////--TESTING--/////////////////////
	//Init Entites
	this->map = new Dungeon(this->levelData.mapSize, this->levelData.mapScale, this->levelData.maxNrOfRooms, this->levelData.roomSize);
	this->map->generate();
	this->map->setPosition(Vector2f(-500.f, 0.f));
	
	//Init Grid
	this->initGrid();
	for (size_t i = 0; i < 10; i++)
	{
		this->entites.push_back(new Weapon(Vector2f(rand() % this->window->getSize().x, rand() % this->window->getSize().y), PreLoad::Textures::weapons, Vector2i(20, 1), SCALE, rand() % 20, 10, 10, true));
	}
	for (size_t i = 0; i < 10; i++)
	{
		this->entites.push_back(new BigZombie(Vector2f(rand()%this->window->getSize().x, rand() % this->window->getSize().y)));
	}
	this->entites.push_back(new Wall(Vector2f(3*TILESIZE*SCALE.x, 3*TILESIZE*SCALE.y), Vector2i(1, 0)));
	this->entites.push_back(new Wall(Vector2f(3*TILESIZE*SCALE.x, 4*TILESIZE*SCALE.y), Vector2i(2, 0)));
	this->entites.push_back(new Wall(Vector2f(3*TILESIZE*SCALE.x, 5*TILESIZE*SCALE.y), Vector2i(3, 0)));

	//Player init
	this->player = new Hero(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2));
	this->entites.push_back(player);
	///////////////////////////////////////////////////

	//Init Camera
	this->cameraFollow = this->player;

	//Init Editor
	this->editor = new Editor(this->worldGrid, &this->entites, this->window, &this->cameraFollow);
}

void Game::initGrid()
{
	//this->worldGrid = new Grid(this->map->getGridSize()*this->map->getTilesPerCell(),SCALE.x*TILESIZE, true);
	this->worldGrid = new Grid(Vector2i(50, 50), SCALE.x*TILESIZE, true);
	this->worldGrid->updateTexture();
}

void Game::start()
{
	this->startLoop();
}

void Game::startLoop()
{
	bool first = true;
	while (this->window->isOpen())
	{
		this->pollEvents();
		//Game clock
		this->updateClock();

		//Draw
		this->window->clear(Color(255, 255, 255));
		this->worldGrid->draw(window);
		if (this->editor != NULL) this->editor->drawGrid();
		this->map->draw(window);
		//Sort based on colision order
		std::sort(entites.begin(), entites.end(), [](const Object* obj1, const Object* obj2) {
			return obj1->getColisionIndex() < obj2->getColisionIndex();
		});
		for (auto *entity : entites)
		{
			if (!first)
			{
				this->addObjectToWorldGrid(entity);
				entity->updateColisions();
			}
		}
		//Sort based on Z-index
		std::sort(entites.begin(), entites.end(), [](const Object* obj1, const Object* obj2) {
			return obj1->getZIndex() < obj2->getZIndex();
		});
		for (auto *entity : entites)
		{
			entity->update(this->dt, this->multiplier);
			//this->ensureBounds(entity);
			if (this->editor != NULL) entity->moveWithMouse(this->editor->mousePos, this->editor->followMouse, this->editor->mousePoint.pos);
			Vector2f acutalPos = entity->getPos();
			Vector2f pixelPos = Vector2f(round(acutalPos.x), round(acutalPos.y));
			entity->setPosition(pixelPos);
			entity->draw(this->window);
			entity->setPosition(acutalPos);
		}
	
		//Editor
		if (this->editor != NULL)
		{
			this->editor->update(this->dt, this->multiplier);
			this->editor->draw();
		}

		//Game view/camera
		if (this->cameraFollow != NULL)
		{
			this->updateView(this->cameraFollow->getCenter());
		}

		this->window->display();
		first = false;
		this->clearWorldGrid(); 
	}
}

void Game::pollEvents()
{
	//Events
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			this->window->close();
		if (event.type == Event::MouseWheelScrolled)
			if(this->editor != NULL) this->editor->updateZoom(event);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) this->window->close();		
}

void Game::updateClock()
{
	static float incer = 0.f;
	const static float cap = 30.f;
	this->dt = this->clock.restart().asSeconds();
	this->FPS = 1.f / dt;

	if (incer >= cap)
	{
		incer = 0;
		this->printFPS();
		
	}
	incer+=this->dt*this->multiplier;
}

void Game::printFPS()
{
	std::cout << this->FPS << std::endl;
}

void Game::clearEntityVec()
{
	for (size_t i = 0; i < this->entites.size(); i++)
	{
		delete entites[i];
	}
	entites.clear();
}

void Game::updateView(const Vector2f &targetPos)
{
	View view = this->window->getView();
	Vector2f movement = targetPos - view.getCenter();
	view.move(Vector2f(movement.x*dt, movement.y*dt));
	this->window->setView(view);

	//view.setCenter(Vector2f(this->player->getCenter().x, this->player->getCenter().y));
	//this->window->setView(view);
}

void Game::ensureBounds(Object * entity)
{
	
}

void Game::addObjectToWorldGrid(Object * object)
{
	if (object->getHitboxComponent() == NULL) return;
	object->setWorldGridPos();
	if (object->getWorldGridPos().topLeft.x < 0) return;
	if (object->getWorldGridPos().topLeft.y < 0) return;
	for (size_t x = object->getWorldGridPos().topLeft.x; x <= object->getWorldGridPos().bottomRight.x; x++)
	{
		for (size_t y = object->getWorldGridPos().topLeft.y; y <= object->getWorldGridPos().bottomRight.y; y++)
		{
			if (x < this->worldGrid->getSize().x && y < this->worldGrid->getSize().y)
			{
				object->addColisionVec(&this->worldGrid->cells[x][y].Objects);
				this->worldGrid->cells[x][y].Objects.push_back(object);
			}
		}
	}
}

void Game::clearWorldGrid()
{
	for (size_t x = 0; x < this->worldGrid->getSize().x; x++)
	{
		for (size_t y = 0; y < this->worldGrid->getSize().y; y++)
		{
			this->worldGrid->cells[x][y].clearVec();
		}
	}
}
