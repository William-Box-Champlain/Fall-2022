/*
Author: William Box
Class: CSI-281-01
Assignment: PA 2
Date Assigned: Sept 16
Due Date: Sept 20 13:00
Description:

Main file used to test the functions written within sortingFunctions.h

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

#include <iostream>
#include "sortingFunctions.h"
#include "Generator.h"

int main()
{
    Generator generator;
    int length = 1000000;
    int arraySize = 1000000;
    int* numbers = new int[arraySize];

    generator.createFile("testNumbers",length);
    generator.loadFile("testNumbers",numbers,arraySize);
    mergeSort(numbers, 0, arraySize-1);
    generator.outputArray("sortedNumbers", numbers, arraySize);
    generator.outputReversedArray("reverseSortedNumbers", numbers, arraySize);

    delete[] numbers;

    return 0;
}