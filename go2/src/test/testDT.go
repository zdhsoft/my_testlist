package test

import (
	"fmt"
	"go2/src/utils"
	"strings"
	"time"
)

func err(e error) string {
	if e == nil {
		return "nil"
	} else {
		return e.Error()
	}
}

func GetTimeFormat(timestam int64) string {
	// timestam = (timestam - timestam%1000) / 1000
	fTime := time.Unix(timestam, 0).Format("2006-01-02 15:04:05")
	fTimeArry := strings.Split(fTime, " ")
	if len(fTimeArry) >= 2 {
		fTime = strings.ReplaceAll(fTimeArry[0], "-", "")
	}
	return fTime
}

func TestDT() {

	stUTC := utils.MakeDateTime()
	stBeijing := utils.MakeBeijingDateTime()

	fmt.Printf("utc:%d, beijing:%d, beijing zero:%d\n", stUTC.GetTimestamp(), stBeijing.GetTimestamp(), stUTC.GetBeijingZeroTime().GetTimestamp())
	fmt.Printf("%d, %d\n", utils.GetNowMillis(), utils.GetNowSecond())

	dt1, err1 := utils.ParseDateTimeForBegin("2021-12-31")
	dt2, err2 := utils.ParseDateTimeForBegin("2019-1-1")
	dt3, err3 := utils.ParseDateTimeForBegin("2019-10-01")
	dt4, err4 := utils.ParseDateTimeForBegin("2019-1-10")
	dt5, err5 := utils.ParseDateTimeForBegin("2019-1-101")

	fmt.Printf("1: %d, %s, %s\n", dt1, err(err1), GetTimeFormat(1697472000))
	fmt.Printf("2: %d, %s, %s\n", dt2, err(err2), GetTimeFormat(1697472000))
	fmt.Printf("3: %d, %s\n", dt3, err(err3))
	fmt.Printf("4: %d, %s\n", dt4, err(err4))
	fmt.Printf("5: %d, %s\n", dt5, err(err5))

}

func TestFor() {
	s := "Hello"
	for i, v := range s {
		fmt.Printf("index: %d, value:%c \n", i, v)
	}
}
