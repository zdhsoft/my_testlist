package main

import "fmt" // 导入内置 fmt 包

func main() { // main函数，是程序执行的入口
	var outstr string = "Hello World! by outstr!"
	b := "aaaa"
	fmt.Println(outstr) // 在终端打印 Hello World!
	fmt.Println(b)
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
