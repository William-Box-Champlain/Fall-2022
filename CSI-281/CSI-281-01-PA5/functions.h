#pragma once
#include <random>

/*
Author: William Box
Class: CSI-281-01
Assignment: PA 4
Date Assigned: Sept 27
Due Date: Nov 11th 11:59 PM
Description:

contains functions that I think might be helpful in the main

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the definition and
consequences of plagiarism and acknowledge that the assessor of this assignment
may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of academic staff;
and/or
- Communicate a copy of this assignment to a plagiarism checking service (which may
then retain a copy of this assignment on its database for the purpose of future
plagiarism checking)
*/

namespace wb
{
	/*      Pre:  None
	 *     Post:  Returns a random number
	 *  Purpose:  simplify generating a random number between 0 and 10,000
	 ******************************************************************************/
	int getRandomNumber()
	{
		return (std::rand() * std::rand()) % 1000001;
	}
}