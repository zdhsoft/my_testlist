package utils

import (
	"time"
)

const (
	MILLIS_BY_SECOND = 1000
	MILLIS_BY_MINUTE = 60 * MILLIS_BY_SECOND
	MILLIS_BY_HOUR   = 60 * MILLIS_BY_MINUTE
	MILLIS_BY_DAY    = MILLIS_BY_HOUR * 24
	// 北京时间时区
	TIMEZONE_BEIJING = -8
	// 北京时区的毫秒数
	MILLIS_BY_TIMEZONE_BEIJING = TIMEZONE_BEIJING * MILLIS_BY_HOUR
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
	// fmt.Println("init datetime...")
}

// 取北京时区
func GetBeijingTimezone() int {
	return TIMEZONE_BEIJING
}

// 将时间变成北京时间戳
func (t *TDateTime) ToBeijing() *TDateTime {
	st := TDateTime{dt_timestamp: t.dt_timestamp, dt_type: t.dt_type}
	if st.IsUTC() {
		st.dt_timestamp -= MILLIS_BY_TIMEZONE_BEIJING
		st.dt_type = DT_TYPE_BEIJING
	}
	return &st
}

// 将自己变成北京时间戳
func (t *TDateTime) SelfToBeijing() *TDateTime {
	if t.IsUTC() {
		t.dt_timestamp -= MILLIS_BY_TIMEZONE_BEIJING
		t.dt_type = DT_TYPE_UTC
	}
	return t
}

// 变成UTC时间戳
func (t *TDateTime) ToUTC() *TDateTime {
	st := TDateTime{dt_timestamp: t.dt_timestamp, dt_type: t.dt_type}
	if st.IsBeijing() {
		st.dt_timestamp += MILLIS_BY_TIMEZONE_BEIJING
		st.dt_type = DT_TYPE_UTC
	}
	return &st
}

// 将自己变成UTC时间戳
func (t *TDateTime) SelfToUTC() *TDateTime {
	if t.IsBeijing() {
		t.dt_timestamp += MILLIS_BY_TIMEZONE_BEIJING
		t.dt_type = DT_TYPE_UTC
	}
	return t
}

// 取对应北京0点的utc时间戳
func (t *TDateTime) GetBeijingZeroTime() *TDateTime {
	st := t.ToBeijing()
	st.dt_timestamp -= st.dt_timestamp % MILLIS_BY_DAY
	return st.ToUTC()
}

// 取当前时间的时间戳
func (t *TDateTime) GetTimestamp() int64 {
	return t.dt_timestamp
}

// 取当前时间的类型
func (t *TDateTime) GetType() int8 {
	return t.dt_type
}

// 生成当前时间的时间对象
func MakeDateTime() *TDateTime {
	st := TDateTime{dt_timestamp: time.Now().UnixMilli(), dt_type: DT_TYPE_UTC}
	return &st
}

// 生成北京时间的时间对象
func MakeBeijingDateTime() *TDateTime {
	st := TDateTime{dt_timestamp: time.Now().UnixMilli(), dt_type: DT_TYPE_UTC}
	return st.SelfToBeijing()
}

// 取当前时间戳(毫秒)
func GetNowMillis() int64 {
	return time.Now().UnixMilli()
}

// 取当前时间戳(秒）
func GetNowSecond() int64 {
	return time.Now().Unix()
}
