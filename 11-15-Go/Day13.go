// Advent Of Code 2024, Day 13.
// https://adventofcode.com/2024/day/13

//go:build Day13
// +build Day13

package main

import (
	"bufio"
	"fmt"
	"math"
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

func tokenCount(buttonA [2]int64, buttonB [2]int64, target [2]int64) int64 {
	// System of linear equations: set one equal to the other and solve for Ax, Bx
	Ax := float64(buttonB[1]*target[0]-buttonB[0]*target[1]) / float64(buttonB[1]*buttonA[0]-buttonB[0]*buttonA[1])
	Bx := float64(buttonA[1]*target[0]-buttonA[0]*target[1]) / float64(buttonA[1]*buttonB[0]-buttonA[0]*buttonB[1])

	// If results are not integers, there are no valid solutions
	if Ax != math.Trunc(Ax) || Bx != math.Trunc(Bx) {
		return 0
	}

	return int64((3 * Ax) + Bx)
}

func main() {
	machines := readFile("input_files/day_13/input.txt")
	var tokenSum int64 = 0
	var tokenSumConverted int64 = 0

	for _, machine := range machines {
		// Part 1
		ans := tokenCount(
			[2]int64{machine[0], machine[1]},
			[2]int64{machine[2], machine[3]},
			[2]int64{machine[4], machine[5]})
		if ans > 0 {
			tokenSum += ans
		}

		// Part 2
		ans = tokenCount(
			[2]int64{machine[0], machine[1]},
			[2]int64{machine[2], machine[3]},
			[2]int64{machine[4] + 10000000000000, machine[5] + 10000000000000})
		if ans > 0 {
			tokenSumConverted += ans
		}
	}

	fmt.Println("Min number of tokens:", tokenSum)
	fmt.Println("Min tokens after conversion:", tokenSumConverted)
}
