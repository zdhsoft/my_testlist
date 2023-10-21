package test

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
)

func TestMD5() {
	data := "hello world,test MD5"
	hash := md5.New()
	hash.Write([]byte(data))
	md5binary := hash.Sum(nil)
	md5str := hex.EncodeToString(md5binary)
	fmt.Println("aaaa:" + md5str)

	hash2 := md5.New()
	md5binary2 := hash2.Sum([]byte(data))
	md5str2 := hex.EncodeToString(md5binary2[:])
	fmt.Printf("cccc:%s len:%d, len2:%d\n", md5str2, len(md5binary), len(md5binary2))

	data1 := "hello world,"
	data2 := "test MD5"
	hash1 := md5.New()
	hash1.Write([]byte(data1))
	hash1.Write([]byte(data2))
	md5binary1 := hash1.Sum(nil)
	md5str1 := hex.EncodeToString(md5binary1)
	fmt.Println("bbbb:" + md5str1)
}
