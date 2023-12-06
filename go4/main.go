package main

import (
	"fmt"
	"net/url"
	"regexp"
	"strings"
)

func htmlFilter(html string) string {
	// 替换图片中的src链接
	re := regexp.MustCompile(`<img[^>]*src="([^"]*)"`)
	newBody := re.ReplaceAllStringFunc(html, func(match string) string {
		idx := strings.Index(match, "\"")
		if idx == -1 {
			return match
		}
		oldSrc := match[idx+1 : len(match)-1] // 提取旧的src链接
		newSrc := replaceDomain(oldSrc, "https://www.baidu.com")
		fmt.Printf("%s ==> %s\n", oldSrc, newSrc)
		return fmt.Sprintf(`<img src="%s"`, newSrc)
	})
	return newBody
}

func p(uuu string) {
	u, _ := url.Parse(uuu)
	fmt.Println("------------->" + uuu)
	fmt.Println("<<<<" + u.String())
	fmt.Printf("=====> u type is %T, u is %#v\n", u, u)
	/*
		u type is *url.URL,
		u is &url.URL{
			Scheme:"https", Opaque:"", User:(*url.Userinfo)(0xc000088150),
			Host:"www.baidu.com:80", Path:"/search", RawPath:"", ForceQuery:false,
			RawQuery:"mq=test", Fragment:"12345"
		}

	*/

	isABS := "no"
	if u.IsAbs() {
		isABS = "yes"
	}

	fmt.Printf("u.Scheme is %#v\n", u.Scheme) // u.Scheme is "https"
	fmt.Printf("u.Opaque is %#v\n", u.Opaque) // u.Opaque is ""
	fmt.Printf("u.User is %#v\n", u.User)
	// u.User is &url.Userinfo{username:"admin", password:"passwd", passwordSet:true}

	fmt.Printf("u.Host is %#v\n", u.Host)             // u.Host is "www.baidu.com:80"
	fmt.Printf("u.Path is %#v\n", u.Path)             // u.Path is "/search"
	fmt.Printf("u.RawPath is %#v\n", u.RawPath)       // u.RawPath is ""
	fmt.Printf("u.ForceQuery is %#v\n", u.ForceQuery) // u.ForceQuery is false
	fmt.Printf("u.RawQuery is %#v\n", u.RawQuery)     // u.RawQuery is "mq=test"
	fmt.Printf("u.Fragment is %#v\n", u.Fragment)
	fmt.Printf("u.Fragment is ABS=%s\n", isABS)

}

func replaceDomain(oldURL string, newDomain string) string {
	u, err := url.Parse(oldURL)
	if err != nil {
		return ""
	}

	h, err1 := url.Parse(newDomain)
	if err1 != nil {
		return ""
	}
	if h.Scheme != "" {
		u.Scheme = h.Scheme
		u.Host = h.Host
	} else {
		u.Scheme = "https"
		u.Host = newDomain
	}
	return u.String()
}

func replaceDomain2(oldURL, newDomain string) (string, error) {
	u, err := url.Parse(oldURL)
	if err != nil {
		return "", err
	}

	// 如果是相对链接，直接在前面加上域名
	if !u.IsAbs() {
		// u.Scheme = "http" // 默认使用 http 协议
		u.Host = newDomain
	} else {
		// 如果是绝对链接，替换域名
		u.Host = newDomain
		if u.Scheme == "https" {
			u.Scheme = "http"
		} else if u.Scheme == "" {
			u.Scheme = "http"
		}
	}
	return u.String(), nil
}



