// Advent Of Code 2024++, Day 10.
// https://adventofcode.com/2024/day/10

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using TopographicMap = std::vector<std::vector<int>>;
using Position = std::pair<int, int>;
using PositionCache = std::map<Position, bool>;

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

    return map;
}

std::vector<Position> findTrailheads(const TopographicMap& map, const int& target) {
    std::vector<Position> trailheads;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == target) {
                trailheads.emplace_back(i, j);
            }
        }
    }

    return trailheads;
}


// Using DFS to calculate how many peaks are accessible from each trailhead while caching traversed positions
void trailheadScore(const TopographicMap& map, const Position &pos, PositionCache& visited, int& score) {
    if (map[pos.first][pos.second] == 9) {
        score++;
    }
    visited[pos] = true;

    const std::vector<Position> neighbours = {{pos.first - 1, pos.second}, {pos.first + 1, pos.second},
                                              {pos.first, pos.second - 1}, {pos.first, pos.second + 1}};
    for (Position neighbour : neighbours) {
        // Neighbour is in bounds
        if (neighbour.first < 0 || neighbour.first >= map.size() ||
            neighbour.second < 0 || neighbour.second >= map.size()) {
                continue;
            }

        // Neighbour has not already been visited
        if (visited.contains(neighbour)) {
            continue;
        }

        // Neighbour's value is +1 from current position
        if (map[neighbour.first][neighbour.second] - map[pos.first][pos.second] != 1) {
            continue;
        }

        // If valid, call self and explore neighbour(s)
        trailheadScore(map, neighbour, visited, score);
    }
}

// Passing by value instead of by reference to calculates the total no. paths     ↓
void trailheadRating(const TopographicMap& map, const Position &pos, PositionCache visited, int& rating) {
    if (map[pos.first][pos.second] == 9) {
        rating++;
    }
    visited[pos] = true;

    const std::vector<Position> neighbours = {{pos.first - 1, pos.second}, {pos.first + 1, pos.second},
                                              {pos.first, pos.second - 1}, {pos.first, pos.second + 1}};
    for (Position neighbour : neighbours) {
        if (neighbour.first < 0 || neighbour.first >= static_cast<int>(map.size()) ||
            neighbour.second < 0 || neighbour.second >= static_cast<int>(map[0].size()) ||
            map[neighbour.first][neighbour.second] - map[pos.first][pos.second] != 1 ||
            visited.contains(neighbour)) {
            continue;
            }

        trailheadRating(map, neighbour, visited, rating);
    }
}

std::pair<int, int> sumTrailScores(const TopographicMap& map) {
    const std::vector<Position> trailheads = findTrailheads(map, 0);
    int totalScore = 0;
    int totalRating = 0;

    for (const Position& trailhead : trailheads) {
        PositionCache visited;
        trailheadScore(map, trailhead, visited, totalScore);
    }

    for (const Position& trailhead : trailheads) {
        const PositionCache visited;
        trailheadRating(map, trailhead, visited, totalRating);
    }

    return std::make_pair(totalScore, totalRating);
}

int main() {
    const auto& map = readFile("AoC-24/input_files/day_10/input.txt");
    auto [score, rating] = sumTrailScores(map);
    std::cout << "Sum of trailhead scores:  " << score << "\n";
    std::cout << "Sum of trailhead ratings: " << rating << "\n";
}