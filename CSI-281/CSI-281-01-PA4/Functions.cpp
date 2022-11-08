/*
Author: William Box
Class: CSI-281-01
Assignment: PA 4
Date Assigned: I forgot when this was assigned.
Due Date: Nov 11th 11:59 PM
Description:

.cpp file defining the functions declared in Header.h

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
operand getOperand(char c)
{
    if (c == '^') return operand::expo;
    else if (c == '/') return operand::divi;
    else if (c == '*') return operand::mult;
    else if (c == '-') return operand::subi;
    else if (c == '+') return operand::addi;
    else return operand::def;
};

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a number
 *  Purpose: Determine if char c is a number
 *********************************************************************/
bool isNumber(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') return true;
    else return false;
};

/*      Pre: A char of unknown type
 *     Post: Returns if the char is an operand
 *  Purpose: Determine if char c is an operand
 *********************************************************************/
bool isOperand(char c)
{
    if (c == '^' || c == '/' || c == '*' || c == '-' || c == '+') return true;
    else return false;
};

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a white-space
 *  Purpose: Determine if char c is a white-space
 *********************************************************************/
bool isWhiteSpace(char c)
{
    if (c == ' ') return true;
    else return false;
};

/*      Pre: A char of unknown type
 *     Post: Returns if the char is a type that is valid character for the calculator
 *  Purpose: Check if char c is an operand, number, or white-space
 *********************************************************************/
bool isValidCharacter(char c)
{
    return (!isOperand(c) && !isNumber(c) && !isWhiteSpace(c));
};

/*      Pre: A string that you wish to later process with infixToPostfix()
 *     Post: A boolean value corresponding to if the string can be processed by infixToPostfix()
 *  Purpose: To prevent invalid strings from being entered into infixToPostfix()
 *********************************************************************/
bool isValidString(std::string input)
{
    int i;
    int openCount = 0;
    int charCount = 0;
    char c;
    for (i = 0; i < input.length(); i++)
    {
        c = input[i];
        if (c == '(') openCount++;
        else if (c == ')') openCount--;
        else if (isValidCharacter(c))
        {
            charCount++;
        }
    }
    if (openCount != 0 || charCount != 0) return false;
    else return true;
};

/*      Pre: A string that you wish to later process with processPostFixQueue()
 *     Post: A string Queue containing a formula in post-fix notation
 *  Purpose: Prepare a string to be processed by processPostFixQueue()
 *********************************************************************/
Queue<string>* infixToPostfix(std::string input)
{
    Queue<string>* postFixQueue = new Queue<string>();
    Stack<char> opStack;
    std::string temp;
    int i = 0;
    int openCount = 0;
    char c;

    for (i = 0; i < input.length(); i++)
    {
        c = input[i];
        if (isOperand(c))
        {
            opStack.push(c);
            postFixQueue->enqueue(temp);
            temp.clear();
        }
        else if (c == '(') openCount++;
        else if (c == ')')
        {
            openCount--;
            if (temp != "")
            {
                postFixQueue->enqueue(temp);
                temp.clear();
            }
            postFixQueue->enqueue(std::string(1, opStack.pop()));
        }
        else if (isNumber(c))
        {
            temp.push_back(c);
        }
        else if (isWhiteSpace(c))
        {
            if (temp != "")
            {
                postFixQueue->enqueue(temp);
                temp.clear();
            }
        }
    }
    if (!opStack.isEmpty())
    {
        postFixQueue->enqueue(std::string(1, opStack.pop()));
    }
    return postFixQueue;
};

/*      Pre: A string Queue containing a formula in post-fix notation
 *     Post: Returns a string-stream containing the solution to the given formula
 *  Purpose: Output the result of a given formula into a stringstream so that it can be displayed to the screen (or whatever you want a stringstream for)
 *********************************************************************/
std::stringstream processPostFixQueue(Queue<string> queue)
{
    std::stringstream ss;

    float a, b;
    int runningTotal;
    int arrayLength = queue.getCount();

    operand o;

    Stack<string> tempStack;
    std::string tempString;

    while (!queue.isEmpty())
    {
        tempString = queue.dequeue();
        if (isNumber(tempString[0]))
        {
            tempStack.push(tempString);
        }
        else if (isOperand(tempString[0]))
        {
            b = std::stod(tempStack.pop());
            a = std::stod(tempStack.pop());
            o = getOperand(tempString[0]);
            switch (o)
            {
            case addi:
                tempString = to_string(a + b);
                tempStack.push(tempString);
                break;
            case subi:
                tempString = to_string(a - b);
                tempStack.push(tempString);
                break;
            case mult:
                tempString = to_string(a * b);
                tempStack.push(tempString);
                break;
            case divi:
                tempString = to_string(a / b);
                tempStack.push(tempString);
                break;
            case expo:
                tempString = to_string(std::pow(a, b));
                tempStack.push(tempString);
                break;
            case def:
                break;
            default:
                break;
            }
        }
    }

    tempString = tempStack.pop();
    ss << tempString;

    return ss;
};