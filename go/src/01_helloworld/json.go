package main

import (
	"encoding/json"
)

func score2Array(scores string) {

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

func testjson() {
	// var s = "[1,2,3,4,5,6]"
	// var h = "[2,4,5,6,7,3]"
	// var n []int32
	// err := json.Unmarshal([]byte(s), &n)

	// fmt.Println(err, n, s)
}
