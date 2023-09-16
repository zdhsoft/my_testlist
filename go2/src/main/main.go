package main

import (
	"fmt"
	"go2/src/common"
	test "go2/src/test"
	xxxyyy "go2/src/utils"
)

func testPackage() {
	fmt.Println("hello world", common.PI, common.PINAME, common.T, common.GetT())
	x := xxxyyy.Xxx{}
	c := x.Calc(1, 2)
	fmt.Println(c)
}

func main() {
	// test.TestPoint()
	test.TestJson()
}
