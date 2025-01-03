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

	// intArr = []uint64{125, 17}

	return intArr
}

func blink(stones []uint64) []uint64 {
	changedStones := make([]uint64, 0, len(stones)*2)
	for _, stone := range stones {
		if stone == 0 {
			changedStones = append(changedStones, 1)
			continue
		}

		// Convert to runes, verify whether it can be halved, verify whether RHS consists of 0's
		runeStone := []rune(strconv.FormatUint(stone, 10))
		N := len(runeStone)
		if N%2 == 0 {
			// Split in half
			lhs := runeStone[0 : N/2]
			rhs := runeStone[N/2 : N]

			// No need to remove trailing 0's? Probably handled by ParseUint

			// Convert back & append
			lhsNum, err := strconv.ParseUint(string(lhs), 10, 64)
			if err != nil {
				panic(err)
			}
			rhsNum, err := strconv.ParseUint(string(rhs), 10, 64)
			if err != nil {
				panic(err)
			}

			changedStones = append(changedStones, lhsNum, rhsNum)
		} else {
			changedStones = append(changedStones, stone*2024)
		}
	}

	//fmt.Println(changedStones)
	return changedStones
}

func countStones(path string) int {
	stones := readFile(path)
	for i := 0; i < 25; i++ {
		fmt.Println("Current length:", len(stones))
		stones = blink(stones)
	}
	return len(stones)
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Printf("Answer! -> %d\n", ans) // 194,433 -> too low! 194,557 LOL - useless code broke answer
}
