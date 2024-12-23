#include <iostream>
#include <fstream>
#include <vector>
#include <set>

size_t m, n;

std::string readInput(std::string input_path, std::vector<std::vector<char>> &grid)
{
    std::ifstream ifstream(input_path);

    std::string line;

    std::string directions = "";

    bool readingGrid = true;

    while (std::getline(ifstream, line))
    {
        if (line == "")
            readingGrid = false;

        if (readingGrid)
        {
            std::vector<char> row;
            for (char c : line)
            {
                row.push_back(c);
            }
            grid.push_back(row);
        }
        else
        {
            directions.append(line);
        }
    }

    return directions;
}

std::string readInput2(std::string input_path, std::vector<std::vector<char>> &grid)
{
    std::ifstream ifstream(input_path);

    std::string line;

    std::string directions = "";

    bool readingGrid = true;

    while (std::getline(ifstream, line))
    {
        if (line == "")
            readingGrid = false;

        if (readingGrid)
        {
            std::vector<char> row;
            for (char c : line)
            {
                if (c == '#')
                {
                    row.push_back('#');
                    row.push_back('#');
                }
                else if (c == '.')
                {
                    row.push_back('.');
                    row.push_back('.');
                }
                else if (c == '@')
                {
                    row.push_back('@');
                    row.push_back('.');
                }
                else if (c == 'O')
                {
                    row.push_back('[');
                    row.push_back(']');
                }
            }
            grid.push_back(row);
        }
        else
        {
            directions.append(line);
        }
    }

    return directions;
}

std::pair<int, int> getStart(const std::vector<std::vector<char>> &grid)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == '@')
            {
                return std::make_pair(i, j);
            }
        }
    }

    throw;
}

bool inBounds(int i, int j)
{
    return i >= 0 && i < m && j >= 0 && j < n;
}

bool findToMove(const std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> &to_move, int ci, int cj, int di, int dj)
{
    if (grid[ci][cj] == '#')
    {
        to_move = {};
        return false;
    }

    if (grid[ci][cj] == 'O' || grid[ci][cj] == '@')
    {
        to_move.insert(std::make_pair(ci, cj));
        return findToMove(grid, to_move, ci + di, cj + dj, di, dj);
    }

    return true;
}

std::vector<std::vector<char>> moveCells(const std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> to_move, int di, int dj)
{
    std::vector<std::vector<char>> new_grid;

    for (int i = 0; i < m; ++i)
    {
        std::vector<char> row;
        for (int j = 0; j < n; ++j)
        {
            auto point = std::make_pair(i, j);
            if (std::find(to_move.begin(), to_move.end(), point) == to_move.end())
            {
                row.push_back(grid[i][j]);
            }
            else
            {
                row.push_back('.');
            }
        }
        new_grid.push_back(row);
    }

    for (std::pair<int, int> p : to_move)
    {
        new_grid[p.first + di][p.second + dj] = grid[p.first][p.second];
    }

    return new_grid;
}

void displayGrid(const std::vector<std::vector<char>> &grid)
{
    for (std::vector<char> row : grid)
    {
        for (char c : row)
        {
            std::cout << c;
        }
        std::cout << '\n';
    }
}

long solve1(std::string input_path)
{
    std::vector<std::vector<char>> grid;

    std::string directions = readInput(input_path, grid);

    m = grid.size();
    n = grid[0].size();

    auto [ci, cj] = getStart(grid);

    int di, dj;

    for (char move : directions)
    {
        if (move == '^')
        {
            di = -1;
            dj = 0;

            std::set<std::pair<int, int>> to_move;

            findToMove(grid, to_move, ci, cj, di, dj);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == '>')
        {
            di = 0;
            dj = 1;

            std::set<std::pair<int, int>> to_move;

            findToMove(grid, to_move, ci, cj, di, dj);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == 'v')
        {
            di = 1;
            dj = 0;

            std::set<std::pair<int, int>> to_move;

            findToMove(grid, to_move, ci, cj, di, dj);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == '<')
        {
            di = 0;
            dj = -1;

            std::set<std::pair<int, int>> to_move;

            findToMove(grid, to_move, ci, cj, di, dj);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
    }

    long result = 0;

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (grid[i][j] == 'O')
            {
                result += i * 100 + j;
            }
        }
    }

    return result;
}

