package main

import (
	"fmt"
	"go2/src/common"
	// "go2/src/utils"
	xxxyyy "go2/src/utils"
	"log"
	"net/http"
	"os"

	"github.com/labstack/echo"
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
	// utils.BuildXlsx()
	// dir, err := os.Getwd()
	// fmt.Println("在mac下运行了！pwd:="+dir, err)
	// test.TestJson2()
	// test.TestParam()
	// // testhttp.TestHttp()
	// test.TestDT()
	// test.TestFor()
	// test.TestIsIn()
	// test.TestMD5()
	// test.TestSHA256()
	// test.TestHttp()
	// test.TestCommonRet()
	// test.TestRandList()

	// 准备学习纤程

	// test.TestRedis()
	// // search.Run("president")
	// // test.TestPoint()
	// // test.TestJson()
	// // testPackage()
	// // str, now := common.TimeToStr()
	// // fmt.Println("st := " + str, now)

	// for i := 0; i < 100; i++ {
	// 	fmt.Println(i, common.CreateToken())
	// }

	maxCnt := 0
	// s := []int{1,2,3,4,5}
	s := []int{}
	cnt := len(s)

	if cnt > maxCnt {
		cnt = maxCnt
	}
	s = s[:cnt]

	fmt.Println(s)
}

func testEcho() {
	e := echo.New()
	e.GET("/", func(c echo.Context) error {
		return c.String(http.StatusOK, "Hello, World!")
	})
	e.Logger.Fatal(e.Start(":1323"))
}
