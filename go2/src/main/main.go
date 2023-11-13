package main

import (
	"fmt"
	"go2/src/common"
	"go2/src/test"
	xxxyyy "go2/src/utils"
	"hash/crc32"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"
	"time"

	"github.com/labstack/echo"
)

const (
	TokenFlag = "qiuliao"
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

// 链接字符串
func StringCat(paramBuilder *strings.Builder, paramArgs ...string) *strings.Builder {
	var builder *strings.Builder
	if paramBuilder == nil {
		builder = &strings.Builder{}
	} else {
		builder = paramBuilder
	}
	builder.Grow(builder.Len() + 128)
	for _, s := range paramArgs {
		builder.WriteString(s)
	}
	return builder
}

func ttt() string {
	now := time.Now().Unix()
	cnt := "9999"
	uu := "234556788887777"
	strNow := strconv.FormatInt(now, 36)
	builder := StringCat(nil, TokenFlag, strNow, "-", cnt, "-", "88888", "-", uu, "-", "7777777")
	crcValue := crc32.ChecksumIEEE([]byte(builder.String()))
	StringCat(builder, "-", strconv.FormatInt(int64(crcValue), 10))
	fullValue := builder.String()
	r := fullValue[len(TokenFlag):]
	fmt.Println(fullValue)
	fmt.Println(r)
	fmt.Printf("f:%p -> r:%p  -> %d", &fullValue, &r, len(TokenFlag))
	return r
}

func main() {

	s := " 1 23 45678    90 "
	fmt.Printf("----------------[%s]\n", strings.TrimSpace(s))

	ttt()
	test.TestMapJSON()

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
}

func testEcho() {
	e := echo.New()
	e.GET("/", func(c echo.Context) error {
		return c.String(http.StatusOK, "Hello, World!")
	})
	e.Logger.Fatal(e.Start(":1323"))
}
