package _chan

import (
	"fmt"
	"sync"
	"time"
)

var cnt int = 1

func Process(ch chan int, ccc int) {
	time.Sleep(time.Duration(ccc) * time.Second)
	fmt.Println("cnt:", ccc)
	ch <- ccc
	cnt++
}

func TTT() {
	chs := make([]chan int, 10)
	for i := 0; i < 10; i++ {
		chs[9-i] = make(chan int)
		go Process(chs[9-i], cnt)
		cnt++
	}

	for i, ch := range chs {
		v, ok := <-ch
		if ok {
			fmt.Println("Routine", i, "value:", v, "quit", time.Now().Unix())
		} else {
			fmt.Println("读取失败: ---> ")
		}
	}
}

func t(ch chan int, wg *sync.WaitGroup) {
	for i := 0; i < 10; i++ {
		ch <- i
		time.Sleep(time.Second)
	}
	close(ch)
	wg.Done()
}

func kk(ch chan int, wg *sync.WaitGroup) {
	isClose := false
	for {
		if isClose {
			break
		}
		select {
		case i, ok := <-ch:
			if ok {
				fmt.Println("----> ", i)
			} else {
				isClose = true
			}
		default:
			time.Sleep(500 * time.Millisecond)
			fmt.Println("<<<<")
		}
	}
	fmt.Println("退出")
	wg.Done()
}

func K() {
	ci := make(chan int, 2)
	//for i := 1; i <= 2; i++ {
	//	ci <- i
	//}
	var wg sync.WaitGroup
	wg.Add(2)
	go t(ci, &wg)
	go kk(ci, &wg)
	wg.Wait()
	fmt.Println("hello exit")
	// close(ci)
	//cs := make(chan string, 2)
	//cs <- "hi"
	//cs <- "golang"
	//close(cs)
	//ciClosed, csClosed := false, false
	//for {
	//	if ciClosed && csClosed {
	//		return
	//	}
	//	select {
	//	case i, ok := <-ci:
	//		if ok {
	//			fmt.Println(i)
	//		} else {
	//			ciClosed = true
	//			// fmt.Println("ci closed")
	//		}
	//	case s, ok := <-cs:
	//		if ok {
	//			fmt.Println(s)
	//		} else {
	//			csClosed = true
	//			// fmt.Println("cs closed")
	//		}
	//	default:
	//		fmt.Println("waiting...")
	//	}
	//}
}
