#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

void readInput(std::string input_path, std::vector<std::vector<char>>& matrix) {
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
        matrix.push_back(row);
    }
}

std::tuple<int, int> getDimensions(const std::vector<std::vector<char>>& matrix) {
    return std::make_tuple(matrix.size(), matrix[0].size());
}

std::map<char, std::vector<std::tuple<int, int>>> getPointMap(const std::vector<std::vector<char>>& matrix) {
    std::map<char, std::vector<std::tuple<int, int>>> point_map;

    auto [m, n] = getDimensions(matrix);

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            char c = matrix[i][j];
            if (c != '.') {
                point_map[c].push_back(std::make_tuple(i, j));
            }
        }
    }

    return point_map;
}

int solve1(std::string input_path) {
    std::vector<std::vector<char>> matrix;
    readInput(input_path, matrix);

    auto [m, n] = getDimensions(matrix);

    auto point_map = getPointMap(matrix);

    std::set<std::tuple<int, int>> antinodes = {};

    for (auto [key_char, points] : point_map) {
        size_t points_len = points.size();

        for (size_t i = 0; i < points_len; ++i) {
            for (size_t j = 0; j < i; ++j) {
                auto [y1, x1] = points[i];
                auto [y2, x2] = points[j];

                int dy = y2 - y1, dx = x2 - x1;

                int ny1 = y2 + dy, nx1 = x2 + dx;
                if (ny1 >= 0 && ny1 < m && nx1 >= 0 && nx1 < n) {
                    std::tuple<int, int> antinode1 = std::make_tuple(ny1, nx1);
                    antinodes.insert(antinode1);
                }
                int ny2 = y1 - dy, nx2 = x1 - dx;
                if (ny2 >= 0 && ny2 < m && nx2 >= 0 && nx2 < n) {
                    std::tuple<int, int> antinode2 = std::make_tuple(ny2, nx2);
                    antinodes.insert(antinode2);
                }
            }
        }
    }

    return antinodes.size();
}

int solve2(std::string input_path) {
    std::vector<std::vector<char>> matrix;
    readInput(input_path, matrix);

    auto [m, n] = getDimensions(matrix);

    auto point_map = getPointMap(matrix);

    std::set<std::tuple<int, int>> antinodes = {};

    for (auto [key_char, points] : point_map) {
        size_t points_len = points.size();

        for (size_t i = 0; i < points_len; ++i) {
            for (size_t j = 0; j < i; ++j) {
                auto [y1, x1] = points[i];
                auto [y2, x2] = points[j];

                int dy = y2 - y1, dx = x2 - x1;

                while (y1 >= 0 && y1 < m && x1 >= 0 && x1 < n) {
                    antinodes.insert(std::make_tuple(y1, x1));
                    y1 = y1 + dy;
                    x1 = x1 + dx;
                }

                while (y2 >= 0 && y2 < m && x2 >= 0 && x2 < n) {
                    antinodes.insert(std::make_tuple(y2, x2));
                    y2 = y2 - dy;
                    x2 = x2 - dx;
                }
            }
        }
    }

    return antinodes.size();
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "No filepath provided!" << std::endl;
        throw;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 8 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 8 -- Part 2: " << solve2(input_path) << std::endl;
}