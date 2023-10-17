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

	dt1, dt2 := utils.GetDateTime("2019-12-31")
	fmt.Printf("%d, %d\n", dt1, dt2)

}
