#include <string>
#include <fstream>
#include <iostream>
#pragma once

struct WordCode
{
	std::string mWord;
	int mCode;
	WordCode()
	{
		mWord = "";
		mCode = 0;
	}
	WordCode(std::string word, int code)
	{
		mWord = word;
		mCode = code;
	}
	bool checkWord(std::string word)
	{
		if (word == mWord)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator == (std::string word) 
	{
		return checkWord(word);
	}
};

class CodeBook
{
public:

	CodeBook();
	CodeBook(std::string filename);
	int lookUpWord(std::string word);

	~CodeBook();

private:
	WordCode* mWordPairs;	//declare a dynamic array for all the WordCodes.
	int mWordPairLength;	//an int to store the length of each dynamic array (length, not max index)

	void codeTextParser(std::string filename);
};