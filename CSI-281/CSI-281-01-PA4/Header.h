/*
Author: William Box
Class: CSI-281-01
Assignment: PA 4
Date Assigned: I forgot when this was assigned.
Due Date: Nov 11th 11:59 PM
Description:

Header file declaring the functions for processing a string containing a math formula using the Queue and Stack data-structures.

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

#pragma once
#include "queue.h"
#include "stack.h"
#include <sstream> 

enum operand
{
    addi,
    subi,
    mult,
    divi,
    expo,
    def
};

/*      Pre: A char that is a math operand
 *     Post: Returns an enum corresoponding to the operand
 *  Purpose: Convert a char that is an operand to an enum for easier coding elsewhere.
 *********************************************************************/
operand getOperand(char c);

/*      Pre: A string that you wish to later process with processPostFixQueue()
 *     Post: A string Queue containing a formula in post-fix notation
 *  Purpose: Prepare a string to be processed by processPostFixQueue()
 *********************************************************************/
Queue<string>* infixToPostfix(std::string input);

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a number
 *  Purpose: Determine if char c is a number
 *********************************************************************/
bool isNumber(char c);

/*      Pre: A char of unknown type
 *     Post: Returns if the char is an operand
 *  Purpose: Determine if char c is an operand
 *********************************************************************/
bool isOperand(char c);

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a type that is valid character for the calculator
 *  Purpose: Check if char c is an operand, number, or white-space
 *********************************************************************/
bool isValidCharacter(char c);

/*      Pre: A string that you wish to later process with infixToPostfix()
 *     Post: A boolean value corresponding to if the string can be processed by infixToPostfix()
 *  Purpose: To prevent invalid strings from being entered into infixToPostfix()
 *********************************************************************/
bool isValidString(std::string input);

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a white-space
 *  Purpose: Determine if char c is a white-space
 *********************************************************************/
bool isWhiteSpace(char c);

/*      Pre: A string Queue containing a formula in post-fix notation
 *     Post: Returns a string-stream containing the solution to the given formula
 *  Purpose: Output the result of a given formula into a stringstream so that it can be displayed to the screen (or whatever you want a stringstream for)
 *********************************************************************/
std::stringstream processPostFixQueue(Queue<string> queue);