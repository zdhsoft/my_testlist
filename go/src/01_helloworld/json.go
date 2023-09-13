package main

import (
	"encoding/json"
	"fmt"
)

func testjson() {
	var s = "[\"a\",2,3,4,5,6]"
	var 
	var n []int32
	err := json.Unmarshal([]byte(s), &n)

	fmt.Println(err, n, s)
}
