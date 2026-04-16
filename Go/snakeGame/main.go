package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"

	"golang.org/x/term"
)

var board [][]int
var snake []Coordinate
var snakeOldState []Coordinate
var fruit Coordinate
var direction Coordinate
var gameOver bool
var score = 0
var termWidth int
var termHeight int
var speedMilliS = 350

const snakeColor = "\033[102m"
const headColor = "\033[42m"
const fruitColor = "\033[101m"
const borderColor = "\033[47m"
const boardColor = "\033[107m"
const resetColor = "\033[0m"

type Coordinate struct {
	x, y int
}

func (c *Coordinate) add(a Coordinate) {
	c.x += a.x
	c.y += a.y
}

func (c *Coordinate) equals(x, y int) bool {
	return c.x == x && c.y == y
}

func updateFruit() {
	var x, y int

	for {
		x = rand.Intn(termHeight)
		y = rand.Intn(termWidth)

		if board[x][y] == 0 {
			break
		}
	}

	fruit.x = x
	fruit.y = y
}

func updateboard() {
	isFruitEatten := false

	for i := range board {
		for j := range board[i] {
			board[i][j] = 0
		}
	}
	snakeOldState = make([]Coordinate, len(snake))
	copy(snakeOldState, snake)

	snake[0].add(direction) //head of the snake
	if snake[0].x == -1 || snake[0].x == termHeight || snake[0].y == -1 || snake[0].y == termWidth {
		gameOver = true
		fmt.Print("You gotta respect boundaries!\r\n")
		return
	}

	for i := 1; i < len(snake); i++ {
		snake[i] = snakeOldState[i-1]
		board[snake[i].x][snake[i].y] = -1
	}

	if board[snake[0].x][snake[0].y] == -1 {
		gameOver = true
		fmt.Print("Canabolism at its finest!\r\n")
		return
	}

	board[snake[0].x][snake[0].y] = -2

	if snake[0].x == fruit.x && snake[0].y == fruit.y {
		updateFruit()
		score++
		if speedMilliS > 100 {
			speedMilliS -= 10
		}
		isFruitEatten = true
	}

	board[fruit.x][fruit.y] = 1

	if isFruitEatten {
		snake = append(snake, snakeOldState[len(snakeOldState)-1])
		isFruitEatten = false
	}
}

func drawboard() {
	var output strings.Builder
	output.WriteString(borderColor + " ")
	for range termWidth {
		output.WriteString("  ")
	}
	output.WriteString(" " + resetColor + "\r\n")

	for i := range board {
		output.WriteString(borderColor + " " + resetColor)
		for _, v := range board[i] {
			switch v {
			case 0:
				output.WriteString(boardColor + "  " + resetColor)
			case -1:
				output.WriteString(snakeColor + "  " + resetColor)
			case -2:
				output.WriteString(headColor + "  " + resetColor)
			case 1:
				output.WriteString(fruitColor + "  " + resetColor)
			}
		}
		output.WriteString(borderColor + " " + resetColor + "\r\n")
	}

	output.WriteString(borderColor + " ")
	for range termWidth {
		output.WriteString("  ")
	}
	output.WriteString(" " + resetColor + "\r\n")

	output.WriteString("Score: " + strconv.Itoa(score) + "\r\n")
	fmt.Print(output.String())
}

func gameLoop(quit chan struct{}) {
	for {
		select {
		case <-quit:
			return
		default:
			clearScreen := "\033[H\033[J"
			fmt.Print(clearScreen)

			updateboard()
			if gameOver {
				return
			}

			drawboard()
			time.Sleep(time.Duration(speedMilliS) * time.Millisecond)
		}
	}
}

func keyboardInput(quit chan struct{}) {
	buffer := make([]byte, 3)

	for {
		n, err := os.Stdin.Read(buffer)
		if err != nil {
			panic(err)
		}

		if n == 3 && buffer[0] == 27 && buffer[1] == 91 {
			switch buffer[2] {
			case 'A': //up
				if !direction.equals(1, 0) {
					direction.x = -1
					direction.y = 0
				}
			case 'B': //down
				if !direction.equals(-1, 0) {
					direction.x = 1
					direction.y = 0
				}
			case 'D': //left
				if !direction.equals(0, 1) {
					direction.x = 0
					direction.y = -1
				}
			case 'C': //right
				if !direction.equals(0, -1) {
					direction.x = 0
					direction.y = 1
				}
			}
			continue
		}
		if n == 1 && buffer[0] == 'q' {
			close(quit)
			return
		}
	}
}

func main() {
	w, h, err := term.GetSize(int(os.Stdin.Fd()))
	if err != nil {
		panic(err)
	}
	termWidth = (w+2-1)/2 - 2
	termHeight = h - 5

	println(w, h, termWidth, termHeight)

	oldState, err := term.MakeRaw(int(os.Stdin.Fd()))
	if err != nil {
		panic(err)
	}
	defer term.Restore(int(os.Stdin.Fd()), oldState)

	quit := make(chan struct{})
	row, col := termHeight, termWidth
	board = make([][]int, row)
	for i := range board {
		board[i] = make([]int, col)
	}
	snake = make([]Coordinate, 0)
	snake = append(snake, Coordinate{0, 0})
	updateFruit()
	direction = Coordinate{1, 0}

	go keyboardInput(quit)
	gameLoop(quit)
	fmt.Print("GameOver!\r\n")
}
