package test

import (
	"fmt"
	"time"
)

func t() (int, int) {
	return 1, 2
}

func k(a int, b int) int {
	return a + b
}

type aaaa struct {
	Aaa int
	Bbb int
	Ccc int
	Ddd int
}

func TestParam() {
	kkk := k(t())
	fmt.Printf("%d", kkk)

	aa := aaaa{1, 2, 3, 4}
	bb := aaaa{5, 6, 7, 7}
	cc := &aa
	bb = aa
	cc.Aaa = 10
	cc.Bbb = 11
	cc.Ccc = 12
	cc.Ddd = 14

	t := time.Now().Unix()

	fmt.Printf("aa: %+v\n", aa)
	fmt.Printf("bb: %+v\n", bb)
	fmt.Printf("cc: %+v\n", cc)
	fmt.Printf("time: %d\n", t)
}
