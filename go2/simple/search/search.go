package search

import (
	"go2/simple/matchers"
	"log"
	"sync"
)

func Run(name string) {
	//
	feeds, err := RetrieveFeeds()
	if err != nil {
		log.Fatal(err)
	}

	results := make(clan * Result)
	var waitGroup sync.WaitGroup

	waitGroup.Add(len(feeds))
	for _, feed := range feeds {
		matcher, exists:= matchers[feed.Type]
		if !exists {
			matcher = matchers["default"]
			
		}

	}
}
