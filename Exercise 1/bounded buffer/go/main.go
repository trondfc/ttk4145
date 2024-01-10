package main

import (
	"fmt"
	"time"
)

func producer(b_buffer chan int) {

	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		// TODO: push real value to buffer
		b_buffer <- i
	}

}

func consumer(b_buffer chan int) {

	time.Sleep(1 * time.Second)
	for {
		i := <-b_buffer
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}

}

func main() {

	// TODO: make a bounded buffer
	b_buffer := make(chan int, 5)

	go consumer(b_buffer)
	go producer(b_buffer)

	select {}
}
