package main
import("fmt" 
"time")

func counter(out chan<- int){
	for x:=0;x<100;x++{
		out<-x
		time.Sleep(200 * time.Millisecond)
	}
	close(out)
}
func squarer(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}
func squarer1(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}
func squarer2(out chan<-int,in<-chan int){
	for v:=range in{
		out<-v*v
		time.Sleep(500 * time.Millisecond)
	}
	close(out)
}

func printer(in<-chan int){
	for v:=range in{
		fmt.Print(v)
		fmt.Print(" ")
		time.Sleep(300 * time.Millisecond)
	}
}
func printer1(in<-chan int){
	for v:=range in{
		fmt.Print(v)
		fmt.Print(" ")
		time.Sleep(300 * time.Millisecond)
	}
}
func main(){
	naturals:=make(chan int)
	squares:=make(chan int)

	go counter(naturals)
	go squarer(squares,naturals)
	go squarer1(squares,naturals)
	go squarer2(squares,naturals)
	go printer1(squares)
	printer(squares)
}