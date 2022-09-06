/*
Author: Bilbo Baggins
Class : CSI-281-01
Assignment : PA 1
Date Assigned : Sept 1st
Due Date : Sept 6th @ 1:00 PM
Description :
Contains the function definitions for the Encoder class
 
	Certification of Authenticity :
	I certify that this is entirely my own work, except where I have given
	fully - documented references to the work of others.I understand the definition and
	consequences of plagiarism and acknowledge that the assessor of this assignment
	may, for the purpose of assessing this assignment :
	-Reproduce this assignment and provide a copy to another member of academic staff;
		and /or
	-Communicate a copy of this assignment to a plagiarism checking service(which may
	then retain a copy of this assignment on its database for the purpose of future
	plagiarism checking)
*/

#include "Encoder.h"

Encoder::Encoder()
{
	mCodeBook = NULL;
	mTarget = "";
	std::cout << "construction finished" << std::endl;
}

Encoder::Encoder(std::string target)
{
	mCodeBook = NULL;
	mTarget = target;
	std::cout << "construction finished" << std::endl;
}

Encoder::Encoder(std::string target, std::string codeText)
{
	mCodeBook = new CodeBook(codeText);
	mTarget = target;
	std::cout << "construction finished" << std::endl;
}

Encoder::~Encoder()
{
	delete mCodeBook;
}

void Encoder::setCodeBook(CodeBook* codeBook)
{
	mCodeBook = codeBook;
}

void Encoder::output(std::string outputName)
{
	encode(outputName);
	std::cout << "output finished" << std::endl;
}

void Encoder::encode(std::string outputName)
{
	std::ifstream input(mTarget);
	std::ofstream output(outputName);
	std::string key;
	int code;

	//reads through the input file and checks if each word is in the CodeBook.
	//If a word is in the CodeBook, it inserts the appropriate code into the output file, else it gives the output file the clear text word.
	if (input.good())
	{
		while (!input.eof())
		{
			input >> key;
			if (mCodeBook->isInCodeBook(key))
			{
				code = mCodeBook->lookUpWord(key);
				output << code << " ";
			}
			else
			{
				output << key << " ";
			}
		}
	}
}