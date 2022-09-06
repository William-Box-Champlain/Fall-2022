/*
Author: Bilbo Baggins
Class : CSI-281-01
Assignment : PA 1
Date Assigned : Sept 1st
Due Date : Sept 6th @ 1:00 PM
Description :
definitions for the CodeBook class functions 
 
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

#include "CodeBook.h"

int CodeBook::lookUpWord(std::string word)
{
	int i = 0;
	while (i != mWordPairLength)
	{
		if (mWordPairs[i] == word)
		{
			return mWordPairs[i].mCode;
		}
		else
		{
			i++;
		}
	}
    return 0;
}

void CodeBook::codeTextParser(std::string filename)	//convert the codes.txt file into a dynamic array of WordPairs.
{
	//find codes.txt file length.
	std::ifstream input(filename);
	if (input.good())
	{
		std::string key;
		while (!input.eof())	
		{
			std::getline(input, key);
			mWordPairLength++;
		}
		std::cout << "There are " << mWordPairLength << " words in the array" << std::endl;
		mWordPairs = new WordCode[mWordPairLength];
	}
	input.close();
	input.open(filename);
	//creates WordCodes using codes.txt file
	if(input.good())
	{
		std::string key;
		for (int i = 0; i < mWordPairLength; i++)
		{
			input >> key;
			std::string word = key;
			input >> key;
			int code = std::stoi(key);
			mWordPairs[i] = WordCode(word, code);
		}
	}
}

CodeBook::CodeBook()
{
	mWordPairs = NULL;
	mWordPairLength = 0;
}

CodeBook::~CodeBook()
{
	cleanUpArray();

}

void CodeBook::cleanUpArray()
{
	delete[] mWordPairs;
}

bool CodeBook::isInCodeBook(std::string word)
{
	switch (lookUpWord(word))
	{
		case 0:			return false;
		default:		return true;
	}
}

CodeBook::CodeBook(std::string filename)
{
	codeTextParser(filename);
}