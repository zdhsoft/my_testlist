package test

import (
	"fmt"
	ret "go2/src/core/comm"
)

func TestCommonRet() {
	r1 := ret.CommonRet[int]{}
	r2 := ret.CommonRet[string]{}

	r2.SetFail(9999, "这是一个错误")
	r1.AssignErrorFrom(&r2)

	fmt.Printf("%d, %s", r1.GetRet(), r1.GetMsg())

}
