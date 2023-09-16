package main

import (
	"fmt"
	"go2/src/common"
	xxxyyy "go2/src/utils"
)

func main() {
	fmt.Println("hello world", common.PI, common.PINAME, common.T, common.GetT())
	x := xxxyyy.Xxx{}
	c := x.Calc(1, 2)
	fmt.Println(c)
}
