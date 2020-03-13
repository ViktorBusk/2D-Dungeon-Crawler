#pragma once
#include "utils.hpp"

using namespace sf;

class FileManager
{
private:
	void init();
	std::ofstream writer;
	std::ifstream reader;
	std::string currentFile;

public:
	FileManager();
	~FileManager();

	//Accessors
	inline std::string getCurrentFileName() const { return this->currentFile; };

	//Modifierss

	//Functions
	void openFile(std::string file);
	void closeFile();

	void read();
	void writeLine(const std::string &string);
};

