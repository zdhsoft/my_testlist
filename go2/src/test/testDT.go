package test

import (
	"fmt"
	"go2/src/utils"
	"strings"
	"time"
)

func err(e error) string {
	if e == nil {
		return "nil"
	} else {
		return e.Error()
	}
}

func GetTimeFormat(timestam int64) string {
	// timestam = (timestam - timestam%1000) / 1000
	fTime := time.Unix(timestam, 0).Format("2006-01-02 15:04:05")
	fTimeArry := strings.Split(fTime, " ")
	if len(fTimeArry) >= 2 {
		fTime = strings.ReplaceAll(fTimeArry[0], "-", "")
	}
	return fTime
}

func TestDT() {

	stUTC := utils.MakeDateTime()
	stBeijing := utils.MakeBeijingDateTime()

	fmt.Printf("utc:%d, beijing:%d, beijing zero:%d\n", stUTC.GetTimestamp(), stBeijing.GetTimestamp(), stUTC.GetBeijingZeroTime().GetTimestamp())
	fmt.Printf("%d, %d\n", utils.GetNowMillis(), utils.GetNowSecond())

	dt1, err1 := utils.ParseDateTimeForBegin("2021-12-31")
	dt2, err2 := utils.ParseDateTimeForBegin("2019-1-1")
	dt3, err3 := utils.ParseDateTimeForBegin("2019-10-01")
	dt4, err4 := utils.ParseDateTimeForBegin("2019-1-10")
	dt5, err5 := utils.ParseDateTimeForBegin("2019-1-101")

	fmt.Printf("1: %d, %s, %s\n", dt1, err(err1), GetTimeFormat(1697472000))
	fmt.Printf("2: %d, %s, %s\n", dt2, err(err2), GetTimeFormat(1697472000))
	fmt.Printf("3: %d, %s\n", dt3, err(err3))
	fmt.Printf("4: %d, %s\n", dt4, err(err4))
	fmt.Printf("5: %d, %s\n", dt5, err(err5))

}

func IsInArray[T comparable](paramList []T, paramItem T) bool {
	for _, v := range paramList {
		if paramItem == v {
			return true
		}
	}
	return false
}

// fmt.Printf的格式化定义使用与C语言类似的占位符和格式化规范。以下是一些常用的格式化定义：

// %d 或 %i：整数类型。将参数格式化为十进制整数。
// %f：浮点数类型。将参数格式化为浮点数。
// %s：字符串类型。将参数格式化为字符串。
// %t：布尔类型。将参数格式化为布尔值（true或false）。
// %v：通用类型。将参数按照其实际类型进行格式化。
// %b：二进制表示。将整数格式化为二进制字符串。
// %x 或 %X：十六进制表示。将整数格式化为十六进制字符串（小写或大写字母）。
// %o：八进制表示。将整数格式化为八进制字符串。
// %p：指针表示。将指针格式化为十六进制地址。
// 除了这些基本的占位符外，Go语言还提供了一些格式化规范，用于更详细地控制输出的格式。以下是一些常用的格式化规范：

// %0d 或 %0i：前导零的整数。在输出整数时，使用前导零填充字段宽度。
// %.d 或 %.i：舍入到指定小数位数的整数。在输出整数时，根据指定的位数进行四舍五入。
// %.f：浮点数。在输出浮点数时，根据指定的精度进行四舍五入。
// %-d 或 %-i：左对齐的整数。在输出整数时，使用左对齐方式。
// %_d 或 %_i：使用下划线填充字段宽度和左对齐的整数。
func TestIsIn() {
	i := []int{1, 2, 3, 4, 5, 6, 7, 8}
	t := []int{4, 5, 6, 7, 8, 9, 10, 11}
	for _, ttt := range t {
		r := IsInArray(i, ttt)
		fmt.Printf("%d is in i ? %t\n", ttt, r)
	}
}

func TestFor() {
	s := "Hello"
	for i, v := range s {
		fmt.Printf("index: %d, value:%c \n", i, v)
	}
	s = "有中文会怎样？"
	for i, v := range s {
		fmt.Printf("index: %d, value:%c \n", i, v)
	}

	m := map[string]string{"aaaa": "bbbb", "cccc": "看看看看看", "aaac": "aaaaaaaa", "aaab": "会是最后一个吗？"}
	for k, v := range m {
		fmt.Printf("key=%s, value=%s \n", k, v)
	}
}
