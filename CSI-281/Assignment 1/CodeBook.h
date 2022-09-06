/*
Author: Bilbo Baggins
Class : CSI-281-01
Assignment : PA 1
Date Assigned : Sept 1st
Due Date : Sept 6th @ 1:00 PM
Description :
CodeBook is designed to store and manage WordCode structs, which are themselves designed to store words and their associated cypher codes. 
 
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

		~CodeBook();

		bool isInCodeBook(std::string word);
		int lookUpWord(std::string word);

	private:

		WordCode* mWordPairs;	//declare a dynamic array for all the WordCodes.
		int mWordPairLength;	//an int to store the length of each dynamic array (length, not max index)

		void codeTextParser(std::string filename);
		void cleanUpArray();
};