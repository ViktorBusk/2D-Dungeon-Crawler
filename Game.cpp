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

	this->window = new RenderWindow(normalMode, "Dungeon Game", Style::None);
	//window->setVerticalSyncEnabled(true);

	//Init Clock
	this->framerateLimit = 100000.f;
	window->setFramerateLimit(framerateLimit);
	this->multiplier = 144.f;

	///////////////////--TESTING--/////////////////////
	//Init Entites
	this->map = new Dungeon(this->levelData.mapSize, this->levelData.mapScale, this->levelData.maxNrOfRooms, this->levelData.roomSize);
	this->map->generate();
	
	//Init Grid
	this->initGrid();
	for (size_t i = 0; i < 10; i++)
	{
		this->entites.push_back(new Weapon(Vector2f(rand() % this->window->getSize().x, rand() % this->window->getSize().y), PreLoad::Textures::weapons, Vector2i(20, 1), SCALE, rand() % 20, 10, 10, true));
	}
	for (size_t i = 0; i < 20 ; i++)
	{
		this->entites.push_back(new BigZombie(Vector2f(rand()%this->window->getSize().x, rand() % this->window->getSize().y), PreLoad::Textures::bigZombie));
	}
	//this->entites.push_back(new Wall(Vector2f(3*TILESIZE*SCALE.x, 3*TILESIZE*SCALE.y), Vector2i(1, 0), -1, 0));

	//Player init
	this->player = new Hero(Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2), PreLoad::Textures::knight);
	this->entites.push_back(player);
	///////////////////////////////////////////////////
}

void Game::initGrid()
{
	//this->worldGrid = new Grid(this->map->getGridSize()*this->map->getTilesPerCell(),SCALE.x*TILESIZE, true);
	this->worldGrid = new Grid(Vector2i(30, 30), SCALE.x*TILESIZE, true);
	this->worldGrid->updateTexture();
}

void Game::start()
{
	this->startLoop();
}

void Game::startLoop()
{
	bool first = true;
	//Update Once
	for (auto *entity : entites)
	{
		entity->update(this->dt, this->multiplier);
	}
	while (this->window->isOpen())
	{
		this->pollEvents();
		//Game clock
		this->updateClock();

		//Draw
		this->window->clear(Color(255, 255, 255));
		this->worldGrid->draw(window);
		//this->map->draw(window);
		std::sort(entites.begin(), entites.end(), [](const Object* obj1, const Object* obj2) {
			return obj1->getZIndex() < obj2->getZIndex();
		});
		for (auto *entity : entites)
		{
			this->addObjectToWorldGrid(entity);
			if(!first) entity->updateColisions();
		}
		for (auto *entity : entites)
		{
			entity->update(this->dt, this->multiplier);
			entity->draw(this->window);
		}
	
		//Game view/camera
		this->updateView(player->getCenter());		

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

void Game::addObjectToWorldGrid(Object * object)
{
	if (object->getWorldGridPos().topLeft.x < 0) return;
	if (object->getWorldGridPos().topLeft.y < 0) return;
	for (size_t x = object->getWorldGridPos().topLeft.x; x <= object->getWorldGridPos().bottomRight.x; x++)
	{
		for (size_t y = object->getWorldGridPos().topLeft.y; y <= object->getWorldGridPos().bottomRight.y; y++)
		{
			if (x < this->worldGrid->cells.size() && y < this->worldGrid->cells.size())
			{
				object->addColisionVec(&this->worldGrid->cells[x][y].Objects);
				this->worldGrid->cells[x][y].Objects.push_back(object);
			}
		}
	}
}

void Game::clearWorldGrid()
{
	for (size_t x = 0; x < this->worldGrid->cells.size(); x++)
	{
		for (size_t y = 0; y < this->worldGrid->cells[x].size(); y++)
		{
			this->worldGrid->cells[x][y].clearVec();
		}
	}
}
