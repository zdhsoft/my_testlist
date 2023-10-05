package main

import (
	"fmt"
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
	dir, err := os.Getwd()
	fmt.Println("pwd:="+dir, err)
	// search.Run("president")
	// test.TestPoint()
	// test.TestJson()
	// testPackage()
	// str, now := common.TimeToStr()
	// fmt.Println("st := " + str, now)

	for i := 0; i < 100; i++ {
		fmt.Println(i, common.CreateToken())
	}
}
