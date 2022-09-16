#pragma once

template <typename T>
void bubbleSort(T list[], int size)
{
	bool swapped = true;
	int i = 0;
	int n = size;
	while (swapped)
	{
		swapped = false;
		for (i = 0; i < n - 1; i++)
		{
			if (list[i + 1] < list[i])
			{
				T temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				swapped = true;
			}
		}
	}
};

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