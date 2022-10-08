#pragma once
#ifndef SORT
#define SORT
#include "Stats.hpp"
#include <vector>

template<typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}


Stats insertion_sort(std::vector<int>& data)
{
	Stats stats;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = i; j > 0 && data[j - 1] > data[j]; j--)
		{
            stats.comparison_count++;
            swap(data[j], data[j - 1]);
            stats.copy_count++;
			
		}
	}
	return stats;
}


Stats& quick_sort(std::vector<int>& data, int low, int high, Stats& stats)
{
    int i = low;
    int j = high;
    int pivot = data[(i + j) / 2];
    while (i <= j)
    {
        stats.comparison_count++;
        while (data[i] < pivot)
        {
            stats.comparison_count++;
            i++;
        }
        while (data[j] > pivot)
        {
            stats.comparison_count++;
            j--;
        }
        if (i <= j)
        {
            stats.comparison_count++;
            swap(data[i], data[j]);
            stats.copy_count++;
            i++;
            j--;
        }
    }
    if (j > low)
        quick_sort(data, low, j, stats);
    if (i < high)
        quick_sort(data, i, high, stats);
    return stats;
}

Stats quick_sort(std::vector<int>& data)
{
	Stats stats;
    if (!data.empty())
        quick_sort(data, 0, int(data.size() - 1), stats);
	return stats;
}

#endif