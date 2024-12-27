// Advent Of Code 2024++, Day 7.

#include <array>
#include <iostream>
#include <string>

std::array<std::array<int, 15>, 850> openFile(std::string path) {
    std::array<std::array<int, 15>, 850> arr;

    return arr;
}

int calibrationSum(std::array<std::array<int, 15>, 850> input) {
    // evaluate whether nums in line can be equal to the number at the beginning using (+) or using (-)
    // ex 3267: 81 40 27  ->  ((81 * 40) + 27))  ==  3267

    return 0;
}

int calibrationSum2(std::array<std::array<int, 15>, 850> input) {
    // New operator, concatenate (||), alongside (+) and (*)
    // ex 7290: 6 8 6 15  ->  (((6 * 8) || 6) * 15)  ->  486 * 15  ==  7290

    return 0;
}

int main() {
    // TODO: everything. WIP!
    // Thoughts: pt.2 should be easy if pt.1 is solved, just add another possibility.
    // Runtime will probably increase by ^(n||) if getting all possible combinations
    std::array<std::array<int, 15>, 850> input = openFile("AoC-24/input_files/day_7/input.txt");
    std::cout << ;

    return 0;
}