#pragma once
#include "Object.h"
#include "GUI.h"


using namespace sf;

class Folder : public GUI
{
private:
	void init();
	bool contentState;
	bool mousePressedState;
	bool hidden;
	Texture* openImg;
	Texture* closedImg;
	std::vector<GUI*> content;

public:
	Folder(std::string text, Folder* parent, Vector2f pos = Vector2f(0, 0));
	~Folder();

	virtual void draw(RenderWindow *window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
	void open();
	void close();
	void moveLower_GUI_elements(bool down);
	void addContent(GUI *moreContent);
	void addContent(std::vector<GUI*> moreContent);
	virtual void show();
	virtual void hide();
};

