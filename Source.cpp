#include "Sort.hpp"
#include <conio.h>
#include <cstdlib>

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
		key = _getch();
	return key;
}

void print(const std::vector<int>& a, const std::vector<int>& b)
{
	std::cout << std::setw(11) << "ORIGINAL" << std::setw(15) << "SORTED" << std::endl;
	for (int i = 0; i < a.size(); i++)
		std::cout << std::setw(11) << a[i] << std::setw(15) << b[i] << std::endl;
	std::cout << std::endl << std::endl;
}

int main_menu()
{
	system("cls");
	std::cout << "[1] Insertion sort"				<< std::endl;
	std::cout << "[2] Quick sort"					<< std::endl;
	std::cout << "[3] Naturial two-way merge sort"	<< std::endl;
	std::cout << "[4] Exit"							<< std::endl << std::endl;
	while (true)
	{
		int key = get_key() - 48;
		if (key > 0 && key < 6)
			return key;
	}
}

int main(int argc, char* argv[])
{
	int size = 100;
	if (argc > 1)
		size = atoi(argv[1]);

	std::vector<int> data;
	std::srand(unsigned(std::time(nullptr)));
	for (int i = 0; i < size; i++)
		data.push_back(rand() % 20000 - 10000);
	const std::vector<int> original = data;
	
	while (true)
	{
		int key = main_menu();
		system("cls");
		Stats stats;
		switch (key)
		{
		case 1:
			data = original;
			stats = insertion_sort(data);
			break;
		case 2:
			data = original;
			stats = quick_sort(data);
			break;
		case 3:
			data = original;
			stats = two_way_merge_sort(data);
			break;
		case 4:
			return 0;
		}
		print(original, data);
		stats.print();
		system("pause >nul");
	}
}