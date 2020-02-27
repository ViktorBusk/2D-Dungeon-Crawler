#include "Cell.h"

const Color Cell::baseColor = Color(70, 70, 70);

Cell::Cell(Vector2f pos, float size, const unsigned int &cellType, bool worldCell)
{
	this->pos = pos;
	this->size = size;
	this->currentType = &cellType;
	this->init();
}


Cell::~Cell()
{
	
}

void Cell::init()
{
	this->color = Cell::baseColor;

	//Square
	this->square.setPosition(this->pos);
	this->square.setFillColor(this->color);
	this->square.setOutlineColor(Color::White);
	//this->square.setOutlineThickness(this->size / 20);
	this->square.setSize(Vector2f(this->size, this->size));
	
	//Sprite
	this->sprite.setPosition(this->pos);
	
	this->walkable = true;
}


void Cell::setType(const unsigned int &newType)
{
	switch (newType)
	{
	case none:
		this->color = Color::Black;
		break;
	case vCorridor:
		this->color = Color::Blue;
		break;
	case hCorridor:
		this->color = Color::Red;
		break;
	case room:
		this->color = Color(255, 127, 80); //Orange
		break;
	case vR_hUp:
		this->color = Color::Cyan;
		break;
	case vL_hUp:
		this->color = Color::Magenta;
		break;
	case vR_hD:
		this->color = Color::Green;
		break;
	case vL_hD:
		this->color = Color::Yellow;
		break;
	case vL_hUp_vR:
		this->color = Color(147, 112, 219); //Purple
		break;
	case hUp_vR_hD:
		this->color = Color(102, 102, 0); //Olive
		break;
	case vL_hD_vR:
		this->color = Color(255, 153, 153); //Flesh
		break;
	case hUp_vL_hD:
		this->color = Color(40, 80, 40); //DarkGreen
		break;
	case vR_hUp_hD_vR:
		this->color = Color(153, 255, 153); //LightGreen
		break;
	case corner:
		this->color = Color(76, 135, 200);
		break;
	}
	this->currentType = &newType;
}

void Cell::setUnwalkable()
{
	this->walkable = false;
}

void Cell::setWalkable()
{
	this->walkable = true;
}

const unsigned int &Cell::getType() const
{
	return *this->currentType;
}

void Cell::clearVec()
{
	this->Objects.clear();
}

void Cell::setTexture(Texture * texture)
{
	this->sprite.setTexture(*texture);
}

void Cell::draw(RenderWindow * window) const
{
	window->draw(this->sprite);
}

void Cell::update()
{
	this->square.setFillColor(this->color);
}

