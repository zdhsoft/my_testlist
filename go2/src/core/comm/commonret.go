package ret

import (
	ErrorCode "go2/src/core/const/errorcode"
	"strconv"
)

type IRet interface {
	GetRet() int
	GetMsg() string
	IsOK() bool
	IsNotOK() bool
}

// CommonRet 通用返回结构
type CommonRet[T any] struct {
	ret  int
	msg  string
	data *T
}

// CommonRetData 通用返回数据结构
type CommonRetData[T any] struct {
	// 返回码
	Ret int `json:"ret"`
	// 返回错误信息
	Msg string `json:"msg"`
	// 返回错误数据
	Data *T `json:"data"`
}

// SetRet 设置返回码
func (r *CommonRet[T]) SetRet(paramRet int) *CommonRet[T] {
	r.ret = paramRet
	return r
}

// GetRet 取返回码
func (r *CommonRet[T]) GetRet() int {
	return r.ret
}

// ToData 返回数据结构
func (r *CommonRet[T]) ToData() *CommonRetData[T] {
	return &CommonRetData[T]{
		Ret:  r.ret,
		Msg:  r.msg,
		Data: r.data,
	}
}

// GetRetStr 取返回码字符串值
func (r *CommonRet[T]) GetRetStr() string {
	return strconv.Itoa(r.ret)
}

// SetMsg 设置错误信息
func (r *CommonRet[T]) SetMsg(paramMsg string) *CommonRet[T] {
	r.msg = paramMsg
	return r
}

// GetMsg 取错误信息
func (r *CommonRet[T]) GetMsg() string {
	return r.msg
}

// SetError 设置错误
func (r *CommonRet[T]) SetError(paramRet int, paramMsg string) *CommonRet[T] {
	r.ret = paramRet
	r.msg = paramMsg
	return r
}

// GetError 取Error信息
func (r *CommonRet[T]) GetError() (int, string) {
	return r.ret, r.msg
}

// SetOK 设置成功
func (r *CommonRet[T]) SetOK(paramData *T) *CommonRet[T] {
	r.ret = ErrorCode.ErrOK
	r.msg = ""
	r.data = paramData
	return r
}

// 设置失败
func (r *CommonRet[T]) SetFail(paramRet int, paramMsg string) *CommonRet[T] {
	r.ret = paramRet
	r.msg = paramMsg
	r.data = nil
	return r
}

// SetData 设置返回数据
func (r *CommonRet[T]) SetData(paramData *T) *CommonRet[T] {
	r.data = paramData
	return r
}

// GetData 取返回数据
func (r *CommonRet[T]) GetData() *T {
	return r.data
}

// IsOK 判断是否成功
func (r *CommonRet[T]) IsOK() bool {
	return r.ret == ErrorCode.ErrOK
}

// IsNotOK 判断是否成功
func (r *CommonRet[T]) IsNotOK() bool {
	return !r.IsOK()
}

// Reset 重置数据
func (r *CommonRet[T]) Reset() {
	r.ret = ErrorCode.ErrOK
	r.msg = ""
	r.data = nil
}

// AssignFrom 从另一个ret赋值
func (r *CommonRet[T]) AssignFrom(paramR *CommonRet[T]) *CommonRet[T] {
	r.ret = paramR.ret
	r.msg = paramR.msg
	r.data = paramR.data
	return r
}

// AssignErrorFrom 复制错误信息
func (r *CommonRet[T]) AssignErrorFrom(paramR IRet) *CommonRet[T] {
	r.ret = paramR.GetRet()
	r.msg = paramR.GetMsg()
	return r
}

// ToRetNoData 返回无数据的一个整数的Common
func (r *CommonRet[T]) ToRetNoData() *CommonRet[int] {
	rrr := &CommonRet[int]{}
	rrr.ret = r.ret
	rrr.msg = r.msg
	return rrr
}
