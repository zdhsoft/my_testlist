package test

import "fmt"

type TPoint struct {
	x int
	y int
}

func (p TPoint) calc() int {
	return p.x + p.y
}

func (p *TPoint) mul() int {
	return p.x * p.y
}

func getPoint(x int, y int) *TPoint {
	p := new(TPoint)
	p.x = x
	p.y = y
	return p
}

//Address 地址结构体
type Address struct {
	Province string
	City     string
}

//User 用户结构体
type User struct {
	Name    string
	Gender  string
	Address //匿名结构体
}

//Animal 动物
type Animal struct {
	name string
}

func (a *Animal) move() {
	fmt.Printf("%s会动！\n", a.name)
}

//Dog 狗
type Dog struct {
	Feet    int8
	*Animal //通过嵌套匿名结构体实现继承
}

func (d *Dog) wang() {
	fmt.Printf("%s会汪汪汪~\n", d.name)
}

func TestPoint() {
	p := new(TPoint)
	p.x = 100
	p.y = 200

	p1 := getPoint(200, 300)

	fmt.Println("point:", p.x, p.y, p.calc(), p.mul())
	fmt.Println("point1:", p1.x, p1.y, p1.calc(), p1.mul())

	var user2 User
	user2.Name = "pprof"
	user2.Gender = "女"
	user2.Address.Province = "黑龙江" //通过匿名结构体.字段名访问
	user2.City = "哈尔滨"             //直接访问匿名结构体的字段名
	fmt.Printf("%+v\n", user2)

	d1 := &Dog{
		Feet: 4,
		Animal: &Animal{ //注意嵌套的是结构体指针
			name: "乐乐",
		},
	}
	d1.wang() //乐乐会汪汪汪~
	d1.move() //乐乐会动！
}
