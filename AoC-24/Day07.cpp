// Advent Of Code 2024++, Day 7.
// https://adventofcode.com/2024/day/7

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using Equation = std::vector<long>;

std::vector<Equation> openFile(const std::string& path) {
    std::vector<Equation> equations;
    std::ifstream file(path);
    equations.reserve(850);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<long> nums;
            nums.reserve(15);
            std::string token;
            std::stringstream stream(line);

            while (std::getline(stream, token, ':')) {
                std::stringstream innerStream(token);
                std::string num;

                while (std::getline(innerStream, num, ' ')) {
                    if (!num.empty()) {
                        nums.push_back(std::stoll(num));
                    }
                }
            }

            equations.push_back(nums);
        }
    } else {
        std::cerr << "File could not be opened!";
    }

    return equations;
}

bool equationCheck(const Equation& equation, const long position, const long total, const long& endIdx) {
    if (position == endIdx) {
        return (total + equation[endIdx] == equation[0] || total * equation[endIdx] == equation[0]);
    }

    if (equationCheck(equation, position + 1, total * equation[position], endIdx)) {
        return true;
    }

    return equationCheck(equation, position + 1, total + equation[position], endIdx);
}

bool concatenateCheck(const Equation& equation, const long position, const long total, const long& endIdx) {
    const std::string str_concatenation = std::to_string(total) + std::to_string(equation[position]);
    const long concatenation = std::stoll(str_concatenation);

    if (position == endIdx) {
        return (total + equation[endIdx] == equation[0] || total * equation[endIdx] == equation[0] || concatenation == equation[0]);
    }

    if (concatenateCheck(equation, position + 1, total * equation[position], endIdx)) {
        return true;
    }

    if (concatenateCheck(equation, position + 1, concatenation, endIdx)) {
        return true;
    }

    return concatenateCheck(equation, position + 1, total + equation[position], endIdx);
}

std::pair<long, long> calibrationSum(const std::vector<Equation>& equations) {
    long sum = 0;
    long concatenateSum = 0;

    for (auto equation : equations) {
        if (equationCheck(equation, 2, equation[1], equation.size() - 1)) {
            sum += equation[0];
        }

        if (concatenateCheck(equation, 2, equation[1], equation.size() - 1)) {
            concatenateSum += equation[0];
        }
    }

    return std::make_pair(sum, concatenateSum);
}

int main() {
    std::vector<Equation> input = openFile("AoC-24/input_files/day_07/input.txt");
    auto [calibration, concatenation] = calibrationSum(input);
    std::cout << "Sum of calibration results: " << calibration << "\n";
    std::cout << "Sum including concatenation: " << concatenation << "\n";
}