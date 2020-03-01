#pragma once
#include "Slider.h"
#include "GUI.h"
#include "Folder.h"
#include "Grid.h"
#include "Tile.h"
#include "Spawner.h"

using namespace sf;

class Editor
{
private:
	Grid *worldGridPtr;
	std::vector<Object*> *entitesPtr;
	std::vector<GUI*> GUI_elements;
	RenderWindow* window;
	Object** cameraFollow;
	Vector2i prev;
	Vector2i current;
	RectangleShape mouseRect;
	Vector2f rectStartPoint;
	void init();
	void initGrid();
	void initGUI();
	void initSpawners();
	void resizeGridImage(const Vector2i &size);
	void resizeGrid(const Vector2i &size);
	void ensureGrid(Object* entity);
	Sprite gridSprite;
	bool showGrid;
	unsigned int chosenAmt;

public:
	Vector2f mousePos;
	struct MousePoint {
		Vector2f pos;
		bool set = false;
	};
	MousePoint mousePoint;
	bool followMouse;
	bool setStartPoint;
	Editor(Grid *worldGridPtr, std::vector<Object*> *entitesPtr, RenderWindow* window, Object** cameraFollow);
	~Editor();
	void delete_GUI_elements();

	void draw() const;
	void drawGrid() const;
	void showMouseInGrid(Vector2f &mousePos, Vector2i &tileSize, Vector2f &prevMousePos);
	static void zoomViewAt(sf::Vector2i pixel, RenderWindow& window, float zoom);
	void updateZoom(Event &event);
	void update(const float & dt, const float & multiplier);
};

