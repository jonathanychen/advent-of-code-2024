#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>

std::vector<std::vector<char>> ReadInput(std::string filepath)
{
	std::ifstream ifstream;
	ifstream.open(filepath);

	std::vector<std::vector<char>> result;
	std::string line;
	while (ifstream)
	{
		std::vector<char> row;
        	std::getline(ifstream, line);
        	if (line == "") break;
        	for (char c : line) row.push_back(c);

		result.push_back(row);
    	}
    	ifstream.close();

    	return result;
}

int CheckMatches(size_t i, size_t j, std::vector<std::vector<char>> matrix, std::string goal) {
	size_t m = matrix.size(), n = matrix[0].size();
	
	int num_matches = 0;

	size_t goal_len = goal.size();

	std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

	for (std::pair<int, int> direction : directions) {
		if (i + direction.first * (goal_len - 1) >= 0 
				&& i + direction.first * (goal_len - 1) < m 
				&& j + direction.second * (goal_len - 1) >= 0 
				&& j + direction.second * (goal_len - 1) < n) {
			bool valid = true;
			for (size_t g = 0; g < goal_len; ++g) {
				int ni = i + g * direction.first, nj = j + g * direction.second;
				if (matrix[ni][nj] != goal.at(g)) {
					valid = false;
					break;
				}
			}
			if (valid) {
				num_matches += 1;
			}
		}
	}

	return num_matches;
}

int Solve1(std::string input_path)
{
	std::vector<std::vector<char>> matrix = ReadInput(input_path);

	std::string goal = "XMAS";

	size_t m = matrix.size(), n = matrix[0].size();
	
	long result = 0;

	for (size_t i = 0; i < m; ++i) {
		for (size_t j = 0; j < n; ++j) {
			result += CheckMatches(i, j, matrix, goal);
		}
	}

	return result;
}

int CheckCrossMatches(size_t i, size_t j, std::vector<std::vector<char>> matrix) {
	int num_matches = 0;

	if (matrix[i+1][j-1] == 'M' && matrix[i+1][j+1] == 'M' && matrix[i-1][j-1] == 'S' && matrix[i-1][j+1] == 'S') {
		num_matches += 1;
	}
	if (matrix[i+1][j-1] == 'S' && matrix[i+1][j+1] == 'S' && matrix[i-1][j-1] == 'M' && matrix[i-1][j+1] == 'M') {
		num_matches += 1;
	}
	if (matrix[i+1][j-1] == 'S' && matrix[i+1][j+1] == 'M' && matrix[i-1][j-1] == 'S' && matrix[i-1][j+1] == 'M') {
		num_matches += 1;
	}
	if (matrix[i+1][j-1] == 'M' && matrix[i+1][j+1] == 'S' && matrix[i-1][j-1] == 'M' && matrix[i-1][j+1] == 'S') {
		num_matches += 1;
	}

	return num_matches;
}

int Solve2(std::string input_path)
{
	std::vector<std::vector<char>> matrix = ReadInput(input_path);

	size_t m = matrix.size(), n = matrix[0].size();

	long result = 0;

	for (size_t i = 1; i < m - 1; ++i) {
		for (size_t j = 1; j < n - 1; ++j) {
			if (matrix[i][j] == 'A') result += CheckCrossMatches(i, j, matrix);
		}
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "No filepath provided!" << std::endl;
		throw;
	}

	std::string input_path = std::string(argv[1]);

	std::cout << "Day 4 -- Part 1: " << Solve1(input_path) << std::endl;
	std::cout << "Day 4 -- Part 2: " << Solve2(input_path) << std::endl;
}
