/*
Author: Bilbo Baggins
Class : CSI-281-01
Assignment : PA 1
Date Assigned : Sept 1st
Due Date : Sept 6th @ 1:00 PM
Description :
Main file of program. 
 
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

int main()
{
	bool dontrepeat = false;
	do
	{
		std::string target = "target.txt"; //filename of .txt file to be encoded, as written the program will use the file target.txt already included with the code.
		std::string codes = "codes.txt";   //filename of .txt file to be used as cypher, as written the program will use the file codes.txt already included with the code.
		std::string output = "output.txt"; //filename of encoded .txt file, as written will output file in programs home directory.

		Encoder encoder(target,codes);

		encoder.output(output);

	} while (dontrepeat);
	
	return 0;
}