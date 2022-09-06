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

		Encoder();
		Encoder(std::string target);
		Encoder(std::string target, std::string codetext);

		~Encoder();

		void setCodeBook(CodeBook* codeBook);

		void output(std::string outputName);

	private:

		void encode(std::string outputName);

		CodeBook* mCodeBook;
		std::string mTarget;	
};