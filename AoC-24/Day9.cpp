// Advent Of Code 2024++, Day 9.
// https://adventofcode.com/2024/day/9

// TODO: everything! Work in progress

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
    std::vector<char> input(str.begin(), str.end());

    return input;
}

expandDisk() {

    return ;
}

compactDisk() {

    return ;
}

size_t checkSum() {
    size_t checksum ;

    return checksum;
}

int main() {
    // Move file blocks one at a time from the end of the disk to the leftmost free space block
    std::vector<char> input = readFile("AoC-24/input_files/day_9/input.txt");
    std::cout << input[0] << "\n";
}