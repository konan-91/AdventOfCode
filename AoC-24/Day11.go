// Advent Of Code 2024++, Day 11.
// https://adventofcode.com/2024/day/11
// WORK IN PROGRESS!! Please check back later...
package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readFile(path string) []uint64 {
	// Read file
	file, err := os.ReadFile(path)
	if err != nil {
		panic(err)
	}

	// Split the string, trim whitespace, remove ""
	strArr := strings.Fields(string(file))

	// Convert atrArr to intArr
	intArr := make([]uint64, len(strArr))
	for i, str := range strArr {
		num, err := strconv.ParseUint(str, 10, 64)
		if err != nil {
			panic(err)
		}
		intArr[i] = num
	}

	return intArr
}

func main() {
	stones := readFile("input_files/day_11/input.txt")
	fmt.Println(stones)
}
