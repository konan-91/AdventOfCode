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
	Rows = 103
	Cols = 101
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
		posX := (item[0] + item[2]*100) % Cols
		posY := (item[1] + item[3]*100) % Rows

		if posX < 0 {
			posX += Cols
		}
		if posY < 0 {
			posY += Rows
		}

		coordinates[i][0] = posX
		coordinates[i][1] = posY
	}

	return coordinates
}

// TODO: Fix this.
func xmasTree(coordinates [][]int) [][]int {
	for iter := range 100 {
		for i, item := range coordinates {
			posX := item[0] + item[2]
			posY := item[1] + item[3]

			if posX > Cols-1 {
				posX %= Cols
			}
			if posY > Rows-1 {
				posY %= Rows
			}
			if posX < 0 {
				posX += Cols
			}
			if posY < 0 {
				posY += Rows
			}

			coordinates[i][0] = posX
			coordinates[i][1] = posY
		}

		if iter == 27 {
			// Temp printing result for each step
			fmt.Println(iter)
			tmpGrid := make([][]rune, Rows)
			for i := range tmpGrid {
				tmpGrid[i] = make([]rune, Cols)
				for j := range tmpGrid[i] {
					tmpGrid[i][j] = ' ' // Populate each cell with a space character
				}
			}

			for _, item := range coordinates {
				tmpGrid[item[1]][item[0]] = '*'
			}
			for _, row := range tmpGrid {
				for _, cell := range row {
					fmt.Printf("%c", cell) // Print the character
				}
				fmt.Println() // Move to the next line after each row
			}
			fmt.Println("DONE!")
			// End tmp
		}
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
		finalGrid[item[1]][item[0]]++
	}

	bounds := [][]int{
		{0, Rows / 2, 0, Cols / 2},                   // Top Left
		{0, Rows / 2, (Cols / 2) + 1, Cols},          // Top Right
		{(Rows / 2) + 1, Rows, 0, Cols / 2},          // Bottom Left
		{(Rows / 2) + 1, Rows, (Cols / 2) + 1, Cols}, // Bottom Right
	}

	for _, bound := range bounds {
		qSum := 0
		for i := bound[0]; i < bound[1]; i++ {
			for j := bound[2]; j < bound[3]; j++ {
				qSum += finalGrid[i][j]
			}
		}

		// Assigning to actual answer. Multiplying
		if ans != 0 {
			ans *= qSum
		} else {
			ans = qSum
		}
	}

	return ans
}

func main() {
	coordinates := readFile("input_files/day_14/input.txt")
	fmt.Println(safetyFactor(coordinates))
	xmasTree(coordinates)
}
