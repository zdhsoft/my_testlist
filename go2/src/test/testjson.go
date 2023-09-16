package test

import (
	"encoding/json"
	"fmt"
)

func TestJson() {
	type bannerInfo struct {
		/* pc端图片 */
		// pcUrl string
		/* 手机端图片 */
		PhoneUrl string `json:"phoneUrl"`
	}
	type zbVideoInfo struct {
		/* 主视频 */
		// mainSource string
		/* 转播源 */
		MainSourceThird string `json:"mainSourceThird"`
	}

	BannerInfo := "{\"pcUrl\": \"https://cos.zdhsoft.com.cn/2023-09-01-0dbeea833395daee80fbbc46276b70d6-banner-2.jpg\", \"phoneUrl\": \"https://cos.zdhsoft.com.cn/2023-09-01-7b2721677c56d7f2290397b1c86ae0f0-banner-3.jpg\"}"
	UrlZb := "{\"backup1\": \"https://sample-videos.com/video123/flv/720/big_buck_bunny_720p_20mb.flv\", \"mainSource\": \"https://sample-videos.com/video123/flv/720/big_buck_bunny_720p_20mb.flv\", \"mainSourceThird\": \"https://live.zdhsoft.com.cn/sports/3999915.m3u8\"}"

	bf := bannerInfo{}
	vi := zbVideoInfo{}

	errbf := json.Unmarshal(([]byte)(BannerInfo), &bf)
	errvi := json.Unmarshal(([]byte)(UrlZb), &vi)

	fmt.Println(errbf, errvi, bf, vi)

}
