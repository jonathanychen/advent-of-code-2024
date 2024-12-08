#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

std::vector<std::string> readInput()
{
    std::ifstream ifstream;
    ifstream.open("./inputs/input.txt");

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

int testIsSafe(std::vector<int> list)
{
    int first_diff = list[1] - list[0];
    if (first_diff == 0)
        return 0;

    bool increasing = first_diff > 0;

    for (size_t i = 1; i < list.size(); i++)
    {
        int curr_diff = list[i] - list[i - 1];
        if (curr_diff == 0)
            return 0;

        bool curr_increasing = curr_diff > 0;

        if (curr_increasing != increasing)
            return 0;

        int abs_diff = abs(curr_diff);
        if (!(abs_diff == 1 || abs_diff == 2 || abs_diff == 3))
            return 0;
    }

    return 1;
}

std::vector<int> splitIntoInts(std::string line)
{
    std::vector<int> result;
    std::string delimiter = " ";
    size_t pos_start = 0, pos_end, delimiter_len = delimiter.size();

    while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos)
    {
        std::string token = line.substr(pos_start, pos_end - pos_start);
        int num = std::stoi(token);
        result.push_back(num);
        pos_start = pos_end + delimiter_len;
    }

    result.push_back(std::stoi(line.substr(pos_start)));

    return result;
}

int solve1()
{
    std::vector<std::string> contents = readInput();

    int result = 0;

    for (std::string line : contents)
    {
        std::vector<int> nums = splitIntoInts(line);
        result += testIsSafe(nums);
    }

    return result;
}

int solve2()
{
    std::vector<std::string> contents = readInput();

    int result = 0;

    for (std::string line : contents)
    {
        std::vector<int> nums = splitIntoInts(line);

        if (testIsSafe(nums))
        {
            result += 1;
        }
        else
        {
            for (size_t i = 0; i < nums.size(); i++)
            {
                std::vector<int> test_slice = std::vector<int>(nums.begin(), nums.begin() + i);
                std::vector<int> right_slice = std::vector<int>(nums.begin() + i + 1, nums.end());
                test_slice.insert(test_slice.end(), right_slice.begin(), right_slice.end());

                if (testIsSafe(test_slice) == 1)
                {
                    result += 1;
                    break;
                }
            }
        }
    }

    return result;
}

int main()
{
    std::cout << "Day 2 -- Part 1: " << solve1() << std::endl;
    std::cout << "Day 2 -- Part 2: " << solve2() << std::endl;
}
