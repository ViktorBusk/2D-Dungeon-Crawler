#pragma once
#include "utils.hpp"

class HitboxList
{
private:

public:
	//The order of the hitboxes are the same as the "Spritesheets" folder
	std::vector<std::vector<std::pair<std::string, std::vector<int>>>> hitboxData;
	
	HitboxList(std::string fileName);
	~HitboxList();

	void loadData(const std::string &fileName);
	void printData() const;
};

