// Advent Of Code 2024++, Day 12.
// https://adventofcode.com/2024/day/12

package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func readFile(path string) [][]rune {
	file, err := ioutil.ReadFile(path)
	if err != nil {
		panic(err)
	}

	lines := strings.Split(string(file), "\n")
	var runeArr [][]rune
	for _, line := range lines {
		runeArr = append(runeArr, []rune(line))
	}

	return runeArr
}

func defineRegion() int {

	return 0
}

func fencePrice(path string) int64 {
	gardenMap := readFile(path)

	// Iterate through every spot, skipping 0's
	// Once letter found, defineRegion and add to cost
	// Turn region to 0's and continue

	return int64(0)
}

func main() {
	answer := fencePrice("input_files/day_12/input.txt")
	fmt.Println(answer)
}
