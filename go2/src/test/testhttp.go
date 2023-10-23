package test

import (
	"fmt"
	"io/ioutil"
	"net/http"
)

func TestHttp() {
	fmt.Println("Test Http!")
	resp, err := http.Get("http://httpbin.org/get")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	fmt.Println("Body:" + string(body))
	fmt.Printf("status: %d\n", (resp.StatusCode))
	if resp.StatusCode == 200 {
		fmt.Println("ok")
	}
}
