/*
Author: Bilbo Baggins
Class : CSI-281-01
Assignment : PA 1
Date Assigned : Sept 1st
Due Date : Sept 6th @ 1:00 PM
Description :
Manages reading a clear text .txt file and writing an encoded .txt using a given (or generated) CodeBook class. 
 
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
#pragma once
class Encoder
{
	public:

		/*
			pre: none
		   post: generates a CodeBook object with an empty mCodeBook and mTarget.
		purpose: this is the default constructor for the CodeBook class.
		*/
		Encoder();
		/*
			pre: requires the filename of the file to be changed by the encoder.
		   post: generates a CodeBook object with an empty mCodeBook and populated mTarget.
		purpose: this is one of two parameterized constructors for the CodeBook class, and allows one to create a CodeBook with a target file already set but still in need of a codebook.
		*/
		Encoder(std::string target);
		/*
			pre: requires the filename of both the file to be changed and the file cont
		   post: generates a CodeBook object with a populated mTarget and constructs a new CodeBook object when ran.
		purpose: this is the default constructor for the CodeBook class.
		*/
		Encoder(std::string target, std::string codetext);

		~Encoder();

		void setTarget();
		void setCodeBook(CodeBook* codeBook);

		void output(std::string outputName);

	private:

		void encode(std::string outputName);

		CodeBook* mCodeBook;
		std::string mTarget;	
};