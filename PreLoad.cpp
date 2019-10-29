#include "PreLoad.h"

PreLoad::PreLoad()
{
}


PreLoad::~PreLoad()
{
	delete PreLoad::Textures::knight;
	delete PreLoad::Textures::bigZombie;

	delete PreLoad::Textures::weapons;

	delete PreLoad::Textures::floors;
	delete PreLoad::Textures::walls;

	delete PreLoad::Fonts::font1;
	delete PreLoad::Hitboxes::hitboxlist;
}

void PreLoad::load()
{
	//Textures
	PreLoad::Textures::knight->loadFromFile("Textures/characters/knight/Orange/knight_orange.png");
	PreLoad::Textures::bigZombie->loadFromFile("Textures/characters/big_zombie/big_zombie.png");
	
	PreLoad::Textures::weapons->loadFromFile("Textures/Weapons/weapons.png");

	PreLoad::Textures::floors->loadFromFile("Textures/Terrain/floor/floors.png");
	PreLoad::Textures::walls->loadFromFile("Textures/Terrain/walls/walls.png");
	//Fonts
	PreLoad::Fonts::font1->loadFromFile("Fonts/Prime-Regular.ttf");

	//HitboxData

}

Texture *PreLoad::Textures::knight = new Texture;
Texture *PreLoad::Textures::bigZombie = new Texture;

Texture *PreLoad::Textures::weapons = new Texture;

Texture *PreLoad::Textures::floors = new Texture;
Texture *PreLoad::Textures::walls = new Texture;

Font *PreLoad::Fonts::font1 = new Font;

HitboxList *PreLoad::Hitboxes::hitboxlist = new HitboxList("hitboxList.txt");