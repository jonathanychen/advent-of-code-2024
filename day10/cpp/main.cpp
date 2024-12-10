#include <iostream>
#include <fstream>
#include <vector>
#include <set>

static std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

std::vector<std::vector<int>> readInput(std::string input_path)
{
    std::vector<std::vector<int>> result;

    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;

    while (ifstream)
    {
        std::getline(ifstream, line);
        if (line == "")
            break;

        std::vector<int> row;

        for (char c : line)
        {
            row.push_back(std::stoi(std::string(1, c)));
        }

        result.push_back(row);
    }

    return result;
}

bool inBounds(size_t i, size_t j, size_t m, size_t n)
{
    return i >= 0 && i < m && j >= 0 && j < n;
}

void dfs1(const std::vector<std::vector<int>> &matrix, size_t i, size_t j, std::set<std::tuple<int, int>> &ends)
{
    if (matrix[i][j] == 9)
    {
        ends.insert(std::make_tuple(i, j));
    }

    size_t m = matrix.size(), n = matrix[0].size();

    for (auto [di, dj] : directions)
    {
        size_t ni = i + di, nj = j + dj;

        if (inBounds(ni, nj, m, n) && matrix[ni][nj] == matrix[i][j] + 1)
        {
            dfs1(matrix, ni, nj, ends);
        }
    }
}

int solve1(std::string input_path)
{
    std::vector<std::vector<int>> matrix = readInput(input_path);

    int result = 0;

    size_t m = matrix.size(), n = matrix[0].size();

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 0)
            {
                std::set<std::tuple<int, int>> ends;
                dfs1(matrix, i, j, ends);
                result += ends.size();
            }
        }
    }

    return result;
}

int dfs2(const std::vector<std::vector<int>> &matrix, size_t i, size_t j)
{
    if (matrix[i][j] == 9)
        return 1;

    int result = 0;

    size_t m = matrix.size(), n = matrix[0].size();

    for (auto [di, dj] : directions)
    {
        size_t ni = i + di, nj = j + dj;

        if (inBounds(ni, nj, m, n) && matrix[ni][nj] == matrix[i][j] + 1)
        {
            result += dfs2(matrix, ni, nj);
        }
    }

    return result;
}

int solve2(std::string input_path)
{
    std::vector<std::vector<int>> matrix = readInput(input_path);

    int result = 0;

    size_t m = matrix.size(), n = matrix[0].size();

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 0)
            {
                result += dfs2(matrix, i, j);
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
        throw;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 9 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 9 -- Part 2: " << solve2(input_path) << std::endl;
}