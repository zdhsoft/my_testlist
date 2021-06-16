package main
import (
	"fmt"
	"os"
) // 导入内置 fmt 包

func main() { // main函数，是程序执行的入口
	fmt.Println("Hello World!") // 在终端打印 Hello World!
	printArgs();
}

// 打印命令行传入的参数
func printArgs() {
	fmt.Println("--------");
	var s, sep string;
	for i:=1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
	fmt.Println(s)
	s = ""
	sep = ""
	for _, arg := range os.Args[1:] {
		s += sep + arg
		sep = " "
	}
	fmt.Println(s);

}