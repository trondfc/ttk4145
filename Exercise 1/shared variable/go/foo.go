// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	. "fmt"
	"runtime"
	"time"
)

var i int = 0

func incrementing(c chan int, q chan int) {
	//TODO: increment i 1000000 times
	for n := 0; n < 1000000; n++ {
		c <- 1
	}
	q <- 1
}

func decrementing(c chan int, q chan int) {
	//TODO: decrement i 1000000 times
	for n := 0; n < 1000000; n++ {
		c <- -1
	}
	q <- 1
}

func counter(c1 chan int, c2 chan int, q1 chan int, q2 chan int) {
	var quit1, quit2 bool = false, false
	//var temp int
	for {
		select {
		case <-c1:
			i++
		case <-c2:
			i--
		case <-q1:
			quit1 = true
		case <-q2:
			quit2 = true
		}
		if quit1 && quit2 {
			fmt.Println("End Program")
			return
		}
	}
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	runtime.GOMAXPROCS(4)
	ch1 := make(chan int)
	ch2 := make(chan int)

	qt1 := make(chan int)
	qt2 := make(chan int)

	// TODO: Spawn both functions as goroutines
	go incrementing(ch1, qt1)
	go decrementing(ch2, qt2)
	go counter(ch1, ch2, qt1, qt2)
	// We have no direct way to wait for the completion of a goroutine (without additional synchronization of some sort)
	// We will do it properly with channels soon. For now: Sleep.
	time.Sleep(1000 * time.Millisecond)
	Println("The magic number is:", i)
}
