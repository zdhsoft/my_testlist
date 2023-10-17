package utils

import (
	"fmt"
	"time"
)

const (
	MILLIS_BY_SECOND = 1000
	MILLIS_BY_MINUTE = 60 * MILLIS_BY_SECOND
	MILLIS_BY_HOUR   = 60 * MILLIS_BY_MINUTE
	MILLIS_BY_DAY    = MILLIS_BY_HOUR * 24
	// 北京时间时区
	TIMEZONE = 8
	// 北京时区的毫秒数
	MILLIS_BY_TIMEZONE_BEIJING = TIMEZONE * MILLIS_BY_HOUR
	// DateTime类型 格林威治时间
	DT_TYPE_UTC = 0
	// DateTime类型 北京时间
	DT_TYPE_BEIJING = 8
)

var ()

// 日期时间
type TDateTime struct {
	// 时间戳 单位毫秒
	dt_timestamp int64
	// 类型
	dt_type int8
}

// 是否是格林威治时间
func (t *TDateTime) IsUTC() bool {
	return t.dt_type == DT_TYPE_UTC
}

// 是否是北京时间
func (t *TDateTime) IsBeijing() bool {
	return t.dt_type == DT_TYPE_BEIJING
}

func init() {
	fmt.Println("init datetime...")
}

func GetTimezone() int {
	return TIMEZONE
}

func (t *TDateTime) ToBeijing() *TDateTime {
	st := TDateTime{dt_timestamp: t.dt_timestamp, dt_type: t.dt_type}
	if st.IsUTC() {
		st.dt_timestamp -= MILLIS_BY_TIMEZONE_BEIJING
		st.dt_type = DT_TYPE_BEIJING
	}
	return &st
}

func (t *TDateTime) SelfToBeijing() *TDateTime {
	if t.IsUTC() {
		t.dt_timestamp -= MILLIS_BY_TIMEZONE_BEIJING
		t.dt_type = DT_TYPE_UTC
	}
	return t
}

func (t *TDateTime) ToUTC() *TDateTime {
	st := TDateTime{dt_timestamp: t.dt_timestamp, dt_type: t.dt_type}
	if st.IsBeijing() {
		st.dt_timestamp += MILLIS_BY_TIMEZONE_BEIJING
		st.dt_type = DT_TYPE_UTC
	}
	return &st
}

func (t *TDateTime) SelfToUTC() *TDateTime {
	if t.IsBeijing() {
		t.dt_timestamp += MILLIS_BY_TIMEZONE_BEIJING
		t.dt_type = DT_TYPE_UTC
	}
	return t
}

func (t *TDateTime) GetTimestamp() int64 {
	return t.dt_timestamp
}

func (t *TDateTime) GetType() int8 {
	return t.dt_type
}

func MakeDateTime() *TDateTime {
	st := TDateTime{dt_timestamp: time.Now().UnixMilli(), dt_type: DT_TYPE_UTC}
	return &st
}

func MakeBeijingDateTime() *TDateTime {
	st := TDateTime{dt_timestamp: time.Now().UnixMilli(), dt_type: DT_TYPE_UTC}
	return st.SelfToBeijing()
}
