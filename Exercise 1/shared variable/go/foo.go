// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	. "fmt"
	"runtime"
	"time"
)

var i = 0

func incrementing(ch1 chan int, ch2 chan int, done chan int) {
	//TODO: increment i 1000000 times
	for x := 0; x < 1000000; x++ {
		numb := <-ch1
		numb++
		ch2 <- numb
	}
	done <- 0
	for {
		temp := <-ch1
		ch2 <- temp
	}
}

func decrementing(ch1 chan int, ch2 chan int, done chan int) {
	//TODO: decrement i 1000000 times
	for x := 0; x < 1000005; x++ {
		numb := <-ch1
		numb--
		ch2 <- numb
	}
	done <- 0
	for {
		temp := <-ch1
		ch2 <- temp
	}
}

func server(ch1 chan int, ch2 chan int, done chan int) {
	var end int = 0
	for {
		select {
		case a := <-ch2:
			ch1 <- a
			i = a
		case h := <-done:
			end++
			h++
			if end == 2 {
				fmt.Println("end")
				return
			}
		}
	}
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	// Defines the max amount of running threads, by setting it to 1 you are no longer threading
	runtime.GOMAXPROCS(2)

	ch1 := make(chan int)
	ch2 := make(chan int)
	quit := make(chan int, 2)

	// TODO: Spawn both functions as goroutines
	go incrementing(ch1, ch2, quit)
	go decrementing(ch1, ch2, quit)

	ch1 <- 0
	server(ch1, ch2, quit)

	// We have no direct way to wait for the completion of a goroutine (without additional synchronization of some sort)
	// We will do it properly with channels soon. For now: Sleep.
	time.Sleep(500 * time.Millisecond)
	Println("The magic number is:", i)
}
