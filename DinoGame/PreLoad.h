#pragma once
#include "utils.hpp"
#include "HitboxList.h"

using namespace sf;

class PreLoad {
public:
	struct Textures
	{
		//https://www.toptal.com/developers/css/sprite-generator/
		//Padding: 5 | Left-right
		
		//Characters
		static Texture* knight;
		static Texture* bigZombie;
		static Texture* weapons;
		static Texture* demon;
		static Texture* skelet;

		//Tiles
		static Texture* floors;
		static Texture* walls;

		//UI
		static Texture* grid;
		static Texture* openFolder;
		static Texture* closedFolder;

	};
	struct Fonts {
		static Font* font1;
	};
	struct Hitboxes {
		static HitboxList* hitboxlist;
	};
	static void load();
	PreLoad();
	~PreLoad();
};


