/*
Author: William Box
Class: CSI-281-01
Assignment: PA 2
Date Assigned: Sept 16
Due Date: Sept 20 13:00
Description:

header file to keep sorting functions that will be written over the course of the semester.

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

/*
* Pre: requires two objects that you wish to swap the locations of.
* Post: the two objects should be swapped.
* Purpose: swap two objects around, primarily to be used in sorting algorithms.
*/
template<typename T>
void swap(T& obj1, T& obj2)
{
	T temp = obj1;
	obj1 = obj2;
	obj2 = temp;
}

/*
* Pre: requires an array, as well as the array's length
* Post: the array should be displayed to the console
* Purpose: display an array's contents to the console
*/
template <typename T>
void coutArray(T list[], int length)
{
	for (size_t i = 0; i < length; i++)
	{
		std::cout << list[i] << " ";
	}
	std::cout << std::endl;
}

/*
* Pre: requires a sorted or unsorted array, as well as the array's length 
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the bubble-sort algorithm
*/
template <typename T>
void bubbleSort(T list[], int size)
{
	bool swapped = true;
	int i = 0;
	int n = size;
	T temp;
	while (swapped)
	{
		swapped = false;
		for (i = 0; i < n - 1; i++)
		{
			if (list[i + 1] < list[i])
			{
				temp = list[i+1];
				list[i + 1] = list[i];
				list[i] = temp;
				swapped = true;
			}
		}
	}
};

/*
* Pre: requires a sorted or unsorted array, as well as the array's length
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the insertion-sort algorithm
*/
template <typename T>
void insertionSort(T list[], int size)
{
	int n = size;
	int i = 0;
	int j = 0;
	T value;
	for (i = 1; i < n; i++)
	{
		value = list[i];
		j = i - 1;
		while (j >= 0 && list[j] > value)
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = value;
	}
};

/*
* Pre: requires arrays that have been fully broken down into it's individual elements
* Post: the array should be sorted in assending order (from left to right)
* Purpose: merge and order the broken up arrays created by the above mergeSort function
*/
template<typename T>
void merge(T list[], int lowerBound, int mid, int upperBound)
{
	int i;
	int j;
	int k;

	int leftArraySize = mid - lowerBound + 1;
	int rightArraySize = upperBound - mid;

	T* leftArray = new T[leftArraySize];
	T* rightArray = new T[rightArraySize];
	
	for (i = 0; i < leftArraySize; i++)
	{
		leftArray[i] = list[lowerBound + i];
	}
	for (j = 0; j < rightArraySize; j++)
	{
		rightArray[j] = list[mid + j + 1];
	}

	i = j = 0;

	for (k = lowerBound; k < upperBound && i < leftArraySize && j < rightArraySize; k++)
	{
		if (leftArray[i] <= rightArray[j])
		{
			list[k] = leftArray[i];
			i++;
		}
		else
		{
			list[k] = rightArray[j];
			j++;
		}
	}

	while (i < leftArraySize)
	{
		list[k] = leftArray[i];
		i++;
		k++;
	}
	while (j < rightArraySize)
	{
		list[k] = rightArray[j];
		j++;
		k++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

/*
* Pre: requires a sorted or unsorted array, as well as the array's length
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the merge-sort algorithm
*/
template<typename T>
void mergeSort(T list[], int lowerBound, int upperBound)
{
	int mid;
	if (lowerBound < upperBound)
	{
		mid = (lowerBound + upperBound) / 2;

		mergeSort(list, lowerBound, mid);
		mergeSort(list, mid + 1, upperBound);

		merge(list, lowerBound, mid, upperBound);
	}
}

/*
* Pre: requires a sorted or unsorted array, as well as the array's length
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the quick-sort algorithm
*/
template<typename T>
void quickSort(T list[], int lowerBound, int upperBound)
{
	int i = lowerBound;
	int j = upperBound;

	int pivotPoint = (i + j) / 2;

	T pivot = list[pivotPoint];
	T temp;

	while (i <= j)
	{
		while (list[i] < pivot)
		{
			i++;
		}
		while (list[j] > pivot)
		{
			j--;
		}
		if (i <= j)
		{
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
			i++;
			j--;
		}
	}
	if (lowerBound < j)
	{
		quickSort(list, lowerBound, j);
	}
	if (i < upperBound)
	{
		quickSort(list, i, upperBound);
	}
}
/*
* Pre: requires a sorted or unsorted array, as well as the array's length
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the selection-sort algorithm
*/
template <typename T>
void selectionSort(T list[], int size)
{
	int i, j, minIndex;
	T temp;
	for (i = 0; i < size-1; i++)
	{
		minIndex = i;
		for (j = i+1; j < size; j++)
		{
			if (list[j] < list[minIndex]) minIndex = j;
		}
		if (minIndex != i)
		{
			temp = list[i];
			list[i] = list[minIndex];
			list[minIndex] = temp;
		}
	}
}

/*
* Pre: requires a sorted or unsorted array, as well as the array's length
* Post: the array should be sorted in assending order (from left to right)
* Purpose: sort an array with the selection-sort algorithm
*/
template <typename T>
void shellSort(T list[], int size)
{
	int i, gap;

	gap = size / 2;

	while (gap > 0)
	{
		for (i = 0; i > size - gap; i++)
		{
			if (list[i] > list[i + gap])
			{
				swap(list[i], list[i + gap]);
			}
		}
		gap = gap / 2;
	}
	bubbleSort(list, size);
}