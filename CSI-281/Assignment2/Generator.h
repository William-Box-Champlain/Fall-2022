#pragma once
#include <random>
#include <fstream>
class Generator
{
public:
	
	Generator();
	
	/*
	* Pre: requires a file loaded with ints and an int array. Ints must be seperated on new lines.
	* Post: the targetted array will be loaded with ints from the file in the order as they appear in the file.
	* Purpose: load arraySize ints from filename into targetArray
	*/
	void loadFile(std::string filename, int targetArray[], int arraySize);
	/*
	* Pre: no pre requirements.
	* Post: a file with the name "filename" will be loaded with length ints.
	* Purpose: create a file with length int values between 1 and 100,000, output to filename
	*/
	void createFile(std::string filename, int length); 
	/*
	* Pre: requires an int array to utilize as a source
	* Post: a file named "filename" filled with the contents of sourceArray
	* Purpose: take sourceArray, and output all it's values into filename
	*/
	void outputArray(std::string filename, int sourceArray[], int length); 
	/*
	* Pre: requires an int array to utilize as a source
	* Post: a file named "filename" filled with the contents of sourceArray but reversed
	* Purpose: take sourceArray, and output all it's values into filename
	*/
	void outputReversedArray(std::string filename, int sourceArray[], int length); //take sourceArray, and output all it's values into filename

private:

	int getRandomNumber(int min, int max); //returns an int between min and max (inclusive)
	int getRandomNumber();//returns random int between 1 and 100000
	
	std::string mTargetFile;
};