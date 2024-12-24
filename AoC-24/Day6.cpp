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
    std::vector<std::vector<char> > lab = readFile(path);
    std::set<std::tuple<int, int>> positionSet;
    std::string direction = "up";

    // find starting position (^)

    // move in (direction)
    // if next pos is at the edge and != "#', add to positionSet and break;
    // else if next pos == "#",
    // else add current position to set and continue...

    return static_cast<int>(positionSet.size());
}

int main() {
    const std::string path = "AoC-24/input_files/day_6/input.txt";
    simulatePatrol(path);
}