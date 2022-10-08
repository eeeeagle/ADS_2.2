#include "Sort.hpp"
#include <conio.h>

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224))
		key = _getch();
	return key;
}

void print(const std::vector<int>& data)
{
	for (int i = 0; i < data.size(); i++)
		std::cout << data[i] << std::endl;
	system("pause");
}

int main_menu()
{
	system("cls");
	std::cout << "[1] Print array" << std::endl;
	std::cout << "[2] Insertion sort" << std::endl;
	std::cout << "[3] Quick sort" << std::endl;
	std::cout << "[4] Two way merge sort" << std::endl;
	std::cout << "[5] Exit" << std::endl << std::endl;
	while (true)
	{
		int key = get_key();
		if (key == 49 || key == 50 || key == 51 || key == 52 || key == 53)
			return key;
	}
}

int main()
{
	std::vector<int> data;
	std::srand(unsigned(std::time(nullptr)));
	for (int i = 0; i < 50; i++)
		data.push_back(rand() % 2000 - 1000);
	const std::vector<int> original = data;
	while (true)
	{
		int key = main_menu();
		system("cls");
		if (key == 53)
			return 0;
		if (key == 49)
			print(original);
		else
		{
			if (key == 50)
				insertion_sort(data).print();
			else if (key == 51)
				quick_sort(data).print();
			else if (key == 52)
				two_way_merge_sort(data).print();
			print(data);
			data = original;
		}
	}
	return 0;
}