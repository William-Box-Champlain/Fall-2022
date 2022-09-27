#include "Generator.h"

Generator::Generator(std::string filename, int arraySize)
{
	targetFile = filename;
	std::ifstream file(targetFile);
	if (!file.is_open())
	{
		generateFile();
	}
}

void Generator::generateFile()
{

}