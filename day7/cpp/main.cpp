#include <iostream>
#include <fstream>
#include <vector>

void readInput(std::string input_path, std::vector<long>& totals, std::vector<std::vector<long>>& values) {
    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;
    while (ifstream) {
        std::getline(ifstream, line);

        if (line == "") break;

        size_t delim_ind = line.find(':');

        totals.push_back(std::stol(line.substr(0, delim_ind)));

        size_t pos_start = delim_ind + 2, pos_end;

        std::vector<long> row;
        while ((pos_end = line.find(' ', pos_start)) != std::string::npos) {
            row.push_back(std::stol(line.substr(pos_start, pos_end - pos_start)));
            pos_start = pos_end + 1;
        }
        row.push_back(std::stol(line.substr(pos_start)));

        values.push_back(row);
    }
}

bool backtrack1(long total, std::vector<long> row, size_t i, long long curr) {
    if (i == row.size()) 
        return total == curr;

    bool add_next = backtrack1(total, row, i+1, curr + row[i]);
    if (add_next) 
        return true;
    

    bool multiply_next = backtrack1(total, row, i+1, curr * row[i]);
    if (multiply_next)
        return true;

    return false;
}

bool backtrack2(long total, std::vector<long> row, size_t i, long long curr) {
    if (i == row.size()) 
        return total == curr;

    if (curr > total) 
        return false;

    bool add_next = backtrack2(total, row, i+1, curr + row[i]);
    if (add_next) 
        return true;
    

    bool multiply_next = backtrack2(total, row, i+1, curr * row[i]);
    if (multiply_next)
        return true;

    long concat_num = std::stol(std::to_string(curr) + std::to_string(row[i]));
    bool concat_next = backtrack2(total, row, i+1, concat_num);
    if (concat_next)
        return true;

    return false;
}

long long solve1(std::string input_path) {

    std::vector<long> totals;
    std::vector<std::vector<long>> values;

    readInput(input_path, totals, values);

    if (totals.size() != values.size()) {
        throw;
    }

    long long int result = 0;

    for (size_t i = 0; i < totals.size(); ++i) {
        if (backtrack1(totals[i], values[i], 0, 0)) {
            result += totals[i];
        }
    }

    return result;
}

long long solve2(std::string input_path) {
    std::vector<long> totals;
    std::vector<std::vector<long>> values;

    readInput(input_path, totals, values);

    if (totals.size() != values.size()) {
        throw;
    }

    long long int result = 0;

    for (size_t i = 0; i < totals.size(); ++i) {
        if (backtrack2(totals[i], values[i], 0, 0)) {
            result += totals[i];
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

    std::cout << "Day 7 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 7 -- Part 2: " << solve2(input_path) << std::endl;
}