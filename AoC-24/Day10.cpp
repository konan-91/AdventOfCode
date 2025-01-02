// Advent Of Code 2024++, Day 1.
// https://adventofcode.com/2024/day/10
// TODO: everything. This week is a work in progress...

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using TopographicMap = std::vector<std::vector<int>>;
using Trailhead = std::pair<int, int>;

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

    return testInput2;
}

std::vector<Trailhead> findTrailheads(const TopographicMap& map) {
    std::vector<Trailhead> trailheads;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 0) {
                trailheads.push_back(std::make_pair(i, j));
            }
        }
    }

    return trailheads;
}

int trailheadScore(const TopographicMap& map, const Trailhead& trailhead) {
    int score = 0;
    // Try to start a DFS in 4 directions (if possible)
    // Same direction may need to be run multiple times if same start has diff ultimate routes
    // for each time a 9 is reached, score++;
    score++;

    return score;
}

int sumTrailScores(const TopographicMap& map) {
    std::vector<Trailhead> trailheads = findTrailheads(map);
    int sum = 0;

    for (Trailhead trailhead : trailheads) {
        sum += trailheadScore(map, trailhead);
    }

    return sum;
}

int main() {
    const auto& map = readFile("AoC-24/input_files/day_10/input.txt");
    const int ans = sumTrailScores(map);

    for (auto row : map) {
        for (const int i : row) {
            std::cout << i;
        }
        std::cout << "\n";
    }

    return ans;
}