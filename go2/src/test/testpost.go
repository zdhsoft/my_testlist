package test

import "fmt"

type TPoint struct {
	x int
	y int
}

func (p TPoint) calc() int {
	return p.x + p.y
}

func (p *TPoint) mul() int {
	return p.x * p.y
}

func getPoint(x int, y int) *TPoint {
	p := new(TPoint)
	p.x = x
	p.y = y
	return p
}

func TestPoint() {
	p := new(TPoint)
	p.x = 100
	p.y = 200

	p1 := getPoint(200, 300)

	fmt.Println("point:", p.x, p.y, p.calc(), p.mul())
	fmt.Println("point1:", p1.x, p1.y, p1.calc(), p1.mul())
}
