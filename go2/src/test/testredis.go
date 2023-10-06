package test

import (
	"context"
	"fmt"
	"testing"
	"time"

	"github.com/go-redis/redis/v8"
)

var (
	cli *redis.Client
)

func init() {
	cli = redis.NewClient(&redis.Options{
		Addr: "127.0.0.1:6379",
		DB:   9,
	})
}

func RedisSet(key string, value interface{}, ttl time.Duration) error {
	err := cli.Set(context.Background(), key, value, ttl).Err()
	if err != nil {
		return err
	}
	return nil
}

func RedisGet(key string) (string, error) {
	val, err := cli.Get(context.Background(), key).Result()
	if err != nil {
		return "", err
	}
	return val, nil
}

func RedisDel(key string) error {
	err := cli.Del(context.Background(), key).Err()
	if err != nil {
		return err
	}
	return nil
}

func TestRedis() {
	fmt.Println("aaaaa")
}
