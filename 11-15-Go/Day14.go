// Advent Of Code 2024, Day 14.
// https://adventofcode.com/2024/day/14

package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

const (
	Rows = 101
	Cols = 103
)

func readFile(path string) [][]int {
	var coordinates [][]int
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}

	re := regexp.MustCompile(`-?\d+`)
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		matches := re.FindAllString(line, 4)
		if matches == nil {
			continue
		}
		var ints []int
		for _, str := range matches {
			if num, err := strconv.Atoi(str); err == nil {
				ints = append(ints, num)
			}
		}
		coordinates = append(coordinates, ints)
	}

	return coordinates
}

func simulateMovement(coordinates [][]int) [][]int {
	for i, item := range coordinates {
		posX := (item[0] + item[2]*100) % Rows
		posY := (item[1] + item[3]*100) % Cols
		//fmt.Println(posX, posY)

		if posX < 0 {
			posX += Rows
		}
		if posY < 0 {
			posY += Cols
		}
		//fmt.Println(posX, posY)

		coordinates[i][0] = posX
		coordinates[i][1] = posY
	}

	return coordinates
}

func safetyFactor(coordinates [][]int) int {
	grid := simulateMovement(coordinates)
	ans := 0

	finalGrid := make([][]int, Rows)
	for i := range finalGrid {
		finalGrid[i] = make([]int, Cols)
	}
	for _, item := range grid {
		finalGrid[item[0]][item[1]]++
	}

	//TODO: Calculate Safety Factor

	return ans
}

func main() {
	coordinates := readFile("input_files/day_14/input.txt")
	fmt.Println(safetyFactor(coordinates))
}
