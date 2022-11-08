/*
Author: William Box
Class: CSI-281-01
Assignment: PA 4
Date Assigned: Sept 27
Due Date: Nov 11th 11:59 PM
Description:

Main file used to test the functions declared in Header.h

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

#include "queue.h"
#include "stack.h"
#include "Header.h"
#include <iostream>

int main()
{
    bool loop = true;

    Queue<string>* tempQueue = NULL;
    std::string tempString;

    while (loop)
    {
        std::cout << "Please enter a fully parenthsized formula: ";
        getline(cin,tempString);
        if (isValidString(tempString))
        {
            tempQueue = infixToPostfix(tempString);
            std::cout << "Your result is: " << processPostFixQueue(*tempQueue).str() << std::endl;
            loop = !loop;
        }
        if (loop == false)
        {
            std::cout << "Would you like to enter a new formula? Y/N: ";
            getline(cin, tempString);
            if (tempString == "Y" || tempString == "y")
            {
                loop = true;
            }
        }
        else
        {
            std::cout << "Parenthesis or character error, please enter again." << std::endl;
        }
    }

}