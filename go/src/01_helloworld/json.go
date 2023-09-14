package main

import (
	"encoding/json"
	"fmt"
	"strconv"
)

type Live struct {
	age   int32
	name  string
	score int32
}

type Live1 struct {
	age   int32
	name  int32
	score string
}

func b2b(src []*Live) []*Live1 {
	b := []*Live1{}
	i := 0
	for i = 0; i < len(src); i++ {
		v := src[i]
		k := Live1{}
		k.age = v.age
		k.name = v.score
		k.score = v.name + ":" + strconv.Itoa((int)(v.score))
		b = append(b, &k)
	}
	return b
}

func utils_football_score(home_scores string, away_scores string) (error, []int32, []int32) {
	var h, a []int32
	errhome := json.Unmarshal([]byte(home_scores), &h)
	if errhome != nil {
		return errhome, h, a
	}

	erraway := json.Unmarshal([]byte(away_scores), &a)
	if erraway != nil {
		return erraway, h, a
	}

	return nil, h, a
}

func to() {
	lives := []*Live{} // 创建一个空的Live数组

	// 添加示例元素
	lives = append(lives, &Live{age: 25, name: "Alice", score: 80})
	lives = append(lives, &Live{age: 30, name: "Bob", score: 90})
	lives = append(lives, &Live{age: 35, name: "Charlie", score: 85})

	k := b2b(lives)

	for _, l := range lives {
		fmt.Printf("Age: %d, Name: %s, Score: %d\n", l.age, l.name, l.score)
	}

	for _, l := range k {
		fmt.Printf(">> Age: %d, Name: %d, Score: %s\n", l.age, l.name, l.score)
	}
}

func testjson() {

	to()
	// var s = "[1,2,3,4,5,6]"
	// var h = "[2,4,5,6,7,3]"
	// var n []int32
	// err := json.Unmarshal([]byte(s), &n)

	// fmt.Println(err, n, s)
}
