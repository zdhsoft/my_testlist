package httputils

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	ret "go2/src/core/comm"
	"io"
	"net/http"
)

const (
	HTTP_METHOD_POST = "POST"
	HTTP_METHOD_GET  = "GET"
	HTTP_STATUS_OK   = 200
)

type HttpHeaderKeyValue struct {
	K string
	V string
}
type HttpOptions struct {
	Headers map[string]string
}

func NewOptions() *HttpOptions {
	return &HttpOptions{Headers: map[string]string{}}
}

func isHttpOk(paramCode int) bool {
	return paramCode >= 200 && paramCode < 300
}

func JsonPost(ctx context.Context, paramURL string, paramMsgBody interface{}, paramOptions *HttpOptions) *ret.CommonRet[any] {
	r := ret.CommonRet[any]{}

	for range [1]int{} {
		client := &http.Client{}
		bytesData, err := json.Marshal(paramMsgBody)
		if err != nil {
			r.SetError(-1, "消息体:MsgBody => JSON 失败:"+err.Error())
			break
		}
		req, err := http.NewRequestWithContext(ctx, HTTP_METHOD_POST, paramURL, bytes.NewReader(bytesData))
		if err != nil {
			r.SetError(-2, "创建请求失败:"+err.Error())
			break
		}
		paramOptions.Headers["Content-Type"] = "application/json"
		for k, v := range paramOptions.Headers {
			req.Header.Add(k, v)
		}

		resp, err := client.Do(req)
		if err != nil {
			r.SetError(-3, "执行请求失败:"+err.Error())
			break
		}

		if !isHttpOk(resp.StatusCode) {
			r.SetError(-5, "响应状态码："+fmt.Sprintf("%d", resp.StatusCode))
			break
		}
		body, err := io.ReadAll(resp.Body)
		if err != nil {
			r.SetError(-4, "读取数据错误"+err.Error())
			break
		}

		fmt.Println(string(body))
	}
	return &r
}
