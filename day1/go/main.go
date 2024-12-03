package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func Solve1() int {
	file, err := os.Open("../../inputs/day1-1.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	list1 := []int{}
	list2 := []int{}

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()

		tokens := strings.Split(line, "   ")

		num1, err := strconv.Atoi(tokens[0])
		if err != nil {
			log.Fatal(err)
		}

		list1 = append(list1, num1)

		num2, err := strconv.Atoi(tokens[1])
		if err != nil {
			log.Fatal(err)
		}

		list2 = append(list2, num2)
	}

	sort.Slice(list1, func(i, j int) bool {
		return list1[i] < list1[j]
	})

	sort.Slice(list2, func(i, j int) bool {
		return list2[i] < list2[j]
	})

	result := 0

	for i := range list1 {
		diff := list1[i] - list2[i]

		if diff < 0 {
			result += -diff
		} else {
			result += diff
		}
	}

	return result
}

func Solve2() int {
	file, err := os.Open("../../inputs/day1-1.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	list1 := []int{}
	list2 := []int{}

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()

		tokens := strings.Split(line, "   ")

		num1, err := strconv.Atoi(tokens[0])
		if err != nil {
			log.Fatal(err)
		}

		list1 = append(list1, num1)

		num2, err := strconv.Atoi(tokens[1])
		if err != nil {
			log.Fatal(err)
		}

		list2 = append(list2, num2)
	}

	counter := map[int]int{}

	for _, num := range list2 {
		if _, ok := counter[num]; !ok {
			counter[num] = 0
		}
		counter[num] += 1
	}

	result := 0

	for _, num := range list1 {
		val, ok := counter[num]
		if !ok {
			continue
		}
		result += val * num
	}

	return result
}

func main() {
	fmt.Println("Day 1 -- Part 1:", Solve1())
	fmt.Println("Day 1 -- Part 2:", Solve2())
}
