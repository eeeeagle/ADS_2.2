#pragma once
#ifndef STATS
#define STATS
#include <iostream>
#include <iomanip>

struct Stats
{
	size_t comparison_count = 0;
	size_t copy_count = 0;

	void print()
	{
		std::cout << std::setw(11) << "COMPARISONS"		<< std::setw(15) << "COPIES"	<< std::endl;
		std::cout << std::setw(11) << comparison_count	<< std::setw(15) << copy_count	<< std::endl;
	}
};
#endif