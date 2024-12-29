// Advent Of Code 2024++, Day 8.
// https://adventofcode.com/2024/day/8

#include <fstream>
#include <iostream>
#include <set>

std::vector<std::vector<char>> readFile(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<char>> city;
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

    std::vector<std::vector<char>> cityTest = {
        {'.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','0','.','.','.'},
        {'.','.','.','.','.','0','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','0','.','.','.','.'},
        {'.','.','.','.','0','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','A','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','A','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','A','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.'}
    };

    return cityTest;
}

std::set<char> uniqueChars(const std::vector<std::vector<char>>& city) {
    std::set<char> charSet;
    for (std::vector row : city) {
        for (char c : row) {
            if (c != '.') {
                charSet.insert(c);
            }
        }
    }

    return charSet;
}

std::set<std::pair<int, int>> collectAntinodes(const std::vector<std::vector<char>>& city, const char& target) {
    std::set<std::pair<int, int>> antinodeSet;
    std::vector<std::pair<int, int>> antennaPos;

    // Step 1: Iterate through city and find coordinates of every 'char'.
    for (int i = 0; i < city.size(); i++) {
        for (int j = 0; j < city[0].size(); j++) {
            if (city[i][j] == target) {
                antennaPos.push_back(std::make_pair(i, j));
            }
        }
    }

    // Step 2: Iterate through antenna list and get distance to every other list
    //         Add antinode to antinodeSet at inverse of distance if in bounds
    if (antennaPos.size() > 1) {
        std::cout << "\n\nAntennaPos.size() == " << antennaPos.size() << "\n";

        for (int i = 0; i < antennaPos.size() - 1; i++) {
            for (int j = i + 1; j < antennaPos.size(); j++) {

                std::cout << "\nFinding distance between " << antennaPos[i].first << ", " << antennaPos[i].second << " and ";
                std::cout << antennaPos[j].first << ", " << antennaPos[j].second << " -- " << city[antennaPos[i].first][antennaPos[i].second] <<"\n";

                int y_dist = antennaPos[j].first - antennaPos[i].first;
                int x_dist = antennaPos[j].second - antennaPos[i].second;
                std::cout << "Distance == (" << y_dist << ", " << x_dist << ")\n";

                int antinode_y = antennaPos[i].first - y_dist;
                int antinode_x = antennaPos[i].second - x_dist;
                std::cout << "Antinode position: (" << antinode_y << ", " << antinode_x << ")\n";

                if (antinode_y >= 0 && antinode_y < city.size() && antinode_x >= 0 && antinode_x < city[0].size()) {
                    antinodeSet.insert(std::make_pair(antinode_y, antinode_x));
                    std::cout << "Antinode1 added!\n";
                } else {
                    std::cout << "Antinode1 NOT IN BOUNDS!\n";
                }

                antinode_y = antennaPos[j].first + y_dist;
                antinode_x = antennaPos[j].second + x_dist;
                std::cout << "2nd antinode position: (" << antinode_y << ", " << antinode_x << ")\n";

                if (antinode_y >= 0 && antinode_y < city.size() && antinode_x >= 0 && antinode_x < city[0].size()) {
                    antinodeSet.insert(std::make_pair(antinode_y, antinode_x));
                    std::cout << "Antinode2 added!\n";
                } else {
                    std::cout << "Antinode2 NOT IN BOUNDS!\n";
                }
            }
        }
    }
    std::cout << "TOTAL UNIQUE ANTINODES FOR " << target << ": " << antinodeSet.size() << "\n";
    return antinodeSet;
}

int main() {
    std::vector<std::vector<char>> city = readFile("AoC-24/input_files/day_8/input.txt");
    std::set<std::pair<int, int>> antinodeSet;
    std::set<char> charSet = uniqueChars(city);

    for (char c : charSet) {
        auto result = collectAntinodes(city, c);
        antinodeSet.insert(result.begin(), result.end());
    }
    std::cout << "\n" << antinodeSet.size() << "\n";
}