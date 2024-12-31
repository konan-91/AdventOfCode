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
    expandedMap.reserve(diskMapSize * 2);

    for (int i = 0; i < diskMapSize; i += 2) {
        // Expand file memory.
        for (int j = 0; j < diskMap[i]; j++) {
            expandedMap.push_back({idNum});

        }
        // Expand free space.
        for (int j = 0; j < diskMap[i + 1]; j++) {
            expandedMap.emplace_back();
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

List compactDisk(List compactedMap) {
    const int compactedMapSize = compactedMap.size();

    int emptyCount = 0; // Needed for ending while loop & clipping vector
    for (auto item : compactedMap) {
        if (item.empty()) {
            emptyCount++;
        }
    }
    const int clipIdx = compactedMapSize - emptyCount;

    // Two pointers: one for free space, another for the memory item to move
    int i = 0, j = compactedMapSize - 1;
    while (emptyCount > 0) {
        while (!compactedMap[i].empty()) {
            i++;
        }
        while (compactedMap[j].empty()) {
            j--;
        }
        compactedMap[i] = compactedMap[j];

        emptyCount--;
        i++;
        j--;
    }
    compactedMap.erase(compactedMap.begin() + clipIdx, compactedMap.end());

    return compactedMap;
}

List defragmentDisk(List defragmentedMap) {
    /*
    00...111...2...333.44.5555.6666.777.888899
    0099.111...2...333.44.5555.6666.777.8888..
    0099.1117772...333.44.5555.6666.....8888..
    0099.111777244.333....5555.6666.....8888..
    00992111777.44.333....5555.6666.....8888..
    // Two pointers again:
        // Get file range with j, get cont. space range with i, move j -> i
        // If there is no space large enough, do not move it file        */

    const int defragMapSize = defragmentedMap.size();
    int idNum = defragmentedMap[defragMapSize - 1][0];

    while (idNum >= 0) {
        int i = 0, j = defragMapSize - 1;
        std::vector<int> fileRange;
        std::vector<int> contiguousSpace;

        // Get file range
        while (defragmentedMap[j][0] != idNum) {
            j--;
        }
        while (defragmentedMap[j][0] == idNum) {
            fileRange.push_back(j);
            j--;
        }

        // Check if contiguous free space matches file size
        bool moveFile = false;
        while (i < defragMapSize) {
            while (!defragmentedMap[i].empty()) { // This may cause an infinite loop near the end - be careful!!
                i++;
            }
            while (defragmentedMap[i].empty()) { // This is EVEN MORE likely to cause an infinite loop!! Possibly add while i < defragMapSize to both.
                contiguousSpace.push_back(i);
            }

            if (contiguousSpace.size() >= fileRange.size()) {
                // Set flag to move file and break;
                moveFile = true;
                break;
            }
        }

        // If there is contiguous free space available, move the file! also set origin pos to '.'
        if (moveFile) {
            for (int i = 0; i < contiguousSpace.size() - 1; i++) {
                defragmentedMap[contiguousSpace[i]][0] = idNum; // Set empty space to idNum
            }
            for (int i = 0; i < fileRange.size() - 1; i++) {
                defragmentedMap[fileRange[i]] = {}; // Set idNums to empty space
            }
        }

        idNum --;
    }

    // PRINT DEFRAG MAP!


    return defragmentedMap;
}

std::pair<size_t, size_t> checkSum(const std::string& path) {
    const List expanded = expandDisk(path);
    const List compacted = compactDisk(expanded);
    const List defragmented = defragmentDisk(expanded);

    size_t checksum = 0;
    for (int i = 0; i < compacted.size(); i++) {
        if (compacted[i].empty()) {
            continue;
        }
        checksum += i * compacted[i][0];
    }

    return std::make_pair(checksum, checksum);
}

int main() {
    auto [compactedCheckSum, defragmentedCheckSum] = checkSum("AoC-24/input_files/day_9/input.txt");
    std::cout << "\nCompacted Checksum: " << compactedCheckSum << "\n";
    std::cout << "Defragmented Checksum: " << defragmentedCheckSum << "\n";
}
