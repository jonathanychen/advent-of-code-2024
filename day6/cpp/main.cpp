#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>

static std::vector<std::pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void ReadInput(std::string input_path, std::vector<std::vector<char>>& result) {

    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;
    while (ifstream) {
        std::getline(ifstream, line);
        if (line == "") break;

        std::vector<char> row;

        for (char c : line) {
            row.push_back(c);
        }

        result.push_back(row);
    }
}

std::pair<size_t, size_t> GetStartPos(std::vector<std::vector<char>> matrix) {
    size_t m = matrix.size(), n = matrix[0].size();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i][j] == '^') {
                return std::make_pair(i, j);
            }
        }
    }

    throw;
}

bool InBounds(size_t i, size_t j, size_t m, size_t n) {
    return i >= 0 && i < m && j >= 0 && j < n;
}

int Solve1(std::string input_path) {
    std::vector<std::vector<char>> matrix;

    ReadInput(input_path, matrix);

    auto [curr_i, curr_j] = GetStartPos(matrix);

    size_t direction_index = 0;

    size_t m = matrix.size(), n = matrix[0].size();

    std::set<std::pair<size_t, size_t>> coords;

    while (InBounds(curr_i, curr_j, m, n)) {
        coords.insert(std::make_pair(curr_i, curr_j));

        size_t new_i = curr_i + DIRECTIONS[direction_index].first, new_j = curr_j + DIRECTIONS[direction_index].second;

        if (InBounds(new_i, new_j, m, n) && matrix[new_i][new_j] == '#') {
            direction_index = (direction_index + 1) % DIRECTIONS.size();
        } else {
            curr_i = new_i;
            curr_j = new_j;
        }

    }

    return coords.size();
}

bool MakesLoop(std::vector<std::vector<char>>& matrix) {
    auto [curr_i, curr_j] = GetStartPos(matrix);

    size_t direction_index = 0;

    size_t m = matrix.size(), n = matrix[0].size();

    int path_len = 0;

    while (InBounds(curr_i, curr_j, m, n)) {
        if (path_len > m * n) {
            return true;
        }

        path_len += 1;

        size_t new_i = curr_i + DIRECTIONS[direction_index].first, new_j = curr_j + DIRECTIONS[direction_index].second;

        if (InBounds(new_i, new_j, m, n) && matrix[new_i][new_j] == '#') {
            direction_index = (direction_index + 1) % DIRECTIONS.size();
        } else {
            curr_i = new_i;
            curr_j = new_j;
        }

    }

    return false;
}

int Solve2(std::string input_path) {
    std::vector<std::vector<char>> matrix;

    ReadInput(input_path, matrix);

    auto [curr_i, curr_j] = GetStartPos(matrix);

    size_t direction_index = 0;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    size_t m = matrix.size(), n = matrix[0].size();

    int result = 0;

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (matrix[i][j] == '.') {
                matrix[i][j] = '#';
                if (MakesLoop(matrix)) {
                    result += 1;
                }
                matrix[i][j] = '.';
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "No filepath provided!" << std::endl;
        throw;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 6 -- Part 1: " << Solve1(input_path) << std::endl;
    std::cout << "Day 6 -- Part 2: " << Solve2(input_path) << std::endl;
}