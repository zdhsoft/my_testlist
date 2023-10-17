package test

import (
	"fmt"
	"go2/src/utils"
)

func TestDT() {

	stUTC := utils.MakeDateTime()
	stBeijing := utils.MakeBeijingDateTime()

	fmt.Printf("utc:%d, beijing:%d, beijing zero:%d\n", stUTC.GetTimestamp(), stBeijing.GetTimestamp(), stUTC.GetBeijingZeroTime().GetTimestamp())
	fmt.Printf("%d, %d\n", utils.GetNowMillis(), utils.GetNowSecond())

}
