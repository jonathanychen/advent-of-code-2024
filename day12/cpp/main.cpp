#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>

static const std::vector<std::pair<int, int>> DIRECTIONS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
size_t m, n;

std::vector<std::vector<char>> readInput(std::string input_path)
{
    std::vector<std::vector<char>> matrix = {};

    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;

    while (ifstream)
    {
        std::getline(ifstream, line);
        if (line == "")
            break;

        std::vector<char> row = {};

        for (char c : line)
        {
            row.push_back(c);
        }

        matrix.push_back(row);
    }

    m = matrix.size();
    n = matrix[0].size();

    return matrix;
}

bool inBounds(size_t i, size_t j, size_t m, size_t n)
{
    return i >= 0 && i < m && j >= 0 && j < n;
}

template <typename T>
bool contains(const std::set<T> &set, const T &item)
{
    return set.find(item) != set.end();
}

bool isEdge(const std::vector<std::vector<char>> &matrix, size_t ni, size_t nj, char curr)
{
    return (inBounds(ni, nj, m, n) && matrix[ni][nj] != curr) || !inBounds(ni, nj, m, n);
}

bool validNext(const std::vector<std::vector<char>> &matrix, const std::set<std::pair<size_t, size_t>> &seen, size_t ni, size_t nj, char curr)
{
    return inBounds(ni, nj, m, n) && !contains(seen, std::make_pair(ni, nj)) && matrix[ni][nj] == curr;
}

long findPrice(const std::vector<std::vector<char>> &matrix, std::set<std::pair<size_t, size_t>> &seen, size_t i, size_t j, char start)
{
    int perimeter = 0, area = 0;

    std::vector<std::pair<int, int>> stack = {};

    stack.push_back(std::make_pair(i, j));

    seen.insert(std::make_pair(i, j));

    while (stack.size() > 0)
    {
        auto [ci, cj] = stack.back();
        stack.pop_back();

        for (auto [di, dj] : DIRECTIONS)
        {
            size_t ni = ci + di, nj = cj + dj;

            if (isEdge(matrix, ni, nj, start))
            {
                perimeter += 1;
            }

            if (inBounds(ni, nj, m, n) && !contains(seen, std::make_pair(ni, nj)) && matrix[ni][nj] == start)
            {
                stack.push_back(std::make_pair(ni, nj));
                seen.insert(std::make_pair(ni, nj));
            }
        }

        area += 1;
    }

    return perimeter * area;
}

long solve1(std::string input_path)
{
    std::vector<std::vector<char>> matrix = readInput(input_path);

    std::set<std::pair<size_t, size_t>> seen = {};

    long result = 0;

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (!contains(seen, std::make_pair(i, j)))
            {
                result += findPrice(matrix, seen, i, j, matrix[i][j]);
            }
        }
    }

    return result;
}

long findPrice2(const std::vector<std::vector<char>> &matrix, std::set<std::pair<size_t, size_t>> &seen_tiles, std::set<std::tuple<size_t, size_t, size_t>> &seen_edges, size_t i, size_t j, char start)
{
    int edges = 0, area = 0;

    std::vector<std::pair<size_t, size_t>> stack = {};

    stack.push_back(std::make_pair(i, j));

    seen_tiles.insert(std::make_pair(i, j));

    while (stack.size() > 0)
    {
        auto [ci, cj] = stack.back();
        stack.pop_back();

        for (size_t k = 0; k < 4; ++k)
        {
            auto [di, dj] = DIRECTIONS[k];

            size_t ni = ci + di, nj = cj + dj;

            if (isEdge(matrix, ni, nj, start) && !contains(seen_edges, std::make_tuple(ci, cj, k)))
            {
                size_t ni2 = ci, nj2 = cj;
                while ((inBounds(ni2, nj2, m, n) && matrix[ni2][nj2] == start) && ((inBounds(ni2 + di, nj2 + dj, m, n) && matrix[ni2 + di][nj2 + dj] != start) || !inBounds(ni2 + di, nj2 + dj, m, n)))
                {
                    seen_edges.insert(std::make_tuple(ni2, nj2, k));
                    ni2 += DIRECTIONS[(k + 1) % 4].first;
                    nj2 += DIRECTIONS[(k + 1) % 4].second;
                }

                ni2 = ci;
                nj2 = cj;
                while ((inBounds(ni2, nj2, m, n) && matrix[ni2][nj2] == start) && ((inBounds(ni2 + di, nj2 + dj, m, n) && matrix[ni2 + di][nj2 + dj] != start) || !inBounds(ni2 + di, nj2 + dj, m, n)))
                {
                    seen_edges.insert(std::make_tuple(ni2, nj2, k));
                    ni2 -= DIRECTIONS[(k + 1) % 4].first;
                    nj2 -= DIRECTIONS[(k + 1) % 4].second;
                }

                edges += 1;
            }

            if (inBounds(ni, nj, m, n) && !contains(seen_tiles, std::make_pair(ni, nj)) && matrix[ni][nj] == start)
            {
                stack.push_back(std::make_pair(ni, nj));
                seen_tiles.insert(std::make_pair(ni, nj));
            }
        }

        area += 1;
    }

    return edges * area;
}

long solve2(std::string input_path)
{
    std::vector<std::vector<char>> matrix = readInput(input_path);

    std::set<std::pair<size_t, size_t>> seen_tiles = {};
    std::set<std::tuple<size_t, size_t, size_t>> seen_edges = {};

    long result = 0;

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (!contains(seen_tiles, std::make_pair(i, j)))
            {
                result += findPrice2(matrix, seen_tiles, seen_edges, i, j, matrix[i][j]);
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

    std::cout << "Day 12 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 12 -- Part 2: " << solve2(input_path) << std::endl;
}