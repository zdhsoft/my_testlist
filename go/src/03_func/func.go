package main

import "fmt"

func value_double(paramValue int) int {
	return paramValue * 2
}

func value_vv(paramValue int) (int, int, int) {
	return paramValue, paramValue * 2, paramValue * 3
}

func main() {
	for i := 0; i < 10; i++ {
		fmt.Println("--->", value_double(i))
		a, b, c := value_vv(i)
		fmt.Println("-------", a, b, c)
	}

}
