package test

import "fmt"

type b interface {
	add(m int) int
}

type b1 struct {
	X int
}

func (this *b1) add(m int) int {
	return this.X + m
}

type b2 struct {
	Y int
}

func (this *b2) add(m int) int {
	return this.Y + m + 100
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
	// p = new(b3) // 这里报错
	// fmt.Println("-->", p.add(1))
}
