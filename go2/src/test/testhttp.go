package test

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
)

// 参考blog: https://www.cnblogs.com/zhaof/p/11346412.html
func testJSON() {
	client := &http.Client{}
	// data := make(map[string]interface{})
	type s struct {
		Name  string `json:"name"`
		Age   int    `json:"age"`
		Email string `json:"email"`
	}
	// data["name"] = "zhaofan"
	// data["age"] = "23"

	data := s{Name: "zhaofan", Age: 1999, Email: "test@163.com"}
	bytesData, _ := json.Marshal(data)
	req, _ := http.NewRequest("POST", "http://httpbin.org/post", bytes.NewReader(bytesData))
	resp, _ := client.Do(req)
	body, _ := io.ReadAll(resp.Body)
	fmt.Println(string(body))
}

func TestHttp() {
	fmt.Println("Test Http!")
	resp, err := http.Get("http://httpbin.org/get")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	fmt.Println("Body:" + string(body))
	fmt.Printf("status: %d\n", (resp.StatusCode))
	if resp.StatusCode == 200 {
		fmt.Println("ok")
	}

	testJSON()
	testdirect()

}

func testdirect() {
	data := make(map[string]interface{})
	data["name"] = "zhaofan"
	data["age"] = "23"
	bytesData, _ := json.Marshal(data)
	resp, _ := http.Post("http://httpbin.org/post", "application/json", bytes.NewReader(bytesData))
	body, _ := io.ReadAll(resp.Body)
	fmt.Println(string(body))
}
