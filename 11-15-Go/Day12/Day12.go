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

func regionPrice(gardenMap *[][]rune, pos [2]int) [2]int {
	directions := [][2]int{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
	traversed := make(map[[2]int][4]int)
	queue := [][2]int{pos}

	// Part one: using BFS to find regions by exploring neighbours
	for len(queue) != 0 {
		pos = queue[0]
		perimeter := [4]int{0, 0, 0, 0} // Keep track of borders for each position
		symbol := (*gardenMap)[pos[0]][pos[1]]

		for i, dir := range directions {
			y := pos[0] + dir[0]
			x := pos[1] + dir[1]
			_, exists := traversed[[2]int{y, x}]

			if exists || contains(&queue, [2]int{y, x}) {
				continue
			}

			if y < 0 || y >= len(*gardenMap) || x < 0 || x >= len((*gardenMap)[0]) {
				perimeter[i] = 1
				continue
			}

			if (*gardenMap)[y][x] == symbol {
				queue = append(queue, [2]int{y, x})
			} else {
				perimeter[i] = 1
			}
		}

		traversed[[2]int{pos[0], pos[1]}] = perimeter
		queue = queue[1:]
	}

	ans1 := 0
	for plot, perim := range traversed {
		(*gardenMap)[plot[0]][plot[1]] = '*'
		for _, val := range perim {
			ans1 += val
		}
	}

	// Part 2: Finding consecutive rows of fences and applying discount
	ans2 := ans1
	for i := 0; i < 4; i++ {
		for plot, perim := range traversed {
			if perim[i] == 1 {
				ans2 -= calculateDiscount(&traversed, i, plot)
			}
		}
	}

	ans1 *= len(traversed)
	ans2 *= len(traversed)

	return [2]int{ans1, ans2}
}

func calculateDiscount(traversed *map[[2]int][4]int, i int, plot [2]int) int {
	discount := 0
	isVertical := 0

	if i == 0 || i == 2 {
		isVertical = 1
	}

	for dir := -1; dir <= 1; dir += 2 {
		pos := plot
		pos[isVertical] += dir
		for {
			perim, exists := (*traversed)[pos]
			if exists && perim[i] == 1 {
				discount++
				perim[i] = 0
				(*traversed)[pos] = perim
				pos[isVertical] += dir
			} else {
				break
			}
		}
	}

	return discount
}

func main() {
	gardenMap := readFile("input_files/day_12/input.txt")
	sum1, sum2 := 0, 0

	for i := 0; i < len(gardenMap); i++ {
		for j := 0; j < len(gardenMap[0]); j++ {
			if gardenMap[i][j] == '*' {
				continue
			}
			price := regionPrice(&gardenMap, [2]int{i, j})
			sum1 += price[0]
			sum2 += price[1]
		}
	}

	fmt.Println("Sum of fence prices:", sum1)
	fmt.Println("Sum after discount:", sum2)
}

// pt.2: 953738
