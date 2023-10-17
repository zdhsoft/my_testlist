package test

import (
	"fmt"
	"go2/src/utils"
)

func TestDT() {

	stUTC := utils.MakeDateTime()
	stBeijing := utils.MakeBeijingDateTime()

	fmt.Printf("utc:%d, beijing:%d", stUTC.GetTimestamp(), stBeijing.GetTimestamp())

}
