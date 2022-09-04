#include "Encoder.h"

int main()
{
	int whileCheck = 1;
	do
	{
		//get target
		std::string input;
		std::cout << "What is the target filename? " << std::endl;
		std::cin >> input;
		//create Encoder and parse codes.txt
		Encoder frank(input,"codes.txt");
		//encode target
		//output encoded text file
		frank.output();
		std::cout << "Wanna do that again? Y/N " << std::endl;
	} while (true);
	
	return 0;
}