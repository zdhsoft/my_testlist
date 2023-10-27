package test

import (
	"fmt"
	"math/rand"
)

func RandomIntScope(minValue int, maxValue int) int {
	if minValue > maxValue {
		minValue, maxValue = maxValue, minValue
	} else if minValue == maxValue {
		return minValue
	}
	return rand.Intn(maxValue-minValue+1) + minValue
}

func RandList[T int | int32 | int64 | int16](recordCount T, randCount T) *[]T {
	retList := make([]T, 0, randCount)
	flag := T(500)
	if recordCount <= flag {
		idxs := make([]T, recordCount)
		for i := T(0); i < recordCount; i++ {
			idxs[i] = i
		}

		for i := T(0); i < randCount; i++ {
			idx := RandomIntScope(0, len(idxs)-1)
			retList = append(retList, idxs[idx])
			idxs = append(idxs[:idx], idxs[idx+1:]...)
		}
	} else {
		m := make(map[T]T, randCount)
		maxIdx := int(recordCount - 1)
		cnt := T(0)
		maxCount := 2000
		for cnt < randCount && maxCount >= 0 {
			maxCount--
			idx := T(RandomIntScope(0, maxIdx))
			_, ok := m[idx]
			if ok {
				continue
			} else {
				m[idx] = idx
				retList = append(retList, idx)
				cnt++
			}
		}
	}
	return &retList
}

func TestRandList() {
	k := RandList[int](50, 5)
	fmt.Println("dddddd:", *k)
}
