#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

struct Machine
{
    std::pair<long, long> button_a, button_b, goal;
};

std::vector<Machine> readInput(std::string input_path)
{
    std::ifstream ifstream(input_path);

    std::vector<Machine> result = {};

    std::string line;

    while (ifstream)
    {

        Machine new_machine;

        std::getline(ifstream, line);

        std::regex button_a_regex("Button A: X\\+([0-9]+), Y\\+([0-9]+)");
        std::smatch m;
        std::regex_match(line, m, button_a_regex);
        std::pair<long, long> button_a = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
        new_machine.button_a = button_a;

        std::getline(ifstream, line);

        std::regex button_b_regex("Button B: X\\+([0-9]+), Y\\+([0-9]+)");
        std::regex_match(line, m, button_b_regex);
        std::pair<long, long> button_b = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
        new_machine.button_b = button_b;

        std::getline(ifstream, line);

        std::regex goal_regex("Prize: X=([0-9]+), Y=([0-9]+)");
        std::regex_match(line, m, goal_regex);
        std::pair<long, long> goal = std::make_pair(std::stoi(m[1]), std::stoi(m[2]));
        new_machine.goal = goal;

        result.push_back(new_machine);

        std::getline(ifstream, line);
    }

    return result;
}

long num_tokens(Machine m)
{
    double a_presses = (double)(m.goal.first * m.button_b.second - m.goal.second * m.button_b.first) / (m.button_a.first * m.button_b.second - m.button_a.second * m.button_b.first);
    double b_presses = (double)(m.button_a.first * m.goal.second - m.button_a.second * m.goal.first) / (m.button_a.first * m.button_b.second - m.button_a.second * m.button_b.first);

    if (a_presses == (long)a_presses && b_presses == (long)b_presses)
    {
        return 3 * a_presses + b_presses;
    }

    return 0;
}

int solve1(std::string input_path)
{
    std::vector<Machine> machines = readInput(input_path);

    int result = 0;

    for (Machine m : machines)
    {
        result += num_tokens(m);
    }

    return result;
}

long solve2(std::string input_path)
{
    std::vector<Machine> machines = readInput(input_path);

    long result = 0;

    for (Machine m : machines)
    {
        m.goal = std::make_pair(m.goal.first + 10000000000000, m.goal.second + 10000000000000);

        result += num_tokens(m);
    }

    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "No filepath provided!" << std::endl;
    }

    std::string input_path = std::string(argv[1]);

    std::cout << "Day 13 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 13 -- Part 2: " << solve2(input_path) << std::endl;
}