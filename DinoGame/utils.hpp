#pragma once
#ifndef UTILS
#define UTILS

//SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"
//Others
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>

//Game Constants (change later)
#define SCALE Vector2f(3.f, 3.f)
#define TILESIZE 15
#define PI 3.141592653
#define FRICTION 2.f
#define GRAVITY 9.82


struct Utils {
	static float distance2i(const sf::Vector2i &a, const sf::Vector2i &b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
	static bool AABBColision(const sf::RectangleShape &r1, const sf::RectangleShape &r2)
	{
		sf::Vector2f r1Pos = r1.getPosition();
		sf::Vector2f r1Size(r1.getGlobalBounds().width, r1.getGlobalBounds().height);

		sf::Vector2f r2Pos = r2.getPosition();
		sf::Vector2f r2Size(r2.getGlobalBounds().width, r2.getGlobalBounds().height);

		return(r1Pos.x < r2Pos.x + r2Size.x &&
			r1Pos.x + r1Size.x > r2Pos.x &&
			r1Pos.y < r2Pos.y + r2Size.y &&
			r1Pos.y + r1Size.y > r2Pos.y);
	}
};

#endif