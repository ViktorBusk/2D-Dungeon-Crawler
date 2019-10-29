#pragma once
#include "utils.hpp"
#include "HitboxList.h"

using namespace sf;

class PreLoad {
public:
	struct Textures
	{
		//Characters
		static Texture* knight;
		static Texture* bigZombie;
		static Texture* weapons;

		//Tiles
		static Texture* floors;
		static Texture* walls;

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


