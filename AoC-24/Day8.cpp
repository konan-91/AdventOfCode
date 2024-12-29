// Advent Of Code 2024++, Day 8.

#include <fstream>
#include <iostream>

std::vector<std::vector<char>> readFile(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::vector<char>> city;
    city.reserve(50);

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return city;
    }

    std::string str;
    while (getline(file, str)) {
        std::vector<char> line;
        line.reserve(130);
        for (const char& c : str) {
            line.push_back(c);
        }
        city.push_back(line);
    }

    return city;
}

// TODO: everything! Work in progress.

int main() {
    auto result = readFile("AoC-24/input_files/day_8/input.txt");

    for (auto collinearity : result) {
        for (auto c : collinearity) {
            std::cout << c;
        }
        std::cout << "\n";
    }
}