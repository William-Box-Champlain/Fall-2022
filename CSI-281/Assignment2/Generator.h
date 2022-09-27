#pragma once
#include <random>
class Generator
{
public:
	
	Generator();
	Generator(std::string filename,int arraySize);

	void loadFile(std::string filename,int arraySize);
	void outputArray(std::string filename);

private:

	void generateFile();
	
	std::string targetFile;
	std::vector<int> mArray;

};