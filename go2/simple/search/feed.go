package search

import (
	"encoding/json"
	"os"
)

const dataFile = "../../simple/data/data.json"

type Feed struct {
	Name string `json:"site"`
	URI  string `json:"link"`
	Type string `json:"type"`
}

func RetrieveFeeds() ([]*Feed, error) {
	file, err := os.Open(dataFile)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var feeds []*Feed
	err = json.NewDecoder(file).Decode(&feeds)
	if err != nil {
		return nil, err
	} else {
		return feeds, nil
	}
}
