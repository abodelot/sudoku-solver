#include <iostream>
#include <fstream>
#include "Sudoku.hpp"

/**
 * Sudoku problems solver
 * @author Alexandre Bodelot <alexandre.bodelot@gmail.com>
 */

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		Sudoku sudoku;
		std::ifstream file(argv[1]);
		if (file)
		{
			// Load each problem in opened file
			while (sudoku.load(file))
			{
				std::cout << "Start grid is:" << std::endl;
				std::cout << sudoku << std::endl;
				clock_t start = clock();
				if (sudoku.solve())
				{
					double elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
					std::cout << "Solution is (elapsed ~ " << elapsed << "s):" << std::endl;
					std::cout << sudoku << std::endl;
				}
				else
				{
					std::cout << "This Sudoku doesn't have a solution." << std::endl;
				}
			}
		}
		else
		{
			std::cerr << "Couldn't load problem file" << std::endl;
		}
	}
	else
	{
		std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
	}
	return 0;
}
