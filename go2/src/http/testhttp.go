package testhttp

import (
	"fmt"
	"net/http"
)

func TestHttp() {
	fmt.Println("hello test Http!")

	resp, err := http.Get("https://www.baidu.com/")
	errmsg := ""
	if err != nil {
		errmsg = err.Error()
	}

	fmt.Printf("resp:%+v\n, err:%s", resp, errmsg)
}
