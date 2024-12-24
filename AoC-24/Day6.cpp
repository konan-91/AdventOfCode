//
// Advent Of Code 2024++, Day 6.
//

#include <fstream>
#include <iostream>
#include <set>

std::vector<std::vector<char>> readFile(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<char>> lab;
    lab.reserve(130);

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return lab;
    }

    std::string str;
    while (getline(file, str)) {
        std::vector<char> line;
        line.reserve(130);
        for (const char& c : str) {
            line.push_back(c);
        }

        lab.push_back(line);
    }

    return lab;
}

int simulatePatrol(const std::string& path) {
    const std::vector<std::vector<char> > lab = readFile(path);
    std::set<std::array<int, 2>> positionSet;
    std::array currentPosition = {0, 0};
    std::string direction = "north";

    for (int i = 0; i < lab.size(); i++) {
        for (int j = 0; j < lab[0].size(); j++) {
            if (lab[i][j] == '^') {
        }
    }

    const int yMax = static_cast<int>(lab.size() - 1);
    const int xMax = static_cast<int>(lab[0].size() - 1);

    // Simulate traversal, counting unique positions visited
    while (currentPosition[0] > 0 && currentPosition[0] < yMax && currentPosition[1] > 0 && currentPosition[1] < xMax) {
        positionSet.insert(currentPosition);

        if (direction == "north") {
            if (lab[currentPosition[0] - 1][currentPosition[1]] == '#') {
                direction = "east";
            } else {
                currentPosition[0]--;
            }
        } else if (direction == "east") {
            if (lab[currentPosition[0]][currentPosition[1] + 1] == '#') {
                direction = "south";
            } else {
                currentPosition[1]++;
            }
        } else if (direction == "south") {
            if (lab[currentPosition[0] + 1][currentPosition[1]] == '#') {
                direction = "west";
            } else {
                currentPosition[0]++;
            }
        } else if (direction == "west") {
            if (lab[currentPosition[0]][currentPosition[1] - 1] == '#') {
                direction = "north";
            } else {
                currentPosition[1]--;
            }
        }
    }

    return static_cast<int>(positionSet.size()) + 1;
}

int main() {
    const std::string path = "AoC-24/input_files/day_6/input.txt";
    std::cout << simulatePatrol(path) << std::endl;
}
