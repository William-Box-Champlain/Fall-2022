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
	std::ifstream input(filename);
	if (input.good())
	{
		std::string key;
		while (!input.eof())	//find codes.txt file length.
		{
			std::getline(input, key);
			mWordPairLength++;
		}
		std::cout << "There are " << mWordPairLength << " words in the array" << std::endl;
		mWordPairs = new WordCode[mWordPairLength];
	}
	input.close();
	input.open(filename);
	if(input.good())
	{
		std::string key;
		int i = 0;
		while (!input.eof() && i != mWordPairLength)	//create WordPairs and stuff them into the array.
		{
			input >> key;
			std::string word = key;
			input >> key;
			int code = std::stoi(key);
			//std::cout << "The word " << word << " has been added to the CodeBook with the code " << code << std::endl;
			mWordPairs[i] = WordCode(word, code);
			i++;
		}
	}
}

CodeBook::CodeBook()
{
	mWordPairs = NULL;
	mWordPairLength = 0;
}

bool CodeBook::isInCodeBook(std::string word)
{
	if (lookUpWord(word) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

CodeBook::CodeBook(std::string filename)
{
	codeTextParser(filename);
}