// Advent Of Code 2024++, Day 9.
// https://adventofcode.com/2024/day/9

// This week is a work in progress!
// TODO: Finish part 1. Fix fileID - breaks when >9. Convert to array of array of ints, therefore ID can be > 9.
// TODO: Possibly rewrite compactDisk function.

#include <fstream>
#include <iostream>

std::vector<char> readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return {};
    }

    std::string str;
    std::getline(file, str);
    std::vector input(str.begin(), str.end());

    std::vector inputTest = {'2', '3', '3', '3', '1', '3', '3', '1', '2', '1', '4', '1', '4', '1', '3', '1', '4', '0', '2'};
    return input;
}

std::vector<char> expandDisk(const std::vector<char>& input) {
    std::vector<char> expanded;
    expanded.reserve(input.size() * 2);
    int idNum = 0;

    for (int i = 0; i < input.size(); i += 2) {
        // Expand file memory.
        for (int j = 0; j < static_cast<int>(input[i]) - '0'; j++) {
            expanded.push_back(static_cast<char>(idNum) + '0'); // THIS IS WRONG! THIS IS WRONG!  THIS IS WRONG!  THIS IS WRONG!  THIS IS WRONG!

        }
        // Expand free space.
        for (int j = 0; j < static_cast<int>(input[i + 1])  - '0'; j++) {
            expanded.push_back('.');
        }

        idNum++;
    }

    for (char c : expanded) {
        std::cout << c;
    }
    std::cout << "expanded!!: " << "\n";

    return expanded;
}

std::vector<char> compactDisk(const std::vector<char>& input) {
    std::vector<char> compacted = expandDisk(input);

    // Get number of digits
    int charNum = 0;
    for (char c : compacted) {
        if (c == '.') {
            continue;
        }
        charNum++;
    }

    // Two pointers: i for free space, j for files
    int i = 0, j = compacted.size() - 1;
    while (i < compacted.size() - 1 && j > 0) {  // THIS MAY NOT WORK! i may need to go back j, check back if it doesn't work

        while (compacted[i] != '.' && i < compacted.size() - 1) {
            i++;
        }

        //std::cout << "Assigning: " << compacted[j] << ", to: " << compacted[i] << "\n";
        compacted[i] = compacted[j];

        j--;
        while (compacted[j] == '.') {
            compacted[j] = '*';
            j--;
        }

    }

    // Trim array from j?
    //std::cout << "i & j: " << i << ", " << j << "\n";
    compacted.erase(compacted.begin() + charNum, compacted.end());

    return compacted;
}

size_t checkSum(const std::vector<char>& input) {
    size_t checksum = 0;
    auto compacted = compactDisk(input);

    for (int i = 0; i < compacted.size(); i++) {
        checksum += i * (compacted[i] - '0');
        //std::cout << compacted[i];
    }

    return checksum;
}

int main() {
    // Move file blocks one at a time from the end of the disk to the leftmost free space block
    std::vector<char> input = readFile("AoC-24/input_files/day_9/input.txt");

    int ans = checkSum(input);
    std::cout << "\nAnswer: " << ans << "\n";
}
