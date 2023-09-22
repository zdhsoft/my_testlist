package main

import (
	"fmt" // 导入内置 fmt 包
	"strconv"
	"strings"
	"sync"
	"time"
)

type TabInfo struct {
	// *
	// @description tab的名称
	// @example 足球
	Name string `protobuf:"bytes,1,opt,name=name,proto3" json:"name,omitempty"`
	// *
	// @description tab对应的列表类型
	// @example football
	Type string `protobuf:"bytes,2,opt,name=type,proto3" json:"type,omitempty"`
	// *
	// @description 图标
	// @example https://...../icon.png
	Icon string `protobuf:"bytes,3,opt,name=icon,proto3" json:"icon,omitempty"`
}

func main_test() { // main函数，是程序执行的入口
	var outstr string = "Hello World! by outstr!"
	b := "aaaa"
	fmt.Println(outstr) // 在终端打印 Hello World!
	fmt.Println(b)

	ten := 10
	if ten > 10 {
		fmt.Println(" > 10 very good!")
	} else {
		fmt.Println(" <= 10")
	}

	if seven := 7; seven < 10 {
		fmt.Println("is < 10 nice!!!")
	} else {
		fmt.Println("is not nice!!!!!>>>>>>>")
	}

	for i := 0; i < 10; i++ {
		fmt.Println(i)
	}

	i := 1
	for {
		if i < 10 {
			fmt.Println("nice:", i)
		} else {
			fmt.Println("not nice", i)
		}

		i++
		if i > 20 {
			fmt.Println("bye bye!")
			break
		}
	}

	ttt := TabInfo{Name: "1", Type: "football", Icon: "这既是icon"}
	fmt.Println(ttt)

	x := []TabInfo{{"1", "2", "3"}, {"2", "3", "4"}}
	// x := append(x, []TabInfo{"4", "5", "6"})

	fmt.Println(x, len(x))
	for i := 0; i < len(x); i++ {
		fmt.Println(x[i])
	}

}

// Go语言的基本类型有：
// bool
// string
// int、int8、int16、int32、int64
// uint、uint8、uint16、uint32、uint64、uintptr
// byte // uint8 的别名
// rune // int32 的别名 代表一个 Unicode 码
// float32、float64
// complex64、complex128

func main() {
	// main_test()
	testjson()
	// testGo()
	testArray()
	testStringBuffer()
}

/**
 * @param name string  任务名称
 * @param cnt int 执行次数
 */
func task(name string, cnt int) {
	for i := 0; i < cnt; i++ {
		fmt.Println(name+":", i)
		time.Sleep(500 * time.Millisecond)
	}
	fmt.Println(name + " done")
}

type P1 struct {
	Name string
	Age  int
	Sex  bool
}

type P2 struct {
	Name  string
	Age   int
	Money int
}

type P3 struct {
	P1
	P2
}

func testArray() {
	var k = []int{11, 12, 13, 14, 15, 1, 2, 3, 4}
	for m, v := range k {
		fmt.Println(m, v)
	}
}

func testStringBuffer() {
	var buff strings.Builder

	buff.WriteString("aaaa")
	buff.WriteString(strconv.Itoa(1))
	buff.WriteString(strconv.Itoa(99))
	fmt.Println(buff.String())

	s := fmt.Sprintf(">>>>%s%d%d", "aaaa", 1, 99)
	fmt.Println(s)

}

func testGo() {
	var wg sync.WaitGroup
	wg.Add(3)

	go func() {
		defer wg.Done()
		task("task 1>>>", 10)
	}()
	go func() {
		defer wg.Done()
		task("task 2>>>", 15)
	}()
	go func() {
		defer wg.Done()
		task("task 3>>>", 20)
	}()

	wg.Wait()
	fmt.Println(" all task is finish!")
}
