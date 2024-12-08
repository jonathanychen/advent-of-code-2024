#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <deque>
#include <set>

void readInput(std::string input_path, std::vector<std::pair<int, int>> &edges, std::vector<std::vector<int>> &updates)
{
    std::ifstream ifstream;
    ifstream.open(input_path);

    std::string line;
    while (ifstream)
    {
        std::getline(ifstream, line);
        if (line == "")
            continue;

        size_t pipe_pos;
        if ((pipe_pos = line.find('|')) != std::string::npos)
        {
            int e1 = std::stoi(line.substr(0, pipe_pos));
            int e2 = std::stoi(line.substr(pipe_pos + 1, line.size()));

            edges.push_back(std::make_pair(e1, e2));
        }
        else
        {
            std::vector<int> update;
            size_t pos_start = 0, pos_end;
            while ((pos_end = line.find(',', pos_start)) != std::string::npos)
            {
                int page_num = std::stoi(line.substr(pos_start, pos_end - pos_start));
                update.push_back(page_num);
                pos_start = pos_end + 1;
            }
            update.push_back(std::stoi(line.substr(pos_start)));

            updates.push_back(update);
        }
    }
}

void topologicalSort(const std::vector<std::pair<int, int>> &edges, std::vector<int> &sequence)
{
    std::map<int, std::vector<int>> edge_map;
    for (std::pair<int, int> edge : edges)
    {
        if (edge_map.find(edge.first) == edge_map.end())
        {
            edge_map[edge.first];
        }
        edge_map[edge.first].push_back(edge.second);
    }

    std::map<int, int> indegrees;
    for (std::pair<int, int> edge : edges)
    {
        if (indegrees.find(edge.first) == indegrees.end())
        {
            indegrees[edge.first];
        }
        if (indegrees.find(edge.second) == indegrees.end())
        {
            indegrees[edge.second];
        }

        indegrees[edge.second] += 1;
    }

    std::deque<int> queue;

    for (std::pair<int, int> pair : indegrees)
    {
        if (pair.second == 0)
        {
            queue.push_back(pair.first);
        }
    }

    while (queue.size() > 0)
    {
        int curr = queue.front();
        queue.pop_front();

        for (int to : edge_map[curr])
        {
            indegrees[to] -= 1;
            if (indegrees[to] == 0)
            {
                queue.push_back(to);
            }
        }

        sequence.push_back(curr);
    }
}

bool validUpdate(std::map<int, std::set<int>> orders, std::vector<int> update)
{
    for (size_t i = 0; i < update.size(); ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if (orders[update[i]].find(update[j]) != orders[update[i]].end())
            {
                return false;
            }
        }
    }
    return true;
}

int solve1(std::string input_path)
{
    int result = 0;

    std::vector<std::pair<int, int>> edges;
    std::vector<std::vector<int>> updates;

    readInput(input_path, edges, updates);

    std::map<int, std::set<int>> orders;

    for (std::pair<int, int> edge : edges)
    {
        if (orders.find(edge.first) == orders.end())
        {
            orders[edge.first];
        }
        orders[edge.first].insert(edge.second);
    }

    for (std::vector<int> update : updates)
    {
        if (validUpdate(orders, update))
        {
            size_t mid = update.size() / 2;
            result += update[mid];
        }
    }

    return result;
}

std::vector<int> correctOrder(std::map<int, std::set<int>> orders, std::vector<int> original)
{
    std::vector<std::pair<int, int>> edges;

    for (size_t i = 0; i < original.size(); ++i)
    {
        for (size_t j = 0; j < original.size(); ++j)
        {
            if (i != j)
            {
                if (orders[original[i]].find(original[j]) != orders[original[i]].end())
                {
                    edges.push_back(std::make_pair(original[i], original[j]));
                }
            }
        }
    }

    std::vector<int> corrected;

    topologicalSort(edges, corrected);

    return corrected;
}

int solve2(std::string input_path)
{
    int result = 0;

    std::vector<std::pair<int, int>> edges;
    std::vector<std::vector<int>> updates;

    readInput(input_path, edges, updates);

    std::map<int, std::set<int>> orders;

    for (std::pair<int, int> edge : edges)
    {
        if (orders.find(edge.first) == orders.end())
        {
            orders[edge.first];
        }
        orders[edge.first].insert(edge.second);
    }

    for (std::vector<int> update : updates)
    {
        if (!validUpdate(orders, update))
        {
            std::vector<int> corrected = correctOrder(orders, update);
            size_t mid = corrected.size() / 2;
            result += corrected[mid];
        }
    }

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

    std::cout << "Day 5 -- Part 1: " << solve1(input_path) << std::endl;
    std::cout << "Day 5 -- Part 2: " << solve2(input_path) << std::endl;
}