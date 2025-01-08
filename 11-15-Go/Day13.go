// Advent Of Code 2024, Day 13.
// https://adventofcode.com/2024/day/13

// TODO: finish part 2! Add a switch for pt.2 which changes <100 to <gazillion, and the special *1,000,000,000 logic
// TODO: which skips a billion steps and adds a billion tokens! And also

package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func extractNums(str string) ([]int64, error) {
	re := regexp.MustCompile(`\d{2,5}`)
	matches := re.FindAllString(str, -1)
	nums := make([]int64, 0, len(matches))

	for _, match := range matches {
		num, err := strconv.Atoi(match)
		if err != nil {
			return nil, fmt.Errorf("invalid integer: %q in string: %s", match, str)
		}
		nums = append(nums, int64(num))
	}

	return nums, nil
}

func readFile(path string) [][]int64 {
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}

	scanner := bufio.NewScanner(file)
	var strList []string
	line := ""

	for scanner.Scan() {
		if scanner.Text() == "" {
			strList = append(strList, line)
			line = ""
			continue
		}
		line += scanner.Text()
	}
	strList = append(strList, line)

	var machines [][]int64
	for _, str := range strList {
		machine, err := extractNums(str)
		if err != nil {
			panic(err)
		}
		machines = append(machines, machine)
	}

	return machines
}

func tokenCount(buttonA [2]int64, buttonB [2]int64, target [2]int64, conversionNum int64) int64 {
	score := [2]int64{0, 0}
	presses := [2]int64{0, 0}
	var tokens int64 = 0
	var skipNum int64 = 10000000000

	// Press B until either score exceeds targets (or equals it, or presses maxes out)
	for score[0]+buttonB[0] <= target[0] && score[1]+buttonB[1] <= target[1] && presses[1]+1 < conversionNum { // Changed here
		score[0] += buttonB[0]
		score[1] += buttonB[1]
		presses[1]++
		tokens++

		// TODO: Implement skipping logic here
		if score[0]+buttonB[0]+skipNum <= target[0] && score[1]+buttonB[1]+skipNum <= target[1] {
			score[0] = score[0] + buttonB[0] + skipNum
			score[1] = score[1] + buttonB[1] + skipNum
			presses[1] += skipNum
			tokens += skipNum
		} else {
			skipNum /= 10
		}

		if score[0] == target[0] && score[1] == target[1] {
			return tokens
		}

		fmt.Println("Part 1:", score)
	}

	fmt.Println("Target:", target)
	fmt.Println("Outcome:", score)

	// Keep adding A while presses[1] < 100 and under or @ target
	// If target reached, take away B and try again
	for presses[0] < conversionNum {
		if score[0] == target[0] && score[1] == target[1] {
			fmt.Println(score, target, tokens)
			return tokens
		}

		if score[0]+buttonA[0] <= target[0] && score[1]+buttonA[1] <= target[1] {
			score[0] += buttonA[0]
			score[1] += buttonA[1]
			presses[0]++
			tokens += 3
		} else { // Since you can't add A anymore, take away B and try again!
			score[0] -= buttonB[0]
			score[1] -= buttonB[1]
			presses[1]--
			tokens--
		}
		// TODO: implement a break here when either of the scores go under 0 -- this is way too low, calculate a better bottom end
		if score[0] < 0 || score[1] < 0 {
			break
		}
		fmt.Println("Part 2:", score)
	}

	return -1
}

func main() {
	machines := readFile("input_files/day_13/inputt.txt")
	var tokenSum int64 = 0
	var tokenSumConverted int64 = 0
	var conversionNum int64 = 10000000000000

	for _, machine := range machines {
		// Part 1 - Stopping at 100
		ans := tokenCount(
			[2]int64{machine[0], machine[1]},
			[2]int64{machine[2], machine[3]},
			[2]int64{machine[4], machine[5]},
			100)
		if ans > 0 {
			tokenSum += ans
		}

		// Part 2 - Rectify conversion error and do not stop at 100 each
		ans = tokenCount(
			[2]int64{machine[0], machine[1]},
			[2]int64{machine[2], machine[3]},
			[2]int64{machine[4] + conversionNum, machine[5] + conversionNum},
			conversionNum)
		if ans > 0 {
			tokenSumConverted += ans
		}
	}

	fmt.Println("Min number of tokens:", tokenSum) // 518 too low. Rethink...
}
