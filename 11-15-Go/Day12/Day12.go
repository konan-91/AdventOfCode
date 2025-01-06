// Advent Of Code 2024++, Day 12.
// https://adventofcode.com/2024/day/12

package main

import (
	"fmt"
	"os"
	"strings"
)

func readFile(path string) [][]rune {
	file, err := os.ReadFile(path)
	if err != nil {
		panic(err)
	}

	lines := strings.Split(string(file), "\n")
	var runeArr [][]rune
	for _, line := range lines {
		if line != "" {
			runeArr = append(runeArr, []rune(line))
		}
	}

	return runeArr
}

func contains(queue *[][2]int, target [2]int) bool {
	for _, x := range *queue {
		if x == target {
			return true
		}
	}
	return false
}

func countRegion(gardenMap *[][]rune, pos [2]int) int {
	traversed := make(map[[2]int]int)
	var directions = [][2]int{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
	queue := [][2]int{pos}

	for len(queue) != 0 {
		pos = queue[0]
		perimeter := 0
		symbol := (*gardenMap)[pos[0]][pos[1]]

		for _, dir := range directions {
			y := pos[0] + dir[0]
			x := pos[1] + dir[1]

			if _, exists := traversed[[2]int{y, x}]; exists {
				continue
			}

			if contains(&queue, [2]int{y, x}) {
				continue
			}

			if y < 0 || y >= len(*gardenMap) || x < 0 || x >= len((*gardenMap)[0]) {
				perimeter++
				continue
			}

			if (*gardenMap)[y][x] == symbol {
				queue = append(queue, [2]int{y, x})
			} else {
				perimeter++
			}
		}

		traversed[[2]int{pos[0], pos[1]}] = perimeter
		queue = queue[1:]
	}

	for plot := range traversed {
		(*gardenMap)[plot[0]][plot[1]] = '*'
	}

	sum := 0
	for _, perim := range traversed {
		sum += perim
	}

	return sum * len(traversed)
}

func totalPrice(path string) int {
	gardenMap := readFile(path)
	sum := 0

	for i := 0; i < len(gardenMap); i++ {
		for j := 0; j < len(gardenMap[0]); j++ {
			if gardenMap[i][j] == '*' {
				continue
			}
			/*/Print map to verify things are working
			for _, row := range gardenMap {
				for _, char := range row {
					fmt.Printf("%c", char)
				}
				fmt.Println()
			}
			fmt.Println()
			*/
			sum += countRegion(&gardenMap, [2]int{i, j})
		}
	}

	return sum
}

func main() {
	answer := totalPrice("input_files/day_12/input.txt")
	fmt.Println("Answer:", answer)
}
