#pragma once
#include <random>
#include <fstream>
class Generator
{
public:
	
	Generator();

	void loadFile(std::string filename, int targetArray[], int arraySize); //load arraySize ints from filename into targetArray
	void createFile(std::string filename, int length); //create a file with length int values between 1 and 100,000, output to filename
	void outputArray(std::string filename, int sourceArray[], int length); //take sourceArray, and output all it's values into filename
	void outputReversedArray(std::string filename, int sourceArray[], int length); //take sourceArray, and output all it's values into filename

private:

	int getRandomNumber(int min, int max); //returns an int between min and max (inclusive)
	int getRandomNumber();//returns random int between 1 and 100000
	
	std::string mTargetFile;
};