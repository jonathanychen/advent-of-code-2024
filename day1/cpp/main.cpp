#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <map>
#include <algorithm>

std::vector<std::string> readInput()
{
    std::ifstream ifstream;
    ifstream.open("./inputs/day1.txt");

    std::vector<std::string> result;
    std::string line;
    while (ifstream)
    {
        std::getline(ifstream, line);
        result.push_back(line);
    }
    ifstream.close();

    return result;
}

std::tuple<std::vector<int>, std::vector<int>> readInts(std::vector<std::string> contents)
{
    std::vector<int> list1;
    std::vector<int> list2;

    std::string delimiter = "   ";

    for (std::string s : contents)
    {
        size_t pos = s.find(delimiter);

        if (pos == std::string::npos)
            break;

        std::string s1 = s.substr(0, pos);
        int n1 = std::stoi(s1);
        list1.push_back(n1);

        std::string s2 = s.substr(pos + delimiter.size());
        int n2 = std::stoi(s2);
        list2.push_back(n2);
    }

    return std::make_tuple(list1, list2);
}

int abs(int n)
{
    return (n < 0 ? -n : n);
}

int solve1(std::vector<int> list1, std::vector<int> list2)
{
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int result = 0;

    for (size_t i = 0; i < list1.size(); i++)
    {
        result += abs(list1[i] - list2[i]);
    }

    return result;
}

int solve2(std::vector<int> list1, std::vector<int> list2)
{
    std::map<int, int> counter;

    for (int i : list2)
    {
        if (counter.find(i) == counter.end())
        {
            counter[i] = 0;
        }
        counter[i] += 1;
    }

    int result = 0;

    for (int i : list1)
    {
        if (counter.find(i) == counter.end())
        {
            continue;
        }

        result += counter[i] * i;
    }

    return result;
}

int main()
{
    std::vector<std::string> contents = readInput();

    std::vector<int> list1, list2;
    std::tie(list1, list2) = readInts(contents);

    std::cout << "Day 1 -- Part 1: " << solve1(list1, list2) << '\n';
    std::cout << "Day 1 -- Part 2: " << solve2(list1, list2) << '\n';
}
