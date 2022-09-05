#include "CodeBook.h"
#pragma once
class Encoder
{
public:
	Encoder();
	Encoder(std::string target);
	Encoder(std::string target, std::string codetext);

	void setCodeBook(CodeBook* codeBook);

	void output();

private:

	void Encode();

	CodeBook* mCodeBook;
	std::string mTarget;	//string containing the name of the file to be changed
	std::string mOuput;
};