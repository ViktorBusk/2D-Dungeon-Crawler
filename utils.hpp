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
#define TILESIZE 16
#define PI 3.141592653
#define FRICTION 2.f
#define GRAVITY 9.82


struct Utils {
	static float distance2i(const sf::Vector2i &a, const sf::Vector2i &b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
	static std::string loadStringFromFile(const std::string &filename)
	{
		std::ifstream inFile;
		inFile.open(filename);

		//Check For Error
		if (inFile.fail())
		{
			std::cerr << "Utils::loadStringFromFile::Error Opening File" << std::endl;
			exit(1);
		}

		std::string line;
		std::string data;

		int rows = 0;

		while (!inFile.eof())
		{
			inFile >> line;
			data += line;
			rows++;
		}
		std::cout << data << std::endl;
		return data;
	}
};

#endif