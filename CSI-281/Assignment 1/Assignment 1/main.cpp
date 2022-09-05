#include "Encoder.h"

int main()
{
	bool dontrepeat = false;
	do
	{
		std::string target = "target.txt";
		std::string codes = "codes.txt";
		Encoder frank(target,codes);
		std::cout << "construction finished" << std::endl;
		frank.output();
		std::cout << "output finished" << std::endl;

	} while (dontrepeat);
	
	return 0;
}