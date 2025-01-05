// Advent Of Code 2024++, Day 11.
// https://adventofcode.com/2024/day/11
// WORK IN PROGRESS!! Please check back later..
package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readFile(path string) map[uint64]uint64 {
	file, err := os.ReadFile(path)
	if err != nil {
		panic(err)
	}
	strArr := strings.Fields(string(file))

	intMap := make(map[uint64]uint64, len(strArr))
	for _, str := range strArr {
		num, err := strconv.ParseUint(str, 10, 64)
		if err != nil {
			panic(err)
		}
		if _, exists := intMap[num]; exists {
			intMap[num] += 1
		} else {
			intMap[num] = 1
		}
	}

	// Temp
	for key := range intMap {
		fmt.Printf("%d,%d  ", key, intMap[key])
	}
	fmt.Println()
	intMap = map[uint64]uint64{125: 1, 17: 1} // Temp test

	return intMap
}

func blink(stones *map[uint64]uint64) map[uint64]uint64 {
	changedStones := make(map[uint64]uint64, len(*stones)*2)

	for key := range *stones {

		// Add cache logic here later if need be

		if key == 0 {
			changedStones[1] = (*stones)[key]
			continue
		}

		runeStone := strconv.FormatUint(key, 10)
		N := len(runeStone)
		if N%2 == 0 {
			left, _ := strconv.ParseUint(runeStone[0:N/2], 10, 64)
			right, _ := strconv.ParseUint(runeStone[N/2:], 10, 64)
			changedStones[left], changedStones[right] = (*stones)[key], (*stones)[key]
		} else {
			changedStones[key*2024] = (*stones)[key]
		}
	}

	return changedStones
}

func countStones(path string) uint64 {
	stones := readFile(path)
	var ans uint64 = 0
	blinkNum := 1

	for i := 0; i < 6; i++ {
		if blinkNum == 25 {
			fmt.Println("Stones at 25th blink:", len(stones))
		} else {
			fmt.Println("Blink no.:", blinkNum)
		}

		blinkNum++
		stones = blink(&stones)
	}

	for key := range stones {
		ans += key * stones[key]
	}

	return ans
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Println("Stones at 75th blink:", ans) // 194,557 LOL - useless code broke answer
}
