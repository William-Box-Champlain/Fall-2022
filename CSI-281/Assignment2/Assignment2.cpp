/*
Author: William Box
Class: CSI-281-01
Assignment: PA 2 - Part 4
Date Assigned: Sept 27
Due Date: Oct 4th 11:59 PM
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
#include "timer system/timerSystem.h"

enum numberList
{
    average,
    best,
    worst,
    all
};

enum sortType
{
    bubble,
    insertion,
    selection,
    shell,
    mergee,
    quick,
    last
};

/*
* Pre: requires a file loaded with ints to be created, and the name of the file to be stored in a string array (so that multiple files may be used)
* Post: outputs the time it took to perform a sorting operation with a list of listLength ints and a list type of numberList using a sorting algorithm of sortType
* Purpose: sort an array with the selection-sort algorithm
*/
void testSort(int listLength, sortType sortType, std::string files[], int iterations)
{
    
    Generator testGenerator;
    TimerSystem timer;

    int* list = new int[listLength];
    
    double sum = 0;
    double time = 0;
    int i;
    
    switch (sortType)
    {
    case bubble:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            bubbleSort(list, listLength);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "bubbleSort time (average over " << iterations << " iterations): " << sum/iterations << std::endl;
        break;
    case insertion:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            insertionSort(list, listLength);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "insertionSort time (average over " << iterations << " iterations): " << sum / iterations << std::endl;
        break;
    case selection:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            selectionSort(list, listLength);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "selectionSort time (average over " << iterations << " iterations): " << sum / iterations << std::endl;
        break;
    case shell:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            shellSort(list, listLength);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "shellSort time (average over " << iterations << " iterations): " << sum / iterations << std::endl;
        break;
    case mergee:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            mergeSort(list, 0, listLength - 1);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "mergeSort time (average over " << iterations << " iterations): " << sum / iterations << std::endl;
        break;
    case quick:
        for (i = 0; i < iterations; i++)
        {
            testGenerator.loadFile(files[i], list, listLength);
            timer.startClock();
            quickSort(list, 0, listLength - 1);
            time = timer.getTime();
            sum += time;
            std::cout << "Iteration " << i << " completed in " << time << " seconds." << std::endl;
        }
        std::cout << "quickSort time (average over " << iterations << " iterations): " << sum / iterations << std::endl;
        break;
    default:
        break;
    }
    delete[] list;
}

int main()
{

    Generator generator;
    int length = 1000000;
    int arraySize = 1000000;
    int iterations = 3;
    int* numbers = new int[arraySize];

    std::string baseNumberLists[] = { "testNumbers0","testNumbers1","testNumbers2" };
    std::string sortedNumberLists[] = { "sortedNumbers0","sortedNumbers1","sortedNumbers2" };
    std::string reverseSortedNumberLists[] = { "reverseSortedNumbers0","reverseSortedNumbers1","reverseSortedNumbers2" };

    for (int i = 0; i < iterations; i++)
    {
        generator.createFile(baseNumberLists[i], length);
    }

    for (int i = 0; i < iterations; i++)
    {
        generator.loadFile(baseNumberLists[i], numbers, arraySize);
        mergeSort(numbers, 0, arraySize - 1);
        generator.outputArray(sortedNumberLists[i], numbers, arraySize);
        generator.outputReversedArray(reverseSortedNumberLists[i], numbers, arraySize);
    }
    std::cout << "average case scenarios" << std::endl;
    int testLength = 100;
    std::cout << "short (100 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), baseNumberLists, iterations);
    }
    testLength = 10000;
    std::cout << "medium (10,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), baseNumberLists, iterations);
    }
    testLength = 750000;
    std::cout << "long (750,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), baseNumberLists, iterations);
    }
    std::cout << "best case scenarios" << std::endl;
    testLength = 100;
    std::cout << "short (100 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), sortedNumberLists, iterations);
    }
    testLength = 10000;
    std::cout << "medium (10,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), sortedNumberLists, iterations);
    }
    testLength = 750000;
    std::cout << "long (750,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), sortedNumberLists, iterations);
    }
    std::cout << "worst case scenarios" << std::endl;
    testLength = 100;
    std::cout << "short (100 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), reverseSortedNumberLists, iterations);
    }
    testLength = 10000;
    std::cout << "medium (10,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), reverseSortedNumberLists, iterations);
    }
    testLength = 750000;
    std::cout << "long (750,000 ints)" << std::endl;
    for (int sortTypeInt = bubble; sortTypeInt != last; sortTypeInt++)
    {
        testSort(testLength, static_cast<sortType>(sortTypeInt), reverseSortedNumberLists, iterations);
    }
    return 0;
}