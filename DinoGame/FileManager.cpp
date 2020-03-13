#include "FileManager.h"


FileManager::FileManager()
{
	
}


FileManager::~FileManager()
{
	this->closeFile();
}

void FileManager::openFile(std::string file)
{
	if (this->writer.is_open()) this->closeFile();
	
	this->writer = std::ofstream(file);
	
	if (!this->writer.is_open())
	{
		std::cout << "ERROR: Writer could not open file " + file << std::endl;
	}
	if (!this->reader.is_open())
	{
		std::cout << "ERROR: Reader could not open file " + file << std::endl;
	}
	this->currentFile = file;
}

void FileManager::closeFile()
{
	this->writer.close();
}

void FileManager::read()
{
}

void FileManager::writeLine(const std::string &string)
{
	this->writer << string << std::endl;
}

