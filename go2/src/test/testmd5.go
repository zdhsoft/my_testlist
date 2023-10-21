package test

import (
	"crypto/md5"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

func TestSHA256() {
	data := "hello world,test Sha256"
	hash := sha256.New()
	hash.Write([]byte(data))
	md5binary := hash.Sum(nil)
	md5str := hex.EncodeToString(md5binary)
	fmt.Println("sha256:aaaa:" + md5str)

	data1 := "hello world,"
	data2 := "test Sha256"
	hash1 := sha256.New()
	hash1.Write([]byte(data1))
	hash1.Write([]byte(data2))
	md5binary1 := hash1.Sum(nil)
	md5str1 := hex.EncodeToString(md5binary1)
	fmt.Println("sha256:bbbb:" + md5str1)
}

func TestMD5() {
	data := "hello world,test MD5"
	hash := md5.New()
	hash.Write([]byte(data))
	md5binary := hash.Sum(nil)
	md5str := hex.EncodeToString(md5binary)
	fmt.Println("aaaa:" + md5str)

	data1 := "hello world,"
	data2 := "test MD5"
	hash1 := md5.New()
	hash1.Write([]byte(data1))
	hash1.Write([]byte(data2))
	md5binary1 := hash1.Sum(nil)
	md5str1 := hex.EncodeToString(md5binary1)
	fmt.Println("bbbb:" + md5str1)
}
