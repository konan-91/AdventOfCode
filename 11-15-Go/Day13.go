// Advent Of Code 2024, Day 13.
// https://adventofcode.com/2024/day/13

// TODO: Everything! This week is a work in progress, please check back later...

package main

import "fmt"

type Pair struct {
	X int
	Y int
}

type Machine map[rune]Pair

func readFile(path string) []Machine {
	var machines []Machine
	// Read files etc...

	return machines
}

func tokensForPrize(machine Machine) int {
	// Maybe extract 3 variables from machine for convenience idk
	var scores Pair
	var presses Pair
	tokens := 0
	both := 99

	// Try to solve using only B
	for presses[1] <= 100 && scores[both] < prizes[both] {
		if scores == prizes {
			return tokens
		}
		scores += buttonB
		presses[1]++
		tokens++
	}

	// Replace B's with A's one by one
	for presses[0] <= 100 && scores[both] < prizes[both] {
		if scores == prizes {
			return tokens
		}
		scores -= buttonB
		scores += buttonA
		presses[0]++
		tokens += 2
	}

	return -1
}

func main() {
	machines := readFile("input_files/day_13/input.txt")
	tokenSum := 0

	for machine := range machines {
		ans := tokensForPrize(machine) // ??? The fuck is the problem here
		if ans > 0 {
			tokenSum += ans
		}
	}

	fmt.Println("Min number of tokens:", tokenSum)
}
