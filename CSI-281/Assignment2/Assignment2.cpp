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
#include "timer system/timerSystem.h"

enum numberList
{
    average,
    best,
    worst
};

enum sortType
{
    bubble,
    insertion,
    selection,
    shell,
    mergee,
    quick
};

void testSort(int listLength, sortType sortType, numberList numberList)
{
    const std::string fullRandom = "testNumbers";
    const std::string assendingNumbers = "sortedNumbers";
    const std::string descendingNumbers = "reverseSortedNumbers";

    Generator testGenerator;
    TimerSystem timer;

    int* list = new int[listLength];
    switch (numberList)
    {
    case average:
        testGenerator.loadFile(fullRandom, list, listLength);
        std::cout << "Average case (" << listLength <<" ints)";
        break;
    case best:
        testGenerator.loadFile(assendingNumbers, list, listLength);
        std::cout << "   Best case (" << listLength << " ints)";
        break;
    case worst:
        testGenerator.loadFile(descendingNumbers, list, listLength);
        std::cout << "  Worst case (" << listLength << " ints)";
        break;
    default:
        break;
    }
    switch (sortType)
    {
    case bubble:
        timer.startClock();
        bubbleSort(list, listLength);
        std::cout << "BubbleSort time: " << timer.getTime() << std::endl;
        break;
    case insertion:
        timer.startClock();
        insertionSort(list, listLength);
        std::cout << "InsertionSort time: " << timer.getTime() << std::endl;
        break;
    case selection:
        timer.startClock();
        selectionSort(list,listLength);
        std::cout << "SelectionSort time: " << timer.getTime() << std::endl;
        break;
    case shell:
        timer.startClock();
        shellSort(list, listLength);
        std::cout << "ShellSort time: " << timer.getTime() << std::endl;
        break;
    case mergee:
        timer.startClock();
        mergeSort(list, 0, listLength-1);
        std::cout << "MergeSort time: " << timer.getTime() << std::endl;
        break;
    case quick:
        timer.startClock();
        quickSort(list, 0, listLength-1);
        std::cout << "QuickSort time: " << timer.getTime() << std::endl;
        break;
    default:
        break;
    }
    delete[] list;
}

int main()
{
    

    //Generator generator;
    //int length = 1000000;
    //int arraySize = 1000000;
    //int* numbers = new int[arraySize];

    ////short tests
    //int shortList = 100;
    //
    ////sort shortArray

    ////medium tests

    //generator.createFile("testNumbers",length);
    //generator.loadFile("testNumbers",numbers,arraySize);
    //mergeSort(numbers, 0, arraySize-1);
    //generator.outputArray("sortedNumbers", numbers, arraySize);
    //generator.outputReversedArray("reverseSortedNumbers", numbers, arraySize);

    //delete[] numbers;

    std::cout << "short tests (100 ints): " << std::endl;
    int testLength = 100;
    testSort(testLength, bubble, average);
    testSort(testLength, bubble, best);
    testSort(testLength, bubble, worst);
    testSort(testLength, insertion, average);
    testSort(testLength, insertion, best);
    testSort(testLength, insertion, worst);
    testSort(testLength, selection, average);
    testSort(testLength, selection, best);
    testSort(testLength, selection, worst);
    testSort(testLength, shell, average);
    testSort(testLength, shell, best);
    testSort(testLength, shell, worst);
    testSort(testLength, mergee, average);
    testSort(testLength, mergee, best);
    testSort(testLength, mergee, worst);
    testSort(testLength, quick, average);
    testSort(testLength, quick, best);
    testSort(testLength, quick, worst);

    std::cout << "medium tests (10,000 ints): " << std::endl;
    testLength = 10000;
    testSort(testLength, bubble, average);
    testSort(testLength, bubble, best);
    testSort(testLength, bubble, worst);
    testSort(testLength, insertion, average);
    testSort(testLength, insertion, best);
    testSort(testLength, insertion, worst);
    testSort(testLength, selection, average);
    testSort(testLength, selection, best);
    testSort(testLength, selection, worst);
    testSort(testLength, shell, average);
    testSort(testLength, shell, best);
    testSort(testLength, shell, worst);
    testSort(testLength, mergee, average);
    testSort(testLength, mergee, best);
    testSort(testLength, mergee, worst);
    testSort(testLength, quick, average);
    testSort(testLength, quick, best);
    testSort(testLength, quick, worst);

    std::cout << "long tests (750,000 ints): " << std::endl;
    testLength = 750000;
    testSort(testLength, bubble, average);
    testSort(testLength, bubble, best);
    testSort(testLength, bubble, worst);
    testSort(testLength, insertion, average);
    testSort(testLength, insertion, best);
    testSort(testLength, insertion, worst);
    testSort(testLength, selection, average);
    testSort(testLength, selection, best);
    testSort(testLength, selection, worst);
    testSort(testLength, shell, average);
    testSort(testLength, shell, best);
    testSort(testLength, shell, worst);
    testSort(testLength, mergee, average);
    testSort(testLength, mergee, best);
    testSort(testLength, mergee, worst);
    testSort(testLength, quick, average);
    testSort(testLength, quick, best);
    testSort(testLength, quick, worst);

    return 0;
}