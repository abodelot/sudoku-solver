#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <fstream>


class Sudoku
{
public:
    // Columns and lines count in a sub-square
    static const int SQUARE = 3;
    // Columns and lines count in the grid
    static const int SIZE = SQUARE * SQUARE;

    Sudoku();

    /**
     * Load next problem in an opened file
     * @return true if problem loaded
     */
    bool load(std::ifstream& file);

    /**
     * Solve problem by recursion
     * @return true if solution found
     */
    bool solve();

    /**
     * Solve problem, no recursion variant. A bit slower (?)
     * @return true if solution found
     */
    bool solve_iter();

    /**
     * Set a value in the grid
     * @param x: line number
     * @param y: col number
     * @param value: new cell's value
     */
    void set(int x, int y, int value);

    /**
     * Get a value from the grid
     * @param x: line number
     * @param y: col number
     */
    int get(int x, int y) const;

    /**
     * Ensure the rules of Sudoku are respected for each already set value
     * @return true if the grid is well-formatted
     */
    bool is_grid_correct() const;

private:
    bool solve_recursion(int);

    /*
     * Check a value from the grid
     * @param x: line number
     * @param y: col number
     * @param value: new cell's value
     * @return true is value at (x, y) is a legit move
     */
    bool is_correct_value(int x, int y, int value) const;

    int m_grid[SIZE * SIZE];
};

std::ostream& operator<<(std::ostream &os, const Sudoku& sudoku);

#endif // SUDOKU_HPP

