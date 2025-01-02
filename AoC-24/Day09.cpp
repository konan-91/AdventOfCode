// Advent Of Code 2024++, Day 9.
// https://adventofcode.com/2024/day/9

#include <fstream>
#include <iostream>
#include <numeric>

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

    return diskMap;
}

List expandDisk(const std::string& path) {
    const auto& diskMap = readFile(path);
    List expandedMap;
    expandedMap.reserve(std::accumulate(diskMap.begin(), diskMap.end(), 0));
    int idNum = 0;

    for (size_t i = 0; i < diskMap.size(); i += 2) {
        // Expand file memory & free space
        expandedMap.insert(expandedMap.end(), diskMap[i], std::vector<int>{idNum});
        expandedMap.insert(expandedMap.end(), diskMap[i + 1], std::vector<int>{});
        ++idNum;
    }
    return expandedMap;
}

List compactDisk(List compactedMap) {
    const int compactedMapSize = compactedMap.size();
    int emptyCount = 0; // Index for terminating while loop & clipping vector
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
    const int defragMapSize = defragmentedMap.size();
    int idNum = defragmentedMap[defragMapSize - 1][0];

    // Two pointers: find file index range & check for sufficient free space
    while (idNum >= 0) {
        int i = 0, j = defragMapSize - 1;
        std::vector<int> fileRange;
        std::vector<int> contiguousSpace;

        // Get index range for file
        while (j > 0) {
            while (defragmentedMap[j].empty()) {
                j--;
            }
            while (!defragmentedMap[j].empty()) {
                if (defragmentedMap[j][0] == idNum) {
                    fileRange.push_back(j);
                }
                j--;
            }

            if (fileRange.size() > 0) {
                break;
            }

            while (!defragmentedMap[j].empty()) {
                j--;
            }
        }

        // Check if contiguous free space matches file size
        bool moveFile = false;
        while (i < fileRange[0]) {
            while (!defragmentedMap[i].empty() && i < fileRange[0]) {
                i++;
            }
            while (defragmentedMap[i].empty() && i < fileRange[0]) {
                contiguousSpace.push_back(i);
                i++;
            }

            if (contiguousSpace.size() >= fileRange.size()) {
                moveFile = true;
                break;
            }
            contiguousSpace = {};
        }

        // If there is contiguous free space available, move the file
        if (moveFile) {
            for (int i = 0; i < fileRange.size(); i++) {
                defragmentedMap[contiguousSpace[i]] = {idNum};
            }
            for (int j = 0; j < fileRange.size(); j++) {
                defragmentedMap[fileRange[j]] = {};
            }
        }
        idNum --;
    }

    return defragmentedMap;
}

std::pair<size_t, size_t> checkSum(const std::string& path) {
    const List expanded = expandDisk(path);
    const List compacted = compactDisk(expanded);
    const List defragmented = defragmentDisk(expanded);

    size_t compactedCheckSum = 0;
    for (int i = 0; i < compacted.size(); i++) {
        if (compacted[i].empty()) {
            continue;
        }
        compactedCheckSum += i * compacted[i][0];
    }

    size_t defragmentedCheckSum = 0;
    for (int i = 0; i < defragmented.size(); i++) {
        if (defragmented[i].empty()) {
            continue;
        }
        defragmentedCheckSum += i * defragmented[i][0];
    }

    return std::make_pair(compactedCheckSum, defragmentedCheckSum);
}

int main() {
    auto [compactedCheckSum, defragmentedCheckSum] = checkSum("AoC-24/input_files/day_9/input.txt");
    std::cout << "Compacted Checksum: " << compactedCheckSum << "\n";
    std::cout << "Defragmented Checksum: " << defragmentedCheckSum << "\n";
}
