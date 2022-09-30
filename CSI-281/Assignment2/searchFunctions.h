#pragma once

template<typename T>
bool binarySearch(T list[], T searchKey, int lowerBound, int upperBound)
{
	bool found = false;
	int mid;

	if (lowerBound <= upperBound)
	{
		mid = (lowerBound + upperBound) / 2;

		if (list[mid] == searchKey) found = true;
		else if (list[mid] > searchKey) return binarySearch(list, searchKey, lowerBound, mid - 1);
		else return binarySearch(list, searchKey, mid + 1, upperBound);
	}
	return found; 
}

template<typename T>
bool sequentialSearch(T list[], T searchKey, int length)
{
	bool found = false;
	int i;
	for (i = 0; i < length; i++)
	{
		if (list[i] == searchKey)
		{
			found = true;
			break;
		}
	}
	return found;
}

template<typename T>
bool enhancedSequentialSearch(T list[], T searchKey, int length)
{
	bool found = false;
	int i;
	for (i = 0; i < length; i++)
	{
		if (list[i] == searchKey)
		{
			found = true;
			break;
		}
		else
		{
			if (list[i] > searchKey)
			{
				break;
			}
		}
	}
	return found;
}