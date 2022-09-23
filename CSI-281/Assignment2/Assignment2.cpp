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



int main()
{
    //declare unsorted array's and their length
    const int arrayLength = 5;
    int intArray0[arrayLength] = {1,5,2,4,3};
    int intArray1[arrayLength] = { 1,5,2,4,3 };
    std::string stringArray0[arrayLength] = { "c","n","t","i","e" };
    std::string stringArray1[arrayLength] = { "c","n","t","i","e" };
    
    //display unsorted array, sort array with selection-sort, and display the sorted array
    coutArray(intArray0,arrayLength);
    quickSort(intArray0, 0, 4);
    coutArray(intArray0,arrayLength);

    return 0;
}