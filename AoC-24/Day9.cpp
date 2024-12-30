// Advent Of Code 2024++, Day 9.
// https://adventofcode.com/2024/day/9

// This week is a work in progress!

#include <fstream>
#include <iostream>

using List = std::vector<std::vector<int>>;

std::vector<int> readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return {};
    }

    std::string str;
    std::getline(file, str);
    std::vector<int> diskMap;
    for (const char c : str) {
        diskMap.push_back(c - '0');
    }

    std::vector inputTest = {2, 3, 3, 3, 1, 3, 3, 1, 2, 1, 4, 1, 4, 1, 3, 1, 4, 0, 2};
    return inputTest;
}

List expandDisk(const std::string& path) {
    const auto diskMap = readFile(path);
    const int diskMapSize = diskMap.size();
    int idNum = 0;
    List expandedMap;
    //expandedMap.reserve(diskMapSize * 2);

    for (int i = 0; i < diskMapSize; i += 2) {
        // Expand file memory.
        for (int j = 0; j < diskMap[i]; j++) {
            expandedMap.push_back({idNum});

        }
        // Expand free space.
        for (int j = 0; j < diskMap[i + 1]; j++) {
            expandedMap.push_back({});
        }

        idNum++;
    }

    // PRINTING -- TEST
    std::cout << "\nExpanded Map\n";
    for (auto item : expandedMap) {
        if (item.empty()) {
            std::cout << ".";
            continue;
        }

        for (const int i : item) {
            std::cout << i;
        }
    }
    std::cout << "\n";

    return expandedMap;
}

List compactDisk(const std::string& path) {
    List compactedMap = expandDisk(path);
    const int compactedMapSize = compactedMap.size();

    // Get emptyCount - number of '.' - so that we know when to stop the loop!
    int emptyCount = 0;
    for (auto item : compactedMap) {
        if (item.empty()) {
            emptyCount++;
        }
    }
    int clipIdx = compactedMapSize - emptyCount;

    std::cout << "\nExpandedMapSize: " << compactedMapSize << "\n";
    std::cout << "emptyCount: " << emptyCount << "\n";
    std::cout << "ClipIdx: " << clipIdx << "\n";

    // Two pointers: one for free space, another for the memory item to move
    int i = 0, j = compactedMapSize - 1;
    while (emptyCount > 0) {
        // Move i to empty space
        while (!compactedMap[i].empty()) {
            i++;
        }

        // Move j to memory item
        while (compactedMap[j].empty()) {
            j--;
        }

        // Move memory item to empty space
        compactedMap[i] = compactedMap[j];

        emptyCount--;
        i++;
        j--;
    }

    // Clip vector
    compactedMap.erase(compactedMap.begin() + clipIdx, compactedMap.end());

    return compactedMap;
}

size_t checkSum(const std::string& path) {
    /*
    size_t checksum = 0;
    std::vector<char> compacted = compactDisk(path);

    return checksum;
    */
}

int main() {
    auto ans = compactDisk("AoC-24/input_files/day_9/input.txt");

    // PRINTING -- TEST
    std::cout << "\nCompact Map\n";
    for (auto item : ans) {
        if (item.empty()) {
            std::cout << ".";
            continue;
        }

        for (const int i : item) {
            std::cout << i;
        }
    }
    std::cout << "\n";
}
