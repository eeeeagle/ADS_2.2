#pragma once
#ifndef STATS
#define STATS
#include <iostream>

struct Stats
{
	size_t comparison_count = 0;
	size_t copy_count = 0;

	void print()
	{
		std::cout << "Comparisons: " << comparison_count	<< std::endl;
		std::cout << "     Copies: " << copy_count			<< std::endl;
	}
};
#endif