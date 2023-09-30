package common

import (
	"fmt"
	"time"
)

const (
	PI     = 3.1415926
	PINAME = "pi"
	t      = 1999
	T      = 2000
)

func GetT() int {
	return t
}

func GetTime() (int64, int64) {
	dateTimeStr := "2023-01-01 00:00:00 +0800 CST"
	//  t, err := time.Parse("2006-01-02 15:04:05 -0700 CST", dateTimeStr)
	date := time.Date(2023, time.July, 19, 0, 0, 0, 0, time.UTC)
	t, err := time.Parse("2006-01-02 15:04:05 -0700 CST", dateTimeStr)

	if err != nil {
		fmt.Println("aaaaa", err)
	}

	// 获取时间戳（秒）
	timestamp := date.Unix()

	return timestamp, t.Unix()

	// 输出时间戳
	// fmt.Println(timestamp)
}