bool findToMoveLeft(const std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> &to_move, int ci, int cj)
{
    if (grid[ci][cj] == '#')
    {
        to_move = {};
        return false;
    }

    if (grid[ci][cj] == '[' || grid[ci][cj] == ']' || grid[ci][cj] == '@')
    {
        to_move.insert(std::make_pair(ci, cj));
        return findToMoveLeft(grid, to_move, ci, cj - 1);
    }

    return true;
}

bool findToMoveRight(const std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> &to_move, int ci, int cj)
{
    if (grid[ci][cj] == '#')
    {
        to_move = {};
        return false;
    }

    if (grid[ci][cj] == '[' || grid[ci][cj] == ']' || grid[ci][cj] == '@')
    {
        to_move.insert(std::make_pair(ci, cj));
        return findToMoveRight(grid, to_move, ci, cj + 1);
    }

    return true;
}

bool findToMoveVertical(const std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> &to_move, int ci, int cj, int di)
{

    auto point = std::make_pair(ci, cj);
    if (std::find(to_move.begin(), to_move.end(), point) != to_move.end())
    {
        return true;
    }

    if (grid[ci][cj] == '#')
    {
        to_move = {};
        return false;
    }

    if (grid[ci][cj] == '@')
    {
        to_move.insert(point);
        return findToMoveVertical(grid, to_move, ci + di, cj, di);
    }

    if (grid[ci][cj] == '[')
    {
        to_move.insert(point);
        bool other_bracket = findToMoveVertical(grid, to_move, ci, cj + 1, di);
        bool next_row = findToMoveVertical(grid, to_move, ci + di, cj, di);
        if (other_bracket && next_row)
        {
            return true;
        }
        else
        {
            to_move = {};
            return false;
        }
    }

    if (grid[ci][cj] == ']')
    {
        to_move.insert(point);
        bool other_bracket = findToMoveVertical(grid, to_move, ci, cj - 1, di);
        bool next_row = findToMoveVertical(grid, to_move, ci + di, cj, di);
        if (other_bracket && next_row)
        {
            return true;
        }
        else
        {
            to_move = {};
            return false;
        }
    }

    return true;
}

long solve2(std::string input_path)
{
    std::vector<std::vector<char>> grid;

    std::string directions = readInput2(input_path, grid);

    m = grid.size();
    n = grid[0].size();

    auto [ci, cj] = getStart(grid);

    int di, dj;

    for (char move : directions)
    {
        if (move == '^')
        {
            di = -1;
            dj = 0;

            std::set<std::pair<int, int>> to_move;

            findToMoveVertical(grid, to_move, ci, cj, di);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == '>')
        {
            di = 0;
            dj = 1;

            std::set<std::pair<int, int>> to_move;

            findToMoveRight(grid, to_move, ci, cj);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == 'v')
        {
            di = 1;
            dj = 0;

            std::set<std::pair<int, int>> to_move;

            findToMoveVertical(grid, to_move, ci, cj, di);

            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
        else if (move == '<')
        {
            di = 0;
            dj = -1;

            std::set<std::pair<int, int>> to_move;

            findToMoveLeft(grid, to_move, ci, cj);
            if (to_move.size() > 0)
            {
                grid = moveCells(grid, to_move, di, dj);
                ci += di;
                cj += dj;
            }
        }
    }

    long result = 0;

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (grid[i][j] == '[')
            {
                result += i * 100 + j;
            }
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "No filepath provided!" << std::endl;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 14 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 14 -- Part 2: " << solve2(input_path) << std::endl;
}