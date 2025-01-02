// Advent Of Code 2024++, Day 1.
// https://adventofcode.com/2024/day/10
// TODO: everything. This week is a work in progress...

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using TopographicMap = std::vector<std::vector<int>>;
using Position = std::pair<int, int>;

TopographicMap readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return {};
    }

    std::string str;
    TopographicMap map;

    while (std::getline(file, str)) {
        std::istringstream stream(str);
        std::vector<int> row;

        char ch;
        while (stream >> ch) {
            row.push_back(ch - '0');
        }
        map.push_back(row);
    }

    TopographicMap testInput = {
        {0, 1, 2, 3},
        {1, 2, 3, 4},
        {8, 7, 6, 5},
        {9, 8, 7, 6}
    };

    TopographicMap testInput2 = {
        {8, 9, 0, 1, 0, 1, 2, 3},
        {7, 8, 1, 2, 1, 8, 7, 4},
        {8, 7, 4, 3, 0, 9, 6, 5},
        {9, 6, 5, 4, 9, 8, 7, 4},
        {4, 5, 6, 7, 8, 9, 0, 3},
        {3, 2, 0, 1, 9, 0, 1, 2},
        {0, 1, 3, 2, 9, 8, 0, 1},
        {1, 0, 4, 5, 6, 7, 3, 2}
    };

    return testInput;
}

std::vector<Position> findTrailheads(const TopographicMap& map) {
    std::vector<Position> trailheads;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 0) {
                trailheads.emplace_back(i, j);
            }
        }
    }

    return trailheads;
}

void trailheadScore(const TopographicMap& map, const Position pos, std::map<Position, bool>& visited, int& score) {

    // Result case: if 9 encountered
    if (map[pos.first][pos.second] == 9) {
        //std::cout << "9 FOUND! incrementing score\n";
        score += 1; // no need to return as no other positions are +1 from 9
    }
    visited[pos] = true;

    // Call self on all 4 neighbours, so long as they are in bounds and have no already been visited
    const std::vector<Position> neighbours = {{pos.first - 1, pos.second}, {pos.first + 1, pos.second},
                                              {pos.first, pos.second - 1}, {pos.first, pos.second + 1}};

    for (Position neighbour : neighbours) {
        //std::cout << "Trying neighbour: " << neighbour.first << ", " << neighbour.second << "\n";
        // Neighbour is in bounds
        if (neighbour.first < 0 || neighbour.first >= map.size() ||
            neighbour.second < 0 || neighbour.second >= map.size()) {
                //std::cout << "not in bounds\n";
                continue;
            }

        // Neighbour has not already been visited
        if (visited.contains(neighbour)) {
            //std::cout << "already visited\n";
            continue;
        }

        // Neighbour is +1 from current position
        if (map[neighbour.first][neighbour.second] - map[pos.first][pos.second] != 1) {
            //std::cout << "not +1 from currentPos\n";
            continue;
        }

        // If valid, call self and explore neighbour
        //std::cout << "Valid! recursing\n\n";
        trailheadScore(map, neighbour, visited, score);
    }

    //std::cout << "DONE!\n\n";
}

void trailheadRating() {

}

int sumTrailScores(const TopographicMap& map) {
    const std::vector<Position> trailheads = findTrailheads(map);
    int sum = 0;

    for (const Position& trailhead : trailheads) {
        std::map<Position, bool> visited;
        trailheadScore(map, trailhead, visited, sum);
    }

    return sum;
}

int main() {
    const auto& map = readFile("AoC-24/input_files/day_10/input.txt");
    const int ans = sumTrailScores(map);
    std::cout << "Answer: " << ans << "\n";

    for (auto row : map) {
        for (const int i : row) {
            std::cout << i;
        }
        std::cout << "\n";
    }

    return ans;
}