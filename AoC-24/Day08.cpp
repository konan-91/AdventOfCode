// Advent Of Code 2024++, Day 8.
// https://adventofcode.com/2024/day/8

#include <fstream>
#include <iostream>
#include <set>

using Grid = std::vector<std::vector<char>>;
using Position = std::pair<int, int>;

Grid readFile(const std::string& path) {
    std::ifstream file(path);
    Grid city;
    city.reserve(50);

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return city;
    }

    std::string str;
    while (getline(file, str)) {
        std::vector<char> line;
        line.reserve(130);
        for (const char& c : str) {
            line.push_back(c);
        }
        city.push_back(line);
    }

    return city;
}

std::set<char> uniqueChars(const Grid& city) {
    std::set<char> charSet;
    for (const auto& row : city) {
        for (const auto& c : row) {
            if (c != '.') {
                charSet.insert(c);
            }
        }
    }

    return charSet;
}

std::vector<Position> antennaPositions(const Grid& city, const char& target) {
    std::vector<Position> antennaPos;
    for (int i = 0; i < city.size(); i++) {
        for (int j = 0; j < city[0].size(); j++) {
            if (city[i][j] == target) {
                antennaPos.emplace_back(i, j);
            }
        }
    }

    return antennaPos;
}

bool isInBounds(int y, int x, const Grid& city) {
    return y >= 0 && y < city.size() && x >= 0 && x < city[0].size();
}

std::set<Position> collectAntinodes(const Grid& city, const char& target) {
    const std::vector<Position> antennaPos = antennaPositions(city, target);
    std::set<Position> antinodeSet;

    // Finding a pair of antinodes for each antenna combination
    if (antennaPos.size() > 1) {
        for (int i = 0; i < antennaPos.size() - 1; i++) {
            for (int j = i + 1; j < antennaPos.size(); j++) {
                const int y_dist = antennaPos[j].first - antennaPos[i].first;
                const int x_dist = antennaPos[j].second - antennaPos[i].second;

                int antinode_y = antennaPos[i].first - y_dist;
                int antinode_x = antennaPos[i].second - x_dist;
                if (isInBounds(antinode_y, antinode_x, city)) {
                    antinodeSet.emplace(antinode_y, antinode_x);
                }

                antinode_y = antennaPos[j].first + y_dist;
                antinode_x = antennaPos[j].second + x_dist;
                if (isInBounds(antinode_y, antinode_x, city)) {
                    antinodeSet.emplace(antinode_y, antinode_x);
                }
            }
        }
    }

    return antinodeSet;
}

std::set<Position> collectHarmonicAntinodes(const Grid& city, const char& target) {
    std::vector<Position> antennaPos = antennaPositions(city, target);
    std::set<Position> antinodeSet(antennaPos.begin(), antennaPos.end());

    if (antennaPos.size() > 1) {
        // Calculating antinodes for each combination until out of bounds
        for (int i = 0; i < antennaPos.size() - 1; i++) {
            for (int j = i + 1; j < antennaPos.size(); j++) {
                const int y_dist = antennaPos[j].first - antennaPos[i].first;
                const int x_dist = antennaPos[j].second - antennaPos[i].second;

                int antinode_y = antennaPos[i].first - y_dist;
                int antinode_x = antennaPos[i].second - x_dist;
                while (isInBounds(antinode_y, antinode_x, city)) {
                    antinodeSet.emplace(antinode_y, antinode_x);

                    antinode_y -= y_dist;
                    antinode_x -= x_dist;
                }

                antinode_y = antennaPos[j].first + y_dist;
                antinode_x = antennaPos[j].second + x_dist;
                while (isInBounds(antinode_y, antinode_x, city)) {
                    antinodeSet.emplace(antinode_y, antinode_x);

                    antinode_y += y_dist;
                    antinode_x += x_dist;
                }
            }
        }
    }

    return antinodeSet;
}

int main() {
    const Grid city = readFile("AoC-24/input_files/day_08/input.txt");
    const std::set<char> charSet = uniqueChars(city);
    std::set<Position> antinodeSet;

    for (const char& c : charSet) {
        auto result = collectAntinodes(city, c);
        antinodeSet.insert(result.begin(), result.end());
    }
    std::cout << "Unique positions containing antinodes: " << antinodeSet.size() << "\n";

    for (const char& c : charSet) {
        auto result = collectHarmonicAntinodes(city, c);
        antinodeSet.insert(result.begin(), result.end());
    }
    std::cout << "Using resonant harmonics ruleset: " << antinodeSet.size() << "\n";
}
