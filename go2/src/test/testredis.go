package test

import (
	"context"
	"encoding/json"
	"fmt"
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

func RedisGet(key string) *redis.StringCmd {
	return cli.Get(context.Background(), key)
	// val, err := cli.Get(context.Background(), key).Result()
	// if err != nil {
	// 	return "", err
	// }
	// return val, nil
}

func RedisDel(key string) error {
	err := cli.Del(context.Background(), key).Err()
	if err != nil {
		return err
	}
	return nil
}

type kkk struct {
	Key   string `json:"key"`
	Value string `json:"value"`
	Age   int    `json:"age"`
}

type yyy struct {
	kkk
	MM  string   `json:"mm"`
	Yes bool     `json:"yes"`
	RR  []string `json:"rr"`
}

func (g *yyy) MarshalBinary() (data []byte, err error) {
	return json.Marshal(g)
}

func (g *yyy) UnmarshalBinary(data []byte) (err error) {
	return json.Unmarshal(data, g)
}

func (g *kkk) MarshalBinary() (data []byte, err error) {
	return json.Marshal(g)
}

func (g *kkk) UnmarshalBinary(data []byte) (err error) {
	return json.Unmarshal(data, g)
}

func TestRedis() {
	k := &kkk{Key: "key~~~", Value: "value~~~", Age: 10}

	j := &yyy{}
	err := RedisSet("key", k, time.Second*1000)
	if err != nil {
		panic(err)
	}
	cmd := RedisGet("key~~")
	if cmd.Err() != nil {
		fmt.Println("error:", cmd.Err().Error())
		return
		// panic(cmd.Err())
	}

	j.RR = append(j.RR, "1", "2", "3")

	fmt.Printf("%+v\n", j)
	fmt.Println("===", j)
	s := fmt.Sprintf("%+v", j)
	fmt.Println("s === sprintf:", s)
	jsonData, err := json.MarshalIndent(j, "", "    ")
	if err == nil {
		fmt.Println("JSON:", string(jsonData))
	}
	// fmt.Println("aaaaa", json.Marshal(*j))
	// if val != "value" {
	// 	panic("get value error")
	// }
	// err = RedisDel("key")
	// if err != nil {
	// 	panic(err)
	// }
	// val, err = RedisGet("key")
	// if err == nil || val != "" {
	// 	panic("get value error")
	// }
	fmt.Println("aaaaa")
}
