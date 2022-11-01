#include "queue.h"
#include "stack.h"
#include <iostream>
#include <sstream>

int pemdas(char c)
{
    switch (c)
    {
    case '^':
        return 1;
    case '/':
    case '*':
        return 2;
    case '-':
    case '+':
        return 3;
    default:
        return -1;
    }
}

bool isOperand(char c)
{
    if (c == '^' || '/' || '*' || '-' || '+') return true;
    else return false;
}

void infixToPostfix(std::string input)
{
    Stack<char> inputStack;
    std::string result;
    int i;
    char c;

    for (i = 0; i < input.length(); i++)
    {
        c = input[i];
        if (isOperand(c)) result += c;
        else if (c == '(') inputStack.push('(');
        else if (c == ')')
        {
            while(inputStack.)
        }
    }
}

int main()
{

}