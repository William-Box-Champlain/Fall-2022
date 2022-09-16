#include <iostream>
#include "sortingFunctions.h"

int main()
{
    int bubbleArray[5] = {1,5,2,4,3};
    std::cout << "Unsorted array: ";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << bubbleArray[i] << " ";
    }
    std::cout << std::endl;
    bubbleSort(bubbleArray, 5);
    std::cout << "Sorted with bubbleSort(): ";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << bubbleArray[i] << " ";
    }
    std::cout << std::endl;
    int insertionArray[5] = { 1,5,2,4,3 };
    std::cout << "Unsorted array: ";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << insertionArray[i] << " ";
    }
    std::cout << std::endl;
    insertionSort(insertionArray, 5);
    std::cout << "Sorted with insertionSort(): ";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << insertionArray[i] << " ";
    }
    return 0;
}