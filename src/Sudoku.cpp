#include <stack>
#include <cassert>
#include "Sudoku.hpp"


Sudoku::Sudoku()
{
    // Empty grid
    for (int i = 0; i < SIZE; ++i)
    {
        m_grid[i] = 0;
    }
}


bool Sudoku::load(std::ifstream& file)
{
    if (file)
    {
        std::string line;
        int nb_digits = 0;
        while (getline(file, line))
        {
            // Ignore lines starting with a #
            if (!line.empty() && line[0] != '#')
            {
                for (size_t i = 0; i < line.size(); ++i)
                {
                    char c = line[i];
                    // Do not impose any file formatting, simply discard non digit characters
                    if (c >= '0' && c <= '9')
                    {
                        int value = c - '0';
                        m_grid[nb_digits] = value;
                        ++nb_digits;
                        if (nb_digits >= Sudoku::SIZE * Sudoku::SIZE)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


int Sudoku::get(int x, int y) const
{
    assert(0 <= x && x < Sudoku::SIZE && 0 <= y && y < Sudoku::SIZE);
    return m_grid[x * Sudoku::SIZE + y];
}


void Sudoku::set(int x, int y, int value)
{
    assert(is_correct_value(x, y, value));
    m_grid[x * Sudoku::SIZE + y] = value;
}


bool Sudoku::is_grid_correct() const
{
    for (int x = 0; x < Sudoku::SIZE; ++x)
    {
        for (int y = 0; y < Sudoku::SIZE; ++y)
        {
            int v = get(x, y);
            if (v != 0 && !is_correct_value(x, y, v))
            {
                return false;
            }
        }
    }
    return true;
}


bool Sudoku::solve()
{
    assert(is_grid_correct());

    return solve_recursion(0);
}


bool Sudoku::solve_recursion(int i)
{
    // Go to the first free cell (0)
    for (; i < Sudoku::SIZE * Sudoku::SIZE && m_grid[i] != 0; ++i);

    // If no free cells, grid is completed and solution is found
    if (i == Sudoku::SIZE * Sudoku::SIZE)
    {
        return true;
    }

    // Brute force: check every possible value
    for (int value = 1; value <= Sudoku::SIZE; ++value)
    {
        if (is_correct_value(i / Sudoku::SIZE, i % Sudoku::SIZE, value))
        {
            m_grid[i] = value;
            if (solve_recursion(i + 1))
            {
                return true;
            }
        }
    }

    // No solution
    m_grid[i] = 0;
    return false;
}


bool Sudoku::solve_iter()
{
    assert(is_grid_correct());

    std::stack<int> stack;
    int i, v;
    for (i = 0; i < Sudoku::SIZE * Sudoku::SIZE && m_grid[i] != 0; ++i);

    while (i < Sudoku::SIZE * Sudoku::SIZE)
    {
        for (v = m_grid[i] + 1;
            v <= Sudoku::SIZE
            && !is_correct_value(i / Sudoku::SIZE, i % Sudoku::SIZE, v);
            ++v);
        if (v <= Sudoku::SIZE)
        {
            m_grid[i] = v;
            stack.push(i);
            for (; i < Sudoku::SIZE * Sudoku::SIZE && m_grid[i] != 0; ++i);
        }
        else
        {
            if (stack.empty())
            {
                return false; // no solution
            }
            else
            {
                m_grid[i] = 0;
                i = stack.top();
                stack.pop();
            }
        }
    }
      return true;
}


bool Sudoku::is_correct_value(int x, int y, int value) const
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || value < 1 || value > SIZE)
        return false;

    // Check line
    for (int i = 0; i < Sudoku::SIZE; ++i)
        if (i != x && get(i, y) == value)
            return false;

    // Check column
    for (int j = 0; j < Sudoku::SIZE; ++j)
        if (j != y && get(x, j) == value)
            return false;

    // Check sub-square
    for (int i = (x / Sudoku::SQUARE) * Sudoku::SQUARE; i < (x / Sudoku::SQUARE + 1) * Sudoku::SQUARE; ++i)
        for (int j = (y / Sudoku::SQUARE) * Sudoku::SQUARE; j < (y / Sudoku::SQUARE + 1) * Sudoku::SQUARE; ++j)
            if (i != x && j != y && get(i, j) == value)
                return false;

    return true;
}


std::ostream& operator<<(std::ostream &os, const Sudoku& sudoku)
{
    for (int x = 0; x < Sudoku::SIZE; ++x)
    {
        if (x % Sudoku::SQUARE == 0)
            os << "+-------+-------+-------+" << std::endl;

        os << "|";
        for (int y = 0; y < Sudoku::SIZE; ++y)
        {
            int value = sudoku.get(x, y);
            if (value)
                os << " " << value;
            else
                os << "  ";
            if ((y + 1) % Sudoku::SQUARE == 0)
                os << " |";
        }
        os << std::endl;
    }
    os << "+-------+-------+-------+" << std::endl;
    return os;
}

