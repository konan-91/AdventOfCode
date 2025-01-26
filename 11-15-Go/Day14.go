// Advent Of Code 2024, Day 14.
// https://adventofcode.com/2024/day/14

package main

import (
	"bufio"
	"fmt"
	"math"
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

func xmasTree(coordinates [][]int) int {
	for idx := 1; idx < 50000; idx++ {
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

		// Calculate the average distance to all other points
		var distances []int
		for c1 := 0; c1 < len(coordinates); c1 += 1 {
			for c2 := 0; c2 < len(coordinates); c2 += 1 {
				dstX := math.Abs(float64(coordinates[c1][0] - coordinates[c2][0]))
				dstY := math.Abs(float64(coordinates[c1][1] - coordinates[c2][1]))
				distances = append(distances, int(dstX*dstY))
			}
		}
		average := 0
		for _, item := range distances {
			average += item
		}
		average /= len(distances)

		// If the average distance is abnormally low, a tree is present
		if average < 500 {
			displayGrid := make([][]rune, Rows)
			for j := range displayGrid {
				displayGrid[j] = make([]rune, Cols)
				for k := range displayGrid[j] {
					displayGrid[j][k] = ' '
				}
			}
			for _, item := range coordinates {
				displayGrid[item[1]][item[0]] = '*'
			}
			for _, line := range displayGrid {
				for _, char := range line {
					fmt.Printf("%c", char)
				}
				fmt.Println()
			}

			return idx
		}
	}

	return -1
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
	xmasScore := xmasTree(coordinates)
	fmt.Println("Safety factor after 100 seconds:", safetyFactor(coordinates))
	fmt.Println("Seconds before xmas tree formed:", xmasScore)
}
