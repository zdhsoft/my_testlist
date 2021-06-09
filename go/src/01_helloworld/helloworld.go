package main

import "fmt" // 导入内置 fmt 包

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
