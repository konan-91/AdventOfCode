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
	file, err := os.ReadFile(path)
	if err != nil {
		panic(err)
	}
	// Convert to string & split
	strArr := strings.Fields(string(file))

	// Convert to []uint64
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

// PT.2 SOLUTION -> Cache solutions in map. For each stone, before doing anything, check if the answer is in the cache.
// If yes, use the answer and skip.
// If no, calculate the answer and add to the cache.
func blink(stones *[]uint64) []uint64 {
	changedStones := make([]uint64, 0, len(*stones)*2)

	for _, stone := range *stones {
		if stone == 0 {
			changedStones = append(changedStones, 1)
			continue
		}

		runeStone := strconv.FormatUint(stone, 10)
		N := len(runeStone)

		if N%2 == 0 {
			// Split in half & append
			lhsNum, _ := strconv.ParseUint(runeStone[0:N/2], 10, 64)
			rhsNum, _ := strconv.ParseUint(runeStone[N/2:N], 10, 64)
			changedStones = append(changedStones, lhsNum, rhsNum)
		} else {
			changedStones = append(changedStones, stone*2024)
		}
	}

	return changedStones
}

func countStones(path string) int {
	blinkNum := 0
	stones := readFile(path)
	for i := 0; i < 40; i++ {
		if blinkNum == 25 {
			fmt.Println("Stones at 25th blink:", len(stones))
		} else {
			fmt.Println("Blink no.:", blinkNum+1)
		}
		blinkNum++
		stones = blink(&stones)
	}
	return len(stones)
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Println("Stones at 75th blink:", ans) // 194,557 LOL - useless code broke answer
}
