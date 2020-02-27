#include "HitboxList.h"

HitboxList::HitboxList(std::string fileName)
{
	this->loadData(fileName);
	//this->printData();
}


HitboxList::~HitboxList()
{
	//delete hitboxData;
}

void HitboxList::loadData(const std::string & fileName)
{

	std::ifstream inFile;
	inFile.open(fileName);

	//Check For Error
	if (inFile.fail())
	{
		std::cerr << "Utils::loadStringFromFile::Error Opening File" << std::endl;
		exit(1);
	}

	std::vector<int> data;
	std::pair<std::string, std::vector<int>> pair;
	std::vector<std::pair<std::string, std::vector<int>>> vector1D;

	int rows = 0;
	int index = -1;
	std::string prevLine;

	while (!inFile.eof())
	{
		float intLine;
		std::string stringLine;
		if (rows % 7 == 0)
		{
			if (index >= 0)
			{
				pair.second = data;
				vector1D.push_back(pair);
				data.clear();
			}
			index++;
			inFile >> stringLine;
			if (prevLine != stringLine)
			{
				this->hitboxData.push_back(vector1D);
				vector1D.clear();
				prevLine = stringLine;
				index = 0;
			}
			pair.first = std::to_string(index) + "." + stringLine;
		}
		else
		{
			inFile >> intLine;
			data.push_back(intLine);
		}
		rows++;
	}
}


void HitboxList::printData() const
{
	for (size_t i = 0; i < this->hitboxData.size(); i++)
	{
		for (size_t j = 0; j < this->hitboxData[i].size(); j++)
		{
			std::cout << this->hitboxData[i][j].first << std::endl;
		}
	}
}

