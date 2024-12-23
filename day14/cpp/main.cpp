#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

static int m = 103, n = 101;

struct Robot
{
    std::pair<int, int> pos;
    std::pair<int, int> vel;
};

std::vector<Robot> readInput(std::string input_path)
{
    std::vector<Robot> result = {};

    std::ifstream ifstream(input_path);

    std::regex robot_regex("p=([0-9]+),([0-9]+) v=([\\-]?[0-9]+),([\\-]?[0-9]+)");

    std::string line;
    while (std::getline(ifstream, line))
    {
        Robot robot;

        std::smatch m;

        std::regex_match(line, m, robot_regex);

        std::pair<int, int> pos = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
        std::pair<int, int> vel = std::make_pair(std::stoi(m[3]), std::stoi(m[4]));

        robot.pos = pos;
        robot.vel = vel;

        result.push_back(robot);
    }

    return result;
}

long mod(long a, long b)
{
    return (a % b + b) % b;
}

bool inBounds(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

int countNeighbors(const std::array<std::array<int, 103>, 101> &grid, int x, int y)
{
    int neighbors = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (inBounds(x + dx, y + dy) && grid[x + dx][y + dy] > 0)
            {
                neighbors += 1;
            }
        }
    }
    return neighbors;
}

void displayGrid(const std::array<std::array<int, 103>, 101> &grid)
{
    for (std::array<int, 103> row : grid)
    {
        for (int cell : row)
        {
            if (cell == 0)
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << '*';
            }
        }
        std::cout << '\n';
    }
}

long solve1(std::string input_path)
{
    std::vector<Robot> robots = readInput(input_path);

    int iterations = 100;

    for (int i = 0; i < iterations; ++i)
    {
        for (Robot &r : robots)
        {
            std::pair<int, int> new_pos = std::make_pair(mod(r.pos.first + r.vel.first, n), mod(r.pos.second + r.vel.second, m));
            r.pos = new_pos;
        }
    }

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    for (Robot r : robots)
    {
        if (r.pos.first < n / 2 && r.pos.second < m / 2)
        {
            q1 += 1;
        }
        else if (r.pos.first < n / 2 && r.pos.second > m / 2)
        {
            q2 += 1;
        }
        else if (r.pos.first > n / 2 && r.pos.second < m / 2)
        {
            q3 += 1;
        }
        else if (r.pos.first > n / 2 && r.pos.second > m / 2)
        {
            q4 += 1;
        }
    }

    return q1 * q2 * q3 * q4;
}

long solve2(std::string input_path)
{
    std::vector<Robot> robots = readInput(input_path);

    int iterations = m * n;

    for (int i = 1; i <= iterations; ++i)
    {
        for (Robot &r : robots)
        {
            std::pair<int, int> new_pos = std::make_pair(mod(r.pos.first + r.vel.first, n), mod(r.pos.second + r.vel.second, m));
            r.pos = new_pos;
        }

        std::array<std::array<int, 103>, 101> grid{};

        for (Robot r : robots)
        {
            grid[r.pos.first][r.pos.second] += 1;
        }

        for (int x = 0; x < 101; ++x)
        {
            for (int y = 0; y < 103; ++y)
            {
                if (countNeighbors(grid, x, y) == 8)
                {
                    displayGrid(grid);
                    return i;
                }
            }
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "No filepath provided!" << std::endl;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 14 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 14 -- Part 2: " << solve2(input_path) << std::endl;
}