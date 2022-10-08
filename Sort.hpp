#pragma once
#ifndef SORT
#define SORT
#include "Stats.hpp"
#include <vector>

typedef std::vector<int>::iterator          iterator;
typedef std::vector<int>::reverse_iterator  reverse_iterator;

template<typename T>
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

bool is_sorted(const std::vector<int>& data)
{
    for (auto iter = data.cbegin() + 1; iter != data.cend(); iter++)
    {
        if (*iter < *(iter - 1))
            return false;
    }
    return true;
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
    if (!is_sorted(data))
        quick_sort(data, 0, int(data.size() - 1), stats);
	return stats;
}


template <typename Iter>
Iter get_seq(Stats& stats, Iter iter, const Iter& end)
{
    while (iter != end && *iter > *(iter - 1))
    {
        stats.comparison_count++;
        iter++;
    }
    return iter;
}

std::vector<int> merge_seq(Stats& stats, iterator& a_begin, const iterator& a_end,
    reverse_iterator& b_begin, const reverse_iterator& b_end)
{
    std::vector<int> seq;
    while (a_begin <= b_begin.base() - 1 && a_begin != a_end && b_begin != b_end)
    {
        if (*a_begin < *b_begin)
        {
            seq.push_back(*a_begin);
            a_begin++;
        }
        else if (*a_begin > *b_begin)
        {
            seq.push_back(*b_begin);
            b_begin++;
        }
        else
        {
            seq.push_back(*b_begin);
            a_begin++;
            b_begin++;
        }

        stats.comparison_count++;
        stats.copy_count++;
    }

    if (a_begin < b_begin.base() - 1)
    {

        while (a_begin != a_end)
        {
            seq.push_back(*a_begin);
            a_begin++;
            stats.copy_count++;
        }

        while (b_begin != b_end)
        {
            seq.push_back(*b_begin);
            b_begin++;
            stats.copy_count++;
        }
    }
    return seq;
}

Stats two_way_merge_sort(std::vector<int>& data)
{
    Stats stats;
    while (!is_sorted(data))
    {
        std::vector<std::vector<int>> seq; // sequences array 

        auto forward_start = data.begin();
        auto reverse_start = data.rbegin();

        while (forward_start < reverse_start.base() - 1 && forward_start != data.end() && reverse_start != data.rend())
        {
            auto forward_end = get_seq(stats, forward_start + 1, data.end());
            auto reverse_end = get_seq(stats, reverse_start + 1, data.rend());
            seq.push_back(merge_seq(stats, forward_start, forward_end, reverse_start, reverse_end));
        }

        auto fwd = data.begin();
        auto rvs = data.rbegin();

        for (size_t i = 0; i < seq.size(); i++)
        {
            for (auto iter = seq[i].begin(); iter < seq[i].end(); iter++)
            {
                if (i % 2 == 0)
                {
                    *fwd = *iter;
                    fwd++;
                }
                else
                {
                    *rvs = *iter;
                    rvs++;
                }
                stats.copy_count++;
            }
        }
    }
    return stats;
}
#endif