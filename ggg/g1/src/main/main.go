package main

import (
	"fmt"
)

func P(prompt string, arr []int) {
	fmt.Printf("%s => %p\n", prompt, arr)
	fmt.Print("[")
	for _, v := range arr {
		fmt.Printf("%d, ", v)
	}
	fmt.Print("]\n")
}

type S struct {
	A1 int
	A2 string
	A3 int
}

func newS() *S {
	return new(S)
}

func CreateS() *S {
	return &S{}
}

func main() {
	a := []int{1, 2, 3, 4}
	P("first", a)
	b := append(a, 4, 5, 6)
	a = append(a, 1, 2)
	P("second a", a)
	P("second b", b)

	s3 := S{}

	s1 := newS()
	s2 := CreateS()

	n1 := 1
	n2 := 2
	n3 := 3

	fmt.Printf("%p, %p, %p\n", s1, s2, &s3)
	fmt.Printf("n=== %p, %p, %p\n", &n1, &n2, &n3)
}
