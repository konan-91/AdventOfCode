// Advent Of Code 2024, Day 11.
// https://adventofcode.com/2024/day/11

//go:build Day11
// +build Day11

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

	intMap := map[uint64]uint64{}
	for _, str := range strings.Fields(string(file)) {
		num, err := strconv.ParseUint(str, 10, 64)
		if err != nil {
			panic(err)
		}
		intMap[num]++
	}

	return intMap
}

func blink(stones *map[uint64]uint64) map[uint64]uint64 {
	changedStones := make(map[uint64]uint64, len(*stones)*2)

	for key, value := range *stones {
		if key == 0 {
			changedStones[1] += value
			continue
		}

		runeStone := strconv.FormatUint(key, 10)
		N := len(runeStone)

		if N%2 == 0 {
			left, _ := strconv.ParseUint(runeStone[0:N/2], 10, 64)
			right, _ := strconv.ParseUint(runeStone[N/2:], 10, 64)
			changedStones[left] += value
			changedStones[right] += value
		} else {
			changedStones[key*2024] += value
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
	var sum uint64
	for _, count := range stones {
		sum += count
	}
	return sum
}

func main() {
	ans := countStones("input_files/day_11/input.txt")
	fmt.Println("Stones at 75th blink:", ans)
}
