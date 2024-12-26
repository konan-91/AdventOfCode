// Advent Of Code 2024++, Day 6.
// ps you can probably make lab into an object which contains a matrix + yMax + xMax and that will cut down variables...
// pps you can use enums position and then use a list [x, y, direction] to reduce complications

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
                if (grid[i][j] == '^') return {i, j};
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

// Change the actual lab value as it's faster than creating a copy - just be sure to change it back when you're finished.
int countLoops(Lab& lab, std::set<std::array<int, 3>>& uniquePos) {
    int loopCount = 0;

    // REMOVE lab.startPos from uniquePos before starting, or else you may create a # on the starting position!
    // uniquePos.erase(lab.startPos);

    // Check every uniquePos for loops (start positions where



    return loopCount;
}

std::pair<int, int> simulatePatrol(Lab& lab) {
    std::set<std::array<int, 3>> uniquePosDir; // 3rs val is so we can tell what the orientation was at each position!
    std::set<std::array<int, 2>> uniquePos;
    std::array<int, 2> currentPos = lab.startPos;
    Direction dir = UP;

    while (currentPos[0] > 0 && currentPos[0] < lab.yMax && currentPos[1] > 0 && currentPos[1] < lab.xMax) {
        uniquePos.insert({currentPos[0], currentPos[1]});
        uniquePosDir.insert({currentPos[0], currentPos[1], dir});

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
    }

    return std::make_pair(uniquePos.size() + 1, countLoops(lab, uniquePos));
}

int main() {
    Lab lab{readFile("AoC-24/input_files/day_6/input.txt")};
    auto [positionCount, loopCount] = simulatePatrol(lab);

    std::cout << "Unique Positions: " << positionCount << std::endl;
    std::cout << "Potential Loops: " << loopCount << std::endl;
}
