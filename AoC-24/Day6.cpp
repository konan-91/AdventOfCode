// Advent Of Code 2024++, Day 6.

#include <fstream>
#include <iostream>
#include <set>

enum Direction {
    UP,     // 0
    RIGHT,  // 1
    DOWN,   // 2
    LEFT    // 3
};

struct Lab {
    std::vector<std::vector<char>> grid;
    int yMax;
    int xMax;
    std::array<int, 2> startPos{};

    explicit Lab(const std::vector<std::vector<char>>& input)
        : grid(input)
        , yMax(static_cast<int>(input.size() - 1))
        , xMax(static_cast<int>(input.empty() ? 0 : input[0].size() - 1))
    {
        startPos = findStartPosition();
    }

private:
    [[nodiscard]] std::array<int, 2> findStartPosition() const {
        for (int i = 0; i < yMax; i++) {
            for (int j = 0; j < xMax; j++) {
                if (grid[i][j] == '^') {return {i, j};}
            }
        }

        return {0, 0};
    }
};

Lab readFile(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<char>> grid;
    grid.reserve(130);

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return Lab(grid);  // Return empty Lab
    }

    std::string str;
    while (getline(file, str)) {
        std::vector<char> line;
        line.reserve(130);
        for (const char& c : str) {
            line.push_back(c);
        }
        grid.push_back(line);
    }

    return Lab(grid);
}

int countLoops(Lab& lab, const std::set<std::array<int, 2>>& uniquePos) {
    int loopCount = 0;

    for (std::array<int, 2> pos : uniquePos) {
        auto posBackup = pos;
        lab.grid[pos[0]][pos[1]] = '#';

        // Simulate traversal - if traversal spot has already been traversed with same direction, loop is present.
        std::array<int, 3> guard = {lab.startPos[0], lab.startPos[1], UP};
        std::set<std::array<int, 3>> traversedSet;

        while (guard[0] > 0 && guard[0] < lab.yMax && guard[1] > 0 && guard[1] < lab.xMax) {
            if (traversedSet.contains(guard)) {
                loopCount++;
                break;
            }
            traversedSet.insert(guard);

            if (guard[2] == UP) {
                if (lab.grid[guard[0] - 1][guard[1]] == '#') {
                    guard[2] = RIGHT;
                } else {
                    guard[0]--;
                }
            } else if (guard[2] == RIGHT) {
                if (lab.grid[guard[0]][guard[1] + 1] == '#') {
                    guard[2] = DOWN;
                } else {
                    guard[1]++;
                }
            } else if (guard[2] == DOWN) {
                if (lab.grid[guard[0] + 1][guard[1]] == '#') {
                    guard[2] = LEFT;
                } else {
                    guard[0]++;
                }
            } else if (guard[2] == LEFT) {
                if (lab.grid[guard[0]][guard[1] - 1] == '#') {
                    guard[2] = UP;
                } else {
                    guard[1]--;
                }
            }
        }

        lab.grid[posBackup[0]][posBackup[1]] = '.';
    }

    return loopCount;
}

std::pair<int, int> simulatePatrol(Lab& lab) {
    std::array<int, 2> currentPos = lab.startPos;
    std::set<std::array<int, 2>> uniquePos;
    Direction dir = UP;

    while (currentPos[0] > 0 && currentPos[0] < lab.yMax && currentPos[1] > 0 && currentPos[1] < lab.xMax) {

        if (dir == UP) {
           if (lab.grid[currentPos[0] - 1][currentPos[1]] == '#') {
               dir = RIGHT;
           } else {
               currentPos[0]--;
           }
        } else if (dir == RIGHT) {
            if (lab.grid[currentPos[0]][currentPos[1] + 1] == '#') {
                dir = DOWN;
            } else {
                currentPos[1]++;
            }
        } else if (dir == DOWN) {
            if (lab.grid[currentPos[0] + 1][currentPos[1]] == '#') {
                dir = LEFT;
            } else {
                currentPos[0]++;
            }
        } else if (dir == LEFT) {
            if (lab.grid[currentPos[0]][currentPos[1] - 1] == '#') {
                dir = UP;
            } else {
                currentPos[1]--;
            }
        }

        if (lab.grid[currentPos[0]][currentPos[1]] != '^') {
            uniquePos.insert({currentPos[0], currentPos[1]});
        }
    }

    return std::make_pair(uniquePos.size() + 1, countLoops(lab, uniquePos));
}

int main() {
    Lab lab{readFile("AoC-24/input_files/day_6/input.txt")};
    auto [positionCount, loopCount] = simulatePatrol(lab);

    std::cout << "Unique Positions: " << positionCount << std::endl;
    std::cout << "Potential Loops: " << loopCount << std::endl;
}
