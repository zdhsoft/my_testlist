package main

import "fmt" // 导入内置 fmt 包
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

func main() { // main函数，是程序执行的入口
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

	x := [...]TabInfo{{"1", "2", "3"}, {"2","3","4"}}

	fmt.Println(x, len(x))

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
