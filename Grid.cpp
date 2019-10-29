#include "Grid.h"


void Grid::init()
{
	for (size_t x = 0; x < this->size.x; x++)
	{
		std::vector<Cell> temp;
		for (size_t y = 0; y < this->size.y; y++)
		{
			temp.push_back(Cell(Vector2f(x*scale, y*scale), scale, Cell::none, this->worldGrid));
		}
		cells.push_back(temp);
	}
	this->updateTexture();
}

Grid::Grid(Vector2i size, float scale, bool worldGrid)
{
	this->size = size;
	this->scale = scale,
	this->worldSize = Vector2f(size.x*scale, size.y*scale);
	this->worldGrid = worldGrid;
	this->init();
}


Grid::~Grid()
{
}

void Grid::updateTexture()
{
	this->texture.clear();
	this->texture.create(this->worldSize.x, this->worldSize.y);
	for (size_t x = 0; x < this->size.x; x++)
	{
		for (size_t y = 0; y < this->size.y; y++)
		{
			cells[x][y].update();
			this->texture.draw(cells[x][y].square);
		}
	}
	this->sprite.setTexture(this->texture.getTexture());
	this->texture.display();
}

void Grid::draw(RenderWindow * window)
{
	window->draw(this->sprite);
}

void Grid::update(const float & dt, const float & multiplier)
{

}

