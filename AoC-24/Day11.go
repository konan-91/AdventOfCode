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

// TODO: find a better solution than caching. Even when you answer is accessed rather than calculated,
// TODO: it is still insanely slow.
func blink(stones *[]uint64, cache *map[uint64][]uint64) []uint64 {
	changedStones := make([]uint64, 0, len(*stones)*2)

	for _, stone := range *stones {
		// Dereference the pointer to access the map
		if value, exists := (*cache)[stone]; exists {
			for _, item := range value {
				changedStones = append(changedStones, item)
			}
			continue
		}

		if stone == 0 {
			changedStones = append(changedStones, 1)
			(*cache)[stone] = append((*cache)[stone], 1)
			continue
		}

		runeStone := strconv.FormatUint(stone, 10)
		N := len(runeStone)

		if N%2 == 0 {
			// Split in half & append
			lhsNum, _ := strconv.ParseUint(runeStone[0:N/2], 10, 64)
			rhsNum, _ := strconv.ParseUint(runeStone[N/2:], 10, 64)
			changedStones = append(changedStones, lhsNum, rhsNum)
			(*cache)[stone] = append((*cache)[stone], lhsNum, rhsNum)
		} else {
			changedStones = append(changedStones, stone*2024)
			(*cache)[stone] = append((*cache)[stone], stone*2024)
		}
	}

	return changedStones
}

func countStones(path string) int {
	stones := readFile(path)
	cache := make(map[uint64][]uint64)
	blinkNum := 0

	for i := 0; i < 49; i++ {
		if blinkNum == 25 {
			fmt.Println("Stones at 25th blink:", len(stones))
		} else {
			fmt.Println("Blink no.:", blinkNum+1)
		}
		blinkNum++
		stones = blink(&stones, &cache)
	}

	return len(stones)
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Println("Stones at 75th blink:", ans) // 194,557 LOL - useless code broke answer
}
