#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::vector<long> readInput(std::string input_path)
{
    std::vector<long> stones;

    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;
    std::getline(ifstream, line);

    size_t pos_start = 0, pos_end;

    while ((pos_end = line.find(" ", pos_start)) != std::string::npos)
    {
        stones.push_back(std::stoi(line.substr(pos_start, pos_end - pos_start)));

        pos_start = pos_end + 1;
    }

    stones.push_back(std::stol(line.substr(pos_start)));

    return stones;
}

std::vector<long> blink(std::vector<long> stones)
{
    std::vector<long> new_stones;

    for (long stone : stones)
    {
        std::string str_stone = std::to_string(stone);

        if (stone == 0)
        {
            new_stones.push_back(1);
        }
        else if (str_stone.size() % 2 == 0)
        {
            long left_stone = std::stoi(str_stone.substr(0, str_stone.size() / 2));
            long right_stone = std::stoi(str_stone.substr(str_stone.size() / 2));

            new_stones.push_back(left_stone);
            new_stones.push_back(right_stone);
        }
        else
        {
            new_stones.push_back(stone * 2024);
        }
    }

    return new_stones;
}

long long solve(std::string input_path, int iterations)
{
    std::vector<long> stones = readInput(input_path);

    std::map<long, long> stone_counts = {};

    for (long stone : stones)
    {
        if (stone_counts.find(stone) == stone_counts.end())
        {
            stone_counts[stone] = 0;
        }

        stone_counts[stone] += 1;
    }

    for (long i = 0; i < iterations; ++i)
    {
        std::map<long, long> new_counts = {};

        for (auto [stone, count] : stone_counts)
        {
            std::string str_stone = std::to_string(stone);

            if (stone == 0)
            {
                new_counts[1] += count;
            }
            else if (str_stone.size() % 2 == 0)
            {
                long left_stone = std::stoi(str_stone.substr(0, str_stone.size() / 2));
                long right_stone = std::stoi(str_stone.substr(str_stone.size() / 2));

                new_counts[left_stone] += count;
                new_counts[right_stone] += count;
            }
            else
            {
                new_counts[stone * 2024] += count;
            }
        }

        stone_counts = new_counts;
    }

    long long result = 0;

    for (auto [num, count] : stone_counts)
        result += count;

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

    std::cout << "Day 11 -- Part 1: " << solve(input_path, 25) << std::endl;
    std::cout << "Day 11 -- Part 2: " << solve(input_path, 75) << std::endl;
}