func main() {

	newHtml := htmlFilter("<p style=\"text-align: start;\"><span style=\"color: rgb(64, 64, 64);\">北京时间10月18日，火箭和雷霆完成一笔3换2的交易，火箭送出了后卫小凯文-波特和两个次轮签，得到雷霆的奥拉迪波和罗宾逊-厄尔。雷霆将立刻裁掉小波特，这两个次轮分别是森林狼的2027年次轮和雄鹿的2028年次轮。The Athletic第一时间揭秘小波特的这笔交易。</span></p><p style=\"text-align: start;\"><br></p><p style=\"text-align: start;\"><br></p><p style=\"text-align: justify;\"><strong>火箭一箭双雕，也付出代价</strong></p><p style=\"text-align: justify;\">NBA专家霍林格解析了火箭进行这笔交易的意义。对于火箭来说，这笔交易有两个层面的意义。</p><p style=\"text-align: justify;\">其一，显然是为了摆脱小波特，但火箭队也为自己节省了551万美元，并产生了451万美元的交易特例。</p><p style=\"text-align: justify;\">其二，火箭队还可以用罗宾逊-厄尔这个真正的现役球员来填补他的空缺。(人们推测火箭队希望他参与这笔交易，因为这笔交易本可以在没有他的情况下完成，从而节省更多的资金并产生更大的特例）。罗宾逊-厄尔的到来为火箭队增加了一名前场球员，特别是到了赛季中期，兰代尔、杰夫-格林的合同要是被交易的话，罗宾逊-厄尔会派上用场，而且罗宾逊-厄尔下赛季是199万美元的球队选项，火箭有主动权。上赛季，罗宾逊-厄尔场均6.8分4.2篮板。</p><p style=\"text-align: justify;\"><img src=\"https://bfw-pic-new01.obs.cn-south-1.myhuaweicloud.com/avatar/p0020231018092250023005.jpg\" alt=\"图片\" data-href=\"\" style=\"width: 680px;height: auto;\"></p><p style=\"text-align: justify;\">当然，火箭队确实付出了不小的代价，送出了两个次轮。理论上，火箭队也可以在揭幕战前用奥拉迪波即将到期的 945 万美元合同换取另一名球员，而不是直接放弃他，但火箭队的大名单已经满员，因此很可能需要 2 换 1，而奥拉迪波不能被打包；此外，任何奥拉迪波的交易如果需要占用资金，都会抵消这笔交易节省的资金。</p><p style=\"text-align: justify;\">The Athletic表示，现年31岁的奥拉迪波正在进行髌骨肌腱撕裂的康复治疗，本赛季不太可能出战。</p><p style=\"text-align: justify;\"><strong>雷霆精打细算，又获选秀签</strong></p><p style=\"text-align: start;\"><br></p><p style=\"text-align: justify;\">霍林格表示，雷霆在这笔交易上也是精打细算。通过这笔交易，雷霆将奢侈税线下的 451 万美元浮动工资变成了两个次轮签，未来代价也不大，雷霆需要明年为小波特 2024-25 年的轻度保障工资支付100万美元的工资帽费用。</p><p style=\"text-align: justify;\">火箭与多支球队进行了谈判，有的球队索要不止两个次轮签。那么，为什么和火箭做这笔交易的是雷霆，而不是其他球队呢？因为雷霆队有 18 份合同在身，预计无论如何都要放弃这笔交易中涉及的球员。雷霆队没有直接裁掉奥拉迪波和罗宾逊-厄尔，而是得到了两名未来的次轮签，同时也收回了他们在罗宾逊-厄尔身上的一些初始投资。(雷霆在 2021年选秀大会上交易了36 号和 34号签，就是为了将选秀顺位提升到第32位并选中罗宾逊-厄尔）。最后，他们还通过罗宾逊-厄尔获得了190万美元的交易特例。</p><p style=\"text-align: justify;\">对于雷霆来说，这是一笔非常不错的交易，他们又积累了更多的选秀签资产。名记Woj表示，未来7年，雷霆拥有15个首轮签和22个次轮签。</p><p style=\"text-align: justify;\"><strong>小波特拒绝认罪 女友更改口供</strong></p><p style=\"text-align: justify;\">自上个月小波特因涉嫌袭击女友而被指控犯有重伤和勒颈罪而被捕后，火箭队一直在努力交易波特。目前，家暴案已经开庭，小波特拒绝认罪，二级袭击罪指控已经被撤销，他的女友也更改了口供，否认小波特殴打自己。</p><p style=\"text-align: justify;\"><img src=\"https://bfw-pic-new01.obs.cn-south-1.myhuaweicloud.com/avatar/p0020231018092342000164.jpg\" alt=\"图片\" data-href=\"\" style=\"width: 680px;height: auto;\"></p><p style=\"text-align: justify;\"><img src=\"https://bfw-pic-new01.obs.cn-south-1.myhuaweicloud.com/avatar/p0020231018092357004297.jpg\" alt=\"图片\" data-href=\"\" style=\"width: 680px;height: auto;\"></p><p style=\"text-align: justify;\">“他没有打我，”这位 26 岁的前WNBA球员说道， “他从来没有握紧拳头打我，也肯定没有多次击打我的面部。那是谎言。我没有任何伤病来证明这一点。”</p><p style=\"text-align: justify;\">联盟消息人士此前透露，火箭队联系了多支球队，提出以选秀补偿来送走小波特，小波特的合同为4年8250万美元，其中第1年为1590万美元，还有3年合同为非保障。小波特是 2019 年的首轮秀，从克利夫兰被交易到休斯顿后，过去三个赛季都在火箭打球。火箭队在去年10 月份与这位 23 岁的球员续签了一份4年8250万美元的合同。</p>")
	fmt.Println(newHtml)
	fmt.Println(newHtml)
	//dddd := []string{"www.google.com", "www.google.com", "http://www.google.com", "https://www.google.com"}
	//test := []string{"api", "/api", "/api?aaaa=bbb", "https://www.com.cn/api?name=999&c=测试"}
	//
	//
	//
	//
	//for idx, t := range test {
	//	newDomain := dddd[idx]
	//	s := replaceDomain(t, newDomain)
	//	fmt.Printf("示例: [原:%s] [新域名:%s]=> %s\n", t, newDomain, s)
	//}

}
