package test

import "fmt"

type b interface {
	add(m int) int
}

type b1 struct {
	X int
}

func (s *b1) add(m int) int {
	return s.X + m
}

type b2 struct {
	Y int
}

func (s *b2) add(m int) int {
	return s.Y + m + 100
}

type b3 struct {
	Z int
}

func TestInterface() {
	var p b
	p = new(b1)
	fmt.Println("-->", p.add(1))
	p = new(b2)
	fmt.Println("-->", p.add(1))
	// p = new(b3) // 这里报错. 因为这里没事实现接口。
	// fmt.Println("-->", p.add(1))
}
