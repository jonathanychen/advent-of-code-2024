#include <iostream>
#include <fstream>
#include <vector>
#include <set>

std::string readInput(std::string input_path)
{
    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string result;
    std::getline(ifstream, result);
    return result;
}

std::vector<int> constructDisk(std::string input)
{
    std::vector<int> disk;
    int id = 0;
    for (size_t i = 0; i < input.size(); ++i)
    {
        int curr = std::stoi(std::string(1, input[i]));

        for (size_t j = 0; j < curr; ++j)
        {
            disk.push_back(i % 2 == 0 ? id : -1);
        }
        if (i % 2 == 0)
        {
            id += 1;
        }
    }
    return disk;
}

long calculateChecksum(const std::vector<int> &disk)
{
    long result = 0;

    for (size_t i = 0; i < disk.size(); ++i)
    {
        if (disk[i] != -1)
        {
            result += i * disk[i];
        }
    }

    return result;
}

long solve1(std::string input_path)
{
    std::string input = readInput(input_path);

    std::vector<int> disk = constructDisk(input);

    size_t left = 0, right = disk.size() - 1;

    while (left < right)
    {
        while (left < disk.size() && disk[left] != -1)
        {
            left += 1;
        }
        while (right >= 0 && disk[right] == -1)
        {
            right -= 1;
        }

        if (left >= right)
            break;

        disk[left] = disk[right];
        disk[right] = -1;
    }

    return calculateChecksum(disk);
}

long solve2(std::string input_path)
{
    std::string input = readInput(input_path);

    std::vector<int> disk = constructDisk(input);

    std::set<int> tried;

    size_t right = disk.size() - 1;

    // For each file block, try to fit it into every space left of it
    while (right >= 0)
    {
        while (right >= 0 && disk[right] == -1)
        {
            right -= 1;
        }

        if (right < 0)
            break;

        int curr_id = disk[right];

        if (curr_id == 0)
        {
            break;
        }

        // Find size of file we want to move
        size_t file_start = right;

        while (file_start >= 0 && disk[file_start] == curr_id)
        {
            file_start -= 1;
        }

        if (file_start < 0)
            break;

        // If file was already tried (we moved it sometime before), ignore it
        if (tried.find(curr_id) != tried.end())
        {
            right = file_start;
            continue;
        }

        size_t space_required = right - file_start;

        // Find and try every space found in our disk
        size_t left = 0;
        while (left < right)
        {
            while (left < right && disk[left] != -1)
            {
                left += 1;
            }

            if (left >= right)
                break;

            size_t space_end = left;

            while (disk[space_end] == -1)
            {
                space_end += 1;
            }

            size_t space_available = space_end - left;

            // If space is valid, overwrite the appropriate slots, otherwise try next
            if (space_required <= space_available)
            {
                for (size_t i = left; i < left + space_required; ++i)
                {
                    disk[i] = curr_id;
                }

                for (size_t i = right; i > right - space_required; --i)
                {
                    disk[i] = -1;
                }
                break;
            }
            else
            {
                left = space_end;
            }
        }

        right = file_start;

        tried.insert(curr_id);
    }

    return calculateChecksum(disk);
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