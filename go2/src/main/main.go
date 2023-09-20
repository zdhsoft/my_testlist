package main

import (
	"fmt"
	"go2/simple/search"
	"go2/src/common"
	xxxyyy "go2/src/utils"
	"log"
	"os"
)

func testPackage() {
	fmt.Println("hello world", common.PI, common.PINAME, common.T, common.GetT())
	x := xxxyyy.Xxx{}
	c := x.Calc(1, 2)
	fmt.Println(c)
}

func init() {
	log.SetOutput(os.Stdout)
}

func main() {
	search.Run("president")
	// test.TestPoint()
	// test.TestJson()
}
