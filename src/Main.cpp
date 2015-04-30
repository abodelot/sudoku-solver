/**
 * Sudoku problems solver
 * @author Alexandre Bodelot <alexandre.bodelot@gmail.com>
 */

#include <fstream>
#include <iostream>
#include "Sudoku.hpp"


int main(int argc, const char* argv[])
{
    if (argc == 0)
    {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return 0;
    }

    Sudoku sudoku;
    std::ifstream file(argv[1]);
    if (file)
    {
        int count = 0;
        // Load each problem in opened file
        while (sudoku.load(file))
        {
            std::cout << "[" << count << "] Start grid is:" << std::endl;
            std::cout << sudoku << std::endl;
            clock_t start = clock();
            if (sudoku.solve())
            {
                double elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
                std::cout << "[" << count << "] Solution is (elapsed ~ " << elapsed << "s):" << std::endl;
                std::cout << sudoku << std::endl;
            }
            else
            {
                std::cout << "[" << count << "] This Sudoku doesn't have a solution." << std::endl;
            }
            ++count;
        }
    }
    else
    {
        std::cerr << "Couldn't load problem file " << argv[1] << std::endl;
    }
    return 0;
}
