#include "Game.h"
#include "PreLoad.h"

int main()
{
	PreLoad::load();
	Game game;
	game.start();
	
	return 0;
}