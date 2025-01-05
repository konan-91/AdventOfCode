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

	return intMap
}

func blink(stones *map[uint64]uint64) map[uint64]uint64 {
	changedStones := make(map[uint64]uint64, len(*stones)*2)

	for key := range *stones {
		if key == 0 {
			if _, exists := changedStones[1]; exists {
				changedStones[1] += (*stones)[key]
			} else {
				changedStones[1] = (*stones)[key]
			}
			continue
		}

		runeStone := strconv.FormatUint(key, 10)
		N := len(runeStone)

		if N%2 == 0 {
			left, _ := strconv.ParseUint(runeStone[0:N/2], 10, 64)
			right, _ := strconv.ParseUint(runeStone[N/2:], 10, 64)
			halves := []uint64{left, right}

			for i := 0; i < 2; i++ {
				if _, exists := changedStones[halves[i]]; exists {
					changedStones[halves[i]] += (*stones)[key]
				} else {
					changedStones[halves[i]] = (*stones)[key]
				}
			}
		} else {
			if _, exists := changedStones[key*2024]; exists {
				changedStones[key*2024] += (*stones)[key]
			} else {
				changedStones[key*2024] = (*stones)[key]
			}
		}
	}

	return changedStones
}

func countStones(path string) uint64 {
	stones := readFile(path)
	var total uint64

	for blinkNum := 1; blinkNum <= 75; blinkNum++ {
		stones = blink(&stones)

		if blinkNum == 25 {
			total = sumStones(stones)
			fmt.Println("Stones at 25th blink:", total)
		}
	}

	return sumStones(stones)
}

func sumStones(stones map[uint64]uint64) uint64 {
	var total uint64
	for _, count := range stones {
		total += count
	}
	return total
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Println("Stones at 75th blink:", ans)
}
