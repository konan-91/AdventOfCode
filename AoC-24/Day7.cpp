// Advent Of Code 2024++, Day 7.

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::vector<std::vector<long>> openFile(const std::string& path) {
    std::vector<std::vector<long>> equations;
    std::ifstream file(path);
    equations.reserve(850);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // String for each line from here
            std::vector<long> nums;
            nums.reserve(15);
            std::string token;
            std::stringstream stream(line);

            // Splitting the string in half around the ':'
            while (std::getline(stream, token, ':')) {
                // Now we have a string with only numbers separated by space
                std::stringstream innerStream(token);
                std::string num;

                // Get the number from the stream
                while (std::getline(innerStream, num, ' ')) {
                    if (!num.empty()) {
                        nums.push_back(std::stoll(num));
                    }
                }
            }

            equations.push_back(nums);
        }
    } else {
        std::cerr << "File open unsuccessful!";
    }

    // test input
    std::vector<std::vector<long>> testequations = {
        {190L, 10L, 19L},
        {3267L, 81L, 40L, 27L},
        {83L, 17L, 5L},
        {156L, 15L, 6L},
        {7290L, 6L, 8L, 6L, 15L},
        {161011L, 16L, 10L, 13L},
        {192L, 17L, 8L, 14L},
        {21037L, 9L, 7L, 18L, 13L},
        {292L, 11L, 6L, 16L, 20L}
    };

    return equations;
}

// TODO: Study C answer as it shows error perfectly.
bool equationCheck(const std::vector<long>& equation, int pos, long testVal) {
    long testValBackup;
    int posBackup;
    int divCount = 0;

    while (pos > 1) {

        if (testVal % equation[pos] == 0) {
            testValBackup = testVal - equation[pos];
            testVal /= equation[pos];

            pos--;
            posBackup = pos;

            divCount++;

        } else {
            testVal -= equation[pos];
            pos--;
        }
    }

    if (testVal - equation[1] == 0) {
        return true;
    }

    // if we made a pass with no divides and still didn't get 0, we can safely return false as there are no other options.
    if (divCount == 0) {
        return false;
    }

    // If divide didn't work, try the equation again but pass in starting values as if you had (-) instead of (/)
    return equationCheck(equation, posBackup, testValBackup);
}

bool concatenateCheck(const std::vector<long>& equation, int pos, long testVal) {
    return false;
}

std::pair<long, long> calibrationSum(const std::vector<std::vector<long>>& equations) {
    long sum = 0;
    long concatenateSum = 0;

    for (auto equation : equations) {
        int startPos = equation.size() - 1;
        long testVal = equation[0];

        if (equationCheck(equation, startPos, testVal)) {
            sum += equation[0];
        }

        if (concatenateCheck(equation, startPos, testVal)) {
            concatenateSum += equation[0];
        }
    }

    return std::make_pair(sum, concatenateSum);
}

int main() {
    std::vector<std::vector<long>> input = openFile("AoC-24/input_files/day_7/input.txt");
    auto [calibration, concatenation] = calibrationSum(input);
    std::cout << "Total calibration result: " << calibration << "\n";
    std::cout << "Total calibration result with concatenation: " << concatenation << "\n";
}