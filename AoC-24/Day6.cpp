// Advent Of Code 2024++, Day 6.

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

bool loopCheck(const auto& target, auto currentPosition, auto& loopCheckSet, const auto& lab, const int& yMax, const int& xMax) {
    while (currentPosition.first[0] > 0 && currentPosition.first[0] < yMax && currentPosition.first[1] > 0 && currentPosition.first[1] < xMax) {

        if (currentPosition == target) {
            return true;
        }

        /*
        if (loopCheckSet.contains(currentPosition)) {
            return false;
        }
        loopCheckSet.insert(currentPosition);
        */

        if (currentPosition.second == "north") {
            if (lab[currentPosition.first[0] - 1][currentPosition.first[1]] == '#') {
                currentPosition.second = "east";
            } else {
                --currentPosition.first[0];
            }
        }

        else if (currentPosition.second == "east") {
            if (lab[currentPosition.first[0]][currentPosition.first[1] + 1] == '#') {
                currentPosition.second = "south";
            } else {
                ++currentPosition.first[1];
            }
        }

        else if (currentPosition.second == "south") {
            if (lab[currentPosition.first[0] + 1][currentPosition.first[1]] == '#') {
                currentPosition.second = "west";
            } else {
                ++currentPosition.first[0];
            }
        }

        else if (currentPosition.second == "west") {
            if (lab[currentPosition.first[0]][currentPosition.first[1] - 1] == '#') {
                currentPosition.second = "north";
            } else {
                --currentPosition.first[1];
            }
        }
    }

    return false;
}

int simulatePatrol(const std::string& path) {
    const std::vector<std::vector<char> > lab = readFile(path);
/*
    const std::vector<std::vector<char> > lab = {
        {'.','#','.','.','.','.'},
        {'.','0','.','0','.','#'},
        {'#','.','.','#','.','.'},
        {'.','.','#','.','.','.'},
        {'0','^','.','.','.','#'},
        {'.','.','.','.','#','.'},
    };

    const std::vector<std::vector<char> > lab = {
        {'.','.','.','.','#','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','#'},
        {'.','.','.','.','.','.','.','.','.','.'},
        {'.','.','#','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','#','.','.'},
        {'.','.','.','.','.','.','.','.','.','.'},
        {'.','#','.','0','^','.','.','.','.','.'},
        {'.','.','.','.','.','.','X','X','#','.'},
        {'#','X','.','X','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','#','X','.','.'}
    };
    */
    int step = 0;
    // DON'T CALL THE FUCKING FUNCTION IF WHERE YOU WOULD BE PLACING THE # IS A ^. LOGIC NEEDS TO GO IN simulatePatrol() !!!!!!!!!!!!!!!!!!
    std::set<std::pair<std::array<int, 2>, std::string>> loopCheckSet;
    std::set<std::array<int, 2>> positionSet;
    std::array currentPosition = {0, 0};
    std::string direction = "north";
    int loopCount = 0;

    for (int i = 0; i < lab.size(); i++) {
        for (int j = 0; j < lab[0].size(); j++) {
            if (lab[i][j] == '^') {
                currentPosition = {i, j};
            }
        }
    }

    const int yMax = static_cast<int>(lab.size() - 1);
    const int xMax = static_cast<int>(lab[0].size() - 1);

    // Simulate traversal, counting unique positions visited
    while (currentPosition[0] > 0 && currentPosition[0] < yMax && currentPosition[1] > 0 && currentPosition[1] < xMax) {
        positionSet.insert(currentPosition);
        loopCheckSet.insert({currentPosition, direction});

        if (direction == "north") {
            if (lab[currentPosition[0] - 1][currentPosition[1]] == '#') {
                direction = "east";
            } else {
                if (lab[currentPosition[0] - 1][currentPosition[1]] != '^') {
                    if (loopCheck(std::make_pair(currentPosition, direction), std::make_pair(currentPosition, "east"), loopCheckSet, lab, yMax, xMax)) {
                        loopCount++;
                    }
                }

                currentPosition[0]--;
            }
        }

        else if (direction == "east") {
            if (lab[currentPosition[0]][currentPosition[1] + 1] == '#') {
                direction = "south";
            } else {
                if (lab[currentPosition[0]][currentPosition[1] + 1] != '^') {
                    if (loopCheck(std::make_pair(currentPosition, direction), std::make_pair(currentPosition, "south"), loopCheckSet, lab, yMax, xMax)) {
                        loopCount++;
                    }
                }

                currentPosition[1]++;
            }
        }

        else if (direction == "south") {
            if (lab[currentPosition[0] + 1][currentPosition[1]] == '#') {
                direction = "west";
            } else {
                if (lab[currentPosition[0] + 1][currentPosition[1]] != '^') {
                    if (loopCheck(std::make_pair(currentPosition, direction), std::make_pair(currentPosition, "west"), loopCheckSet, lab, yMax, xMax)) {
                        loopCount++;
                    }
                }

                currentPosition[0]++;
            }
       }

        else if (direction == "west") {
            if (lab[currentPosition[0]][currentPosition[1] - 1] == '#') {
                direction = "north";
            } else {
                if (lab[currentPosition[0]][currentPosition[1] - 1] != '^') {
                    if (loopCheck(std::make_pair(currentPosition, direction), std::make_pair(currentPosition, "north"), loopCheckSet, lab, yMax, xMax)) {
                        loopCount++;
                    }
                }

                currentPosition[1]--;
            }
        }

        step++;
        std::cout << step << "\n";
    }

    std::cout << loopCount << std::endl;
    return static_cast<int>(positionSet.size()) + 1;
}

int main() {
    const std::string path = "AoC-24/input_files/day_6/input.txt";
    std::cout << simulatePatrol(path) << std::endl;
}
