#pragma once
#include "utils.hpp"

using namespace sf;

class AnimationComponent
{
private:
	Sprite* spritePtr;
	Texture *spriteSheet;
	float incer;
	float cap;
	unsigned int index;


public:
	unsigned int animationIndex;
	std::vector<std::vector<IntRect>> textureRects;
	std::vector<IntRect*> idle;
	std::vector<IntRect*> walking;
	std::vector<IntRect*> currentAnim;
	std::vector<IntRect*> *previousAnim;

	AnimationComponent();
	~AnimationComponent();
};

