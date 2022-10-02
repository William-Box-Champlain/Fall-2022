#include "Generator.h"

Generator::Generator()
{
	mTargetFile = "";
}

void Generator::loadFile(std::string filename, int targetArray[], int arraySize)
{
	mTargetFile = filename;
	std::ifstream input(filename);
	int key;
	int temp;
	int i;

	if (input.good())
	{
		for (i = 0; i < arraySize; i++)
		{
			input >> key;
			temp = key;
			targetArray[i] = key;
		}
	}
}

void Generator::createFile(std::string filename, int length)
{
	int temp;
	mTargetFile = filename;
	std::ofstream output(filename);
	for (size_t i = 0; i < length; i++)
	{
		temp = getRandomNumber();
		output << temp << "\n";
	}
}

void Generator::outputArray(std::string filename, int sourceArray[], int length)
{
	int i;
	int temp;
	std::ofstream output(filename);
	if (output.good())
	{
		for (i = 0; i < length; i++)
		{
			temp = sourceArray[i];
			output << sourceArray[i] << "\n";
		}
	}
}

void Generator::outputReversedArray(std::string filename, int sourceArray[], int length)
{
	int i;
	int temp;
	std::ofstream output(filename);
	if (output.good())
	{
		for (i = length-1; i >= 0; i--)
		{
			temp = sourceArray[i];
			output << sourceArray[i] << "\n";
		}
	}
}

int Generator::getRandomNumber(int min, int max)
{
    return (std::rand()%(max + 1)+min);
}

int Generator::getRandomNumber()
{
    return (std::rand() * std::rand()) % 1000001;
}
