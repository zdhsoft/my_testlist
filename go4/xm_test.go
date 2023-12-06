package main

import (
	"testing"

	"github.com/zdhsoft/xmutilsgo/xm"
)

func Test_XM(t *testing.T) {
	if xm.Int2String(1000) != "1000" {
		t.Error("xm.Int2String(1000) != 1000")
	}
}
