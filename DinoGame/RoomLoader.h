#pragma once
#include "GUI.h"
#include "Object.h"
#include "FileManager.h"
class RoomLoader : public GUI
{
private:
	bool shouldPickUp;
	static bool initedStatic;
	static bool shouldSave;
	static bool shouldDisplaytext;
	static float incer;
	static float cap;
	static FileManager fm;
	void init();
	static void renderText(RenderWindow * window);

public:
	static void initStatic();
	static std::string roomName;
	static Text text;
	static Vector2f constTextPos;
	static Vector2f constTextSize;
	RoomLoader(Vector2f pos, std::string fileName, GUI* parent);
	virtual ~RoomLoader();

	void loadRoom();
	virtual void show();
	virtual void hide();
	static void updateRoomSave(RenderWindow * window, const float & dt, const float & multiplier, const Vector2f & mousePos);
	virtual void draw(RenderWindow * window);
	virtual void update(const float &dt, const float &multiplier, const Vector2f &mousePos);
};

