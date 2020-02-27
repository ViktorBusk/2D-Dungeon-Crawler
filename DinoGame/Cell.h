#pragma once
#include "utils.hpp"
#include "Object.h"

using namespace sf;

class Cell
{
private:
	void init();

public:
	Vector2f pos;
	float size;
	Color color;
	const static Color baseColor;
	RectangleShape square;
	bool walkable;
	Sprite sprite;

	static const unsigned int none = 0; //Black
	static const unsigned int room = 3; //Orange
	static const unsigned int corner = 13; //Temp
	//---------------2 openings---------------
	static const unsigned int vCorridor = 1; //Blue
	static const unsigned int hCorridor = 2; //Red
	//----------------Corners------------------
	static const unsigned int vR_hUp = 4; //Cyan
	static const unsigned int vL_hUp = 5; //Magneta
	static const unsigned int vR_hD = 6; //Green
	static const unsigned int vL_hD = 7; //Yellow
	//--------------3 openings-----------------
	static const unsigned int vL_hUp_vR = 8; //Purple
	static const unsigned int hUp_vR_hD = 9; //Olive
	static const unsigned int vL_hD_vR = 10; //Flesh
	static const unsigned int hUp_vL_hD = 11; //DarkGreen
	//--------------4 openings---------------
	static const unsigned int vR_hUp_hD_vR = 12; //LightGreen

	int const unsigned *currentType;
	//---------------WorldCells------------------//
	std::vector<Object*> Objects;

	Cell(Vector2f pos, float size, const unsigned int &cellType, bool worldCell);
	~Cell();

	//Accessors
	const unsigned int &getType() const;
	//Modifiers
	void setType(const unsigned int &newType);
	void setUnwalkable();
	void setWalkable();
	//Functions
	void clearVec();
	void setTexture(Texture* texture);
	void draw(RenderWindow *window) const;
	void update();
};

