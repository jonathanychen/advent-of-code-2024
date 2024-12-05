#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>

std::vector<std::string> ReadInput()
{
    std::ifstream ifstream;
    ifstream.open("./inputs/day3.txt");

    std::vector<std::string> result;
    std::string line;
    while (ifstream)
    {
        std::getline(ifstream, line);
        if (line == "")
            break;
        result.push_back(line);
    }
    ifstream.close();

    return result;
}

int Solve1()
{
    std::vector<std::string> contents = ReadInput();

    std::string delimiter = "mul(";

    long result = 0;

    for (std::string line : contents) {
	size_t pos_start = 0, pos_end, delimiter_len = delimiter.size();

	while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
		std::string num_delim = ",";
		size_t first_num_end = line.find(num_delim, pos_end);
		if (first_num_end == std::string::npos) {
			pos_start = pos_end + delimiter_len;
			continue;
		}

		std::string end_mul_delim = ")";
		size_t second_num_end = line.find(end_mul_delim, first_num_end + num_delim.size());
		if (second_num_end == std::string::npos) {
			pos_start = pos_end + delimiter_len;
			continue;
		}

		try {
			size_t first_num_start = pos_end + delimiter_len + 1;

			for (char c : line.substr(first_num_start, first_num_end - first_num_start)) {
				if (!(isdigit(c))) {
					throw (std::string("First string not a number"));
				}
			}

			size_t second_num_start = first_num_end + num_delim.size() + 1;

			for (char c : line.substr(second_num_start, second_num_end - second_num_start)) {
				if (!(isdigit(c))) {
					throw (std::string("Second string not a number"));
				}
			}
			
			int first_num = std::stoi(line.substr(pos_end+delimiter_len, first_num_end));
			int second_num = std::stoi(line.substr(first_num_end+num_delim.size(), second_num_end));

			result += first_num * second_num;
		} catch (std::string error) {
			// do nothing
		}

		pos_start = pos_end + delimiter_len;
	}
    }	

    return result;
}

int Solve2()
{
    std::vector<std::string> contents = ReadInput();

    std::string delimiter = "mul(";

    std::string do_delim = "do()";
    std::string dont_delim = "don't()";

    bool process = true;

    long result = 0;

    for (std::string line : contents) {
	size_t pos_start = 0, pos_end, delimiter_len = delimiter.size();

	while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
		if (process) {
			size_t next_dont = line.find(dont_delim, pos_start);

			if (next_dont != std::string::npos && next_dont < pos_end) {
				pos_start = next_dont + dont_delim.size();
				process = false;
				continue;
			}

			std::string num_delim = ",";
			size_t first_num_end = line.find(num_delim, pos_end);
			if (first_num_end == std::string::npos) {
				pos_start = pos_end + delimiter_len;
				continue;
			}

			std::string end_mul_delim = ")";
			size_t second_num_end = line.find(end_mul_delim, first_num_end + num_delim.size());
			if (second_num_end == std::string::npos) {
				pos_start = pos_end + delimiter_len;
				continue;
			}

			try {
				size_t first_num_start = pos_end + delimiter_len + 1;

				for (char c : line.substr(first_num_start, first_num_end - first_num_start)) {
					if (!(isdigit(c))) {
						throw (std::string("First string not a number"));
					}
				}

				size_t second_num_start = first_num_end + num_delim.size() + 1;

				for (char c : line.substr(second_num_start, second_num_end - second_num_start)) {
					if (!(isdigit(c))) {
						throw (std::string("Second string not a number"));
					}
				}
			
				int first_num = std::stoi(line.substr(pos_end+delimiter_len, first_num_end));
				int second_num = std::stoi(line.substr(first_num_end+num_delim.size(), second_num_end));

				result += first_num * second_num;
			} catch (std::string error) {
				// do nothing
			}

			pos_start = pos_end + delimiter_len;

		} else {
			size_t next_do = line.find(do_delim, pos_start);
			if (next_do == std::string::npos) break;

			pos_start = next_do + do_delim.size();
			process = true;
		}
	}
    }	

    return result;
}

int main()
{
    std::cout << "Day 3 -- Part 1: " << Solve1() << std::endl;
    std::cout << "Day 3 -- Part 2: " << Solve2() << std::endl;
}
