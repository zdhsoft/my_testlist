package main

import (
	"fmt"
	"log"
	"net/http"
)

func main() {
	fmt.Println("hello world! this is go3 study!")
	httpMain()
}

func httpMain() {
	http.HandleFunc("/", handler)
	http.HandleFunc("/count", counter)
	log.Fatal(http.ListenAndServe("localhost:8080", nil))

}

func handler(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("hander::URL.Path=%q\n", r.URL.Path)
	fmt.Fprintf(w, "URL.Path=%q\n", r.URL.Path)
}

func counter(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("counter::URL.Path=%q\n", r.URL.Path)
	fmt.Fprintf(w, "URL.Path=%q\n", r.URL.Path)
}
