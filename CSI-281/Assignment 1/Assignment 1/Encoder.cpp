#include "Encoder.h"

Encoder::Encoder()
{
	mCodeBook = NULL;
	mTarget = "";
	mOuput = "output.txt";
}

Encoder::Encoder(std::string target)
{
	mCodeBook = NULL;
	mTarget = target;
	mOuput = "output.txt";
}

Encoder::Encoder(std::string target, std::string codeText)
{
	mCodeBook = new CodeBook(codeText);
	mTarget = target;
	mOuput = "output.txt";
}

void Encoder::setCodeBook(CodeBook* codeBook)
{
	mCodeBook = codeBook;
}

void Encoder::output()
{
	Encode();
}

void Encoder::Encode()
{
	std::ifstream input(mTarget);
	std::ofstream output(mOuput);
	std::string key;
	int code;
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
