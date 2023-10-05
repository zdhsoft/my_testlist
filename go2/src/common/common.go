package common

import (
	"fmt"
	"strconv"
	"strings"
	"time"

	"github.com/google/uuid"
)

var (
	// token计数
	tokenCnt int32
	// 最近一次时间戳
	lastTimeStamp int64
)

func init() {
	lastTimeStamp = time.Now().Unix()
	tokenCnt = 0
}

const (
	PI     = 3.1415926
	PINAME = "pi"
	t      = 1999
	T      = 2000
)

func generateUUID() string {
	newUUID := uuid.New()
	return newUUID.String()
	// uuid := make([]byte, 16)
	// _, err := rand.Read(uuid)
	// if err != nil {
	// 	// 处理错误
	// 	fmt.Println(err)
	// 	return ""
	// }

	// // 设置版本和变种
	// uuid[6] = (uuid[6] & 0x0f) | 0x40
	// uuid[8] = (uuid[8] & 0x3f) | 0x80

	// return hex.EncodeToString(uuid)
}

func getTokenCnt(paramNow int64) int32 {
	if paramNow == lastTimeStamp {
		tokenCnt++
		return tokenCnt
	} else {
		lastTimeStamp = paramNow
		tokenCnt = 0
		return tokenCnt
	}
}

func StringPad(paramStr string, paramMaxLen int) string {
	strLen := len(paramStr)
	if strLen < paramMaxLen {
		return strings.Repeat("0", paramMaxLen-strLen) + paramStr
	}
	return paramStr
}

func CreateToken() string {
	now := time.Now().Unix()
	cnt := StringPad(strconv.FormatInt(int64(getTokenCnt(now)), 36), 4)
	uuid := generateUUID()
	strNow := StringPad(strconv.FormatInt(now, 36), 7)
	return strNow + "-" + cnt + "-" + uuid
}

func GetT() int {
	return t
}

func TimeToStr() (string, int64) {
	now := time.Now().Unix()
	str := strconv.FormatInt(int64(now), 36)

	maxLen := 7
	len := len(str)

	if len < maxLen {
		str = strings.Repeat("0", maxLen-len) + str
	}

	return str, int64(now)
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
