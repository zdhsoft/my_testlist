package utils

import (
	"fmt"
)

const (
	MILLIS_BY_SECOND = 1000
	MILLIS_BY_MINUTE = 60 * MILLIS_BY_SECOND
	MILLIS_BY_HOUR   = 60 * MILLIS_BY_MINUTE
	MILLIS_BY_DAY    = MILLIS_BY_HOUR * 24
	// 北京时间时区
	TIMEZONE = 8

	MILLIS_BY_TIMEZONE = TIMEZONE * MILLIS_BY_HOUR
	// DateTime类型 格林威治时间
	DT_TYPE_UTC = 0
	// DateTime类型 北京时间
	DT_TYPE_BEIJING = 8
)

var ()

// 日期时间
type TDateTime struct {
	// 时间戳 单位毫秒
	Timestamp int64
	// 类型
	Type int8
}

// 是否是格林威治时间
func (t *TDateTime) IsUTC() bool {
	return t.Type == DT_TYPE_UTC
}

// 是否是北京时间
func (t *TDateTime) IsBeijing() bool {
	return t.Type == DT_TYPE_BEIJING
}

func init() {
	fmt.Println("init datetime...")
}

func GetTimezone() int {
	return TIMEZONE
}
