package cache

import "errors"

type cachedata struct {
	dt   int64
	data *interface{}
}

var (
	caches map[string]cachedata
)

func init() {
	caches = map[string]cachedata{}
}

func SetKey(paramKey string, data interface{}) {
	caches[paramKey] = cachedata{
		dt:   0,
		data: &data,
	}
}

func GetKey(paramKey string) (*interface{}, error) {
	d, ok := caches[paramKey]
	if ok {
		return d.data, nil
	} else {
		return nil, errors.New("没有找到")
	}
}

func KValue[T interface{}](paramKey string) (*T, error) {
	d, err := GetKey(paramKey)
	if err != nil {
		return nil, err
	}

	t, ok := (*d).(T)
	if ok {
		return &t, nil
	} else {
		return nil, errors.New("aaaaa")
	}
}